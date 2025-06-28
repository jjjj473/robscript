# robscript

This repository provides an example script to convert videos to an AV1-based format. AV1 often achieves smaller file sizes than H.264 in MP4 containers while maintaining similar visual quality.

## Prerequisites

- **ffmpeg** built with `libaom-av1` and `libopus` support.

Install ffmpeg using your distribution's package manager or build it from source with these libraries enabled.

## Usage

```
./build_video.sh input_video output.mkv
```

The script encodes the input video to the AV1 codec (video) and Opus (audio) in an MKV container. Adjust the `-crf` value to trade off quality for file size (lower is higher quality).

The resulting file should offer smaller size than a comparable MP4 encoded with H.264 while remaining compatible with players like VLC or mpv on any Linux system.

## Building C tools

The `src` directory contains two small programs:

- **robformat** – converts any input video to a simple Matroska container encoded with the same codecs. It's primarily a format wrapper to create `.rob` files.
- **robplay** – a basic video player using FFmpeg and SDL2 to display `.rob` videos.

To build them, install the FFmpeg and SDL2 development packages and run:

```bash
cd src
make
```

This will create the `robformat` and `robplay` binaries inside `src/`.
