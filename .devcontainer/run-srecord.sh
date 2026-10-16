#!/usr/bin/env bash
set -e

export DISPLAY=:1

if [ ! -x ./SRecord ]; then
  qmake SRecord.pro CONFIG+=debug
  make -j2
fi

exec ./SRecord
