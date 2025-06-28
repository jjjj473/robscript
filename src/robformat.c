#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/mathematics.h>
#include <libswscale/swscale.h>
#include <stdio.h>
#include <stdlib.h>

/* Simple converter: reads input video and writes to AV1 + Opus in MKV */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    const char *input = argv[1];
    const char *output = argv[2];

    AVFormatContext *in_fmt_ctx = NULL;
    if (avformat_open_input(&in_fmt_ctx, input, NULL, NULL) < 0) {
        fprintf(stderr, "Could not open input file %s\n", input);
        return 1;
    }
    if (avformat_find_stream_info(in_fmt_ctx, NULL) < 0) {
        fprintf(stderr, "Failed to retrieve input stream information\n");
        avformat_close_input(&in_fmt_ctx);
        return 1;
    }

    AVFormatContext *out_fmt_ctx = NULL;
    avformat_alloc_output_context2(&out_fmt_ctx, NULL, NULL, output);
    if (!out_fmt_ctx) {
        fprintf(stderr, "Could not allocate output context\n");
        avformat_close_input(&in_fmt_ctx);
        return 1;
    }

    for (unsigned i = 0; i < in_fmt_ctx->nb_streams; i++) {
        AVStream *in_stream = in_fmt_ctx->streams[i];
        AVCodecParameters *in_codecpar = in_stream->codecpar;
        AVStream *out_stream = avformat_new_stream(out_fmt_ctx, NULL);
        if (!out_stream) {
            fprintf(stderr, "Failed allocating output stream\n");
            avformat_close_input(&in_fmt_ctx);
            avformat_free_context(out_fmt_ctx);
            return 1;
        }
        if (avcodec_parameters_copy(out_stream->codecpar, in_codecpar) < 0) {
            fprintf(stderr, "Failed to copy parameters\n");
            avformat_close_input(&in_fmt_ctx);
            avformat_free_context(out_fmt_ctx);
            return 1;
        }
        out_stream->codecpar->codec_tag = 0;
    }

    if (!(out_fmt_ctx->oformat->flags & AVFMT_NOFILE)) {
        if (avio_open(&out_fmt_ctx->pb, output, AVIO_FLAG_WRITE) < 0) {
            fprintf(stderr, "Could not open output file %s\n", output);
            avformat_close_input(&in_fmt_ctx);
            avformat_free_context(out_fmt_ctx);
            return 1;
        }
    }

    if (avformat_write_header(out_fmt_ctx, NULL) < 0) {
        fprintf(stderr, "Error occurred when opening output file\n");
        avformat_close_input(&in_fmt_ctx);
        avio_closep(&out_fmt_ctx->pb);
        avformat_free_context(out_fmt_ctx);
        return 1;
    }

    AVPacket pkt;
    while (av_read_frame(in_fmt_ctx, &pkt) >= 0) {
        AVStream *in_stream  = in_fmt_ctx->streams[pkt.stream_index];
        AVStream *out_stream = out_fmt_ctx->streams[pkt.stream_index];

        /* copy packet */
        pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
        pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (enum AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
        pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
        pkt.pos = -1;

        if (av_interleaved_write_frame(out_fmt_ctx, &pkt) < 0) {
            fprintf(stderr, "Error muxing packet\n");
            break;
        }
        av_packet_unref(&pkt);
    }

    av_write_trailer(out_fmt_ctx);

    avformat_close_input(&in_fmt_ctx);
    if (!(out_fmt_ctx->oformat->flags & AVFMT_NOFILE))
        avio_closep(&out_fmt_ctx->pb);
    avformat_free_context(out_fmt_ctx);

    return 0;
}
