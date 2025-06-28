#!/bin/bash
# build_video.sh - convert video to AV1 format using ffmpeg
# Usage: ./build_video.sh input_file output_file

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 input_file output_file"
  exit 1
fi

INPUT="$1"
OUTPUT="$2"

ffmpeg -i "$INPUT" -c:v libaom-av1 -crf 30 -b:v 0 -c:a libopus "$OUTPUT"
