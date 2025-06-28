#!/bin/sh
# Convert any video to robscript format (.rob)
# Usage: robconvert.sh input_file output_file.rob

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <input> <output.rob>" >&2
    exit 1
fi

in="$1"
out="$2"

# Use ffmpeg to convert to AV1 video and Opus audio inside MKV
ffmpeg -y -i "$in" -c:v libaom-av1 -crf 30 -b:v 0 -c:a libopus "$out"
