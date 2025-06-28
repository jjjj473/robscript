# robscript

This project provides tools for working with a custom video format. It includes
conversion utilities and a modular media player for Arch Linux.

## Prerequisites

- **ffmpeg** with `libaom-av1` and `libopus`
- **SDL2** development libraries

Install these packages using your distribution's package manager.

## Video conversion

Use the helper script to convert videos to an AV1+Opus Matroska file:

```bash
./build_video.sh input.mp4 output.rob
```

## Building the C tools

Inside the `src` directory you will find a converter and two players. Run:

```bash
cd src
make
```

This produces three binaries:

- `robformat` – wraps any video into a `.rob` container
- `robplay` – minimal SDL2 player for `.rob` files
- `robplayer` – experimental modular player built around twelve systems

## robplayer architecture

`robplayer` is organized into the following systems:

1. **logging** – simple stdout logging API
2. **config** – configuration loader
3. **network** – placeholder for streaming support
4. **plugin** – dynamic module hooks
5. **playlist** – manage multiple files
6. **decoder** – video/audio decoding using FFmpeg
7. **audio_output** – audio playback via SDL2
8. **renderer** – video rendering via SDL2
9. **controller** – playback state machine
10. **input** – keyboard event handler
11. **core** – ties all other systems together
12. **robplayer main** – application entry point

Currently each system only prints initialization and shutdown messages, but the
structure allows further expansion for a full-featured media player.
