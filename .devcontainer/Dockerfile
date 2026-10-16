FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    qtbase5-dev \
    qt5-qmake \
    libqt5sql5-sqlite \
    sqlite3 \
    xvfb \
    fluxbox \
    x11vnc \
    novnc \
    websockify \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
