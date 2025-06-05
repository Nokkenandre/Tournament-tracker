#!/bin/bash

Xvfb :1 -screen 0 1024x768x16 &
sleep 2
export DISPLAY=:1
fluxbox &
x11vnc -display :1 -nopw -forever -shared &

python3 /app/backend/flask_interface.py &

exec /app/build/bin/Tournament_tracker
