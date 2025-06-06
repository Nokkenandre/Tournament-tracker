#!/bin/bash

docker run -it \
  -e WAYLAND_DISPLAY=wayland-0 \
  -e XDG_RUNTIME_DIR=/mnt/wslg/runtime-dir \
  -v /mnt/wslg/runtime-dir:/mnt/wslg/runtime-dir \
  tournament-tracker