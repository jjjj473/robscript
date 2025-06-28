#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <SDL2/SDL.h>
#include <stdio.h>

/* Very simple video player for robs format using FFmpeg + SDL2 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        return 1;
    }
    const char *input = argv[1];
    AVFormatContext *fmt_ctx = NULL;
    if (avformat_open_input(&fmt_ctx, input, NULL, NULL) < 0) {
        fprintf(stderr, "Could not open %s\n", input);
        return 1;
    }
    if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        fprintf(stderr, "Failed to retrieve input stream info\n");
        avformat_close_input(&fmt_ctx);
        return 1;
    }

    int video_stream_index = -1;
    for (unsigned i = 0; i < fmt_ctx->nb_streams; i++) {
        if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index = i;
            break;
        }
    }
    if (video_stream_index == -1) {
        fprintf(stderr, "No video stream found\n");
        avformat_close_input(&fmt_ctx);
        return 1;
    }

    AVCodecParameters *codecpar = fmt_ctx->streams[video_stream_index]->codecpar;
    const AVCodec *codec = avcodec_find_decoder(codecpar->codec_id);
    if (!codec) {
        fprintf(stderr, "Decoder not found\n");
        avformat_close_input(&fmt_ctx);
        return 1;
    }

    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
    if (!codec_ctx) {
        avformat_close_input(&fmt_ctx);
        return 1;
    }
    if (avcodec_parameters_to_context(codec_ctx, codecpar) < 0) {
        fprintf(stderr, "Could not copy codec parameters\n");
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&fmt_ctx);
        return 1;
    }
    if (avcodec_open2(codec_ctx, codec, NULL) < 0) {
        fprintf(stderr, "Could not open codec\n");
        avcodec_free_context(&codec_ctx);
        avformat_close_input(&fmt_ctx);
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *win = SDL_CreateWindow("robplay", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        codec_ctx->width, codec_ctx->height, SDL_WINDOW_SHOWN);
    if (!win) {
        fprintf(stderr, "SDL: could not create window - exiting: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING,
                                             codec_ctx->width, codec_ctx->height);

    struct SwsContext *sws = sws_getContext(codec_ctx->width, codec_ctx->height, codec_ctx->pix_fmt,
                                            codec_ctx->width, codec_ctx->height, AV_PIX_FMT_YUV420P,
                                            SWS_BILINEAR, NULL, NULL, NULL);

    AVFrame *frame = av_frame_alloc();
    AVFrame *frameYUV = av_frame_alloc();
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, codec_ctx->width, codec_ctx->height, 1);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(frameYUV->data, frameYUV->linesize, buffer, AV_PIX_FMT_YUV420P,
                         codec_ctx->width, codec_ctx->height, 1);

    AVPacket packet;
    while (av_read_frame(fmt_ctx, &packet) >= 0) {
        if (packet.stream_index == video_stream_index) {
            if (avcodec_send_packet(codec_ctx, &packet) >= 0) {
                while (avcodec_receive_frame(codec_ctx, frame) >= 0) {
                    sws_scale(sws, (const uint8_t * const*)frame->data, frame->linesize, 0,
                              codec_ctx->height, frameYUV->data, frameYUV->linesize);
                    SDL_UpdateYUVTexture(texture, NULL,
                        frameYUV->data[0], frameYUV->linesize[0],
                        frameYUV->data[1], frameYUV->linesize[1],
                        frameYUV->data[2], frameYUV->linesize[2]);

                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    SDL_Event event;
                    SDL_PollEvent(&event);
                }
            }
        }
        av_packet_unref(&packet);
    }

    av_free(buffer);
    av_frame_free(&frameYUV);
    av_frame_free(&frame);
    sws_freeContext(sws);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    avcodec_free_context(&codec_ctx);
    avformat_close_input(&fmt_ctx);
    return 0;
}
