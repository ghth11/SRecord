#!/usr/bin/env bash
set -e

export DISPLAY=:1

if ! pgrep -f "Xvfb :1" >/dev/null; then
  nohup Xvfb :1 -screen 0 1440x900x24 >/tmp/srecord-xvfb.log 2>&1 &
  sleep 1
fi

if ! pgrep -x fluxbox >/dev/null; then
  nohup fluxbox >/tmp/srecord-fluxbox.log 2>&1 &
fi

if ! pgrep -f "x11vnc.*:1" >/dev/null; then
  nohup x11vnc -display :1 -forever -shared -nopw -rfbport 5900 >/tmp/srecord-x11vnc.log 2>&1 &
fi

if ! pgrep -f "websockify.*6080" >/dev/null; then
  nohup websockify --web=/usr/share/novnc/ 6080 localhost:5900 >/tmp/srecord-novnc.log 2>&1 &
fi

echo "Virtual desktop ready on forwarded port 6080."
echo "Run: bash .devcontainer/run-srecord.sh"
