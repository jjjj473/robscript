# robscript

This project provides a single media player for a custom video format. The
player automatically converts other formats as needed and runs on Arch Linux.

## Prerequisites

- **ffmpeg** with `libaom-av1` and `libopus`
- **SDL2** development libraries

Install these packages using your distribution's package manager.

## Building the player

Inside the `src` directory simply run:

```bash
cd src
make
```

This produces a single binary:

- `robplayer` – a modular player that automatically converts videos to the `.rob`
  format before playback

To play a video with `robplayer`, provide the path on the command line:

```bash
./robplayer path/to/video.rob
```

If your path contains spaces or parentheses, wrap it in quotes:

```bash
./robplayer "path/with/Download(18).mp4"
```

`robplayer` will convert non-`.rob` files on the fly before playback.

## robplayer architecture

`robplayer` is organized into the following systems. Each component now
maintains its own small bit of state, paving the way for a fully featured
player:

1. **logging** – simple stdout logging API
2. **config** – configuration loader
3. **network** – placeholder for streaming support
4. **plugin** – dynamic module hooks
5. **playlist** – manage multiple files
6. **formatter** – converts other formats to `.rob`
7. **decoder** – video/audio decoding using FFmpeg
8. **audio_output** – audio playback via SDL2
9. **renderer** – video rendering via SDL2
10. **controller** – playback state machine
11. **input** – keyboard event handler
12. **core** – ties all other systems together
13. **robplayer main** – application entry point

The sample implementation keeps things lightweight but demonstrates how each
subsystem can interact.  Logging supports debug levels, the playlist tracks the
current file, and the controller manages a basic play/pause state.

### MP4 subsystem set

In addition to the core `.rob` systems, the player ships with a collection of
modules focused on the MP4 container. These components are mostly stubs but
illustrate how a more involved architecture might look:

1. **mp4_demuxer** – splits MP4 files into tracks
2. **mp4_muxer** – assembles tracks into a new MP4
3. **mp4_parser** – reads MP4 boxes and metadata
4. **mp4_metadata** – handles track tags and chapters
5. **mp4_stream** – placeholder streaming support
6. **mp4_index** – builds seek indexes
7. **mp4_cache** – caches frequently used segments
8. **mp4_thumbnail** – generates thumbnails from frames
9. **mp4_chapter** – manages chapter markers
10. **mp4_subtitle** – handles subtitle tracks
11. **mp4_encryption** – placeholder for DRM hooks
12. **mp4_quality** – manages adaptive quality settings

Each MP4 subsystem exposes `*_init()` and `*_shutdown()` functions which the
core invokes during startup and shutdown.
