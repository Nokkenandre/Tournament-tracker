#!/usr/bin/env bash

docker build -t tournament-tracker-vnc .

docker run -p 5900:5900 -it tournament-tracker-vnc