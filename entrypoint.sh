#!/bin/bash
set -e

export WAYLAND_DISPLAY=wayland-0
export XDG_RUNTIME_DIR=/mnt/wslg/runtime-dir
export QT_QPA_PLATFORM=wayland

# Start Flask server in background
python3 /app/backend/flask_interface.py &

# Optional: wait for server to be ready (simple fixed delay here)
sleep 3

# Start Qt app in foreground (keeps container alive)
exec /app/build/bin/Tournament_tracker