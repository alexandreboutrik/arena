#!/bin/bash

mkdir -p ./build

CFLAGS="-std=c99 -O3 -pipe"
WARNFLAGS="-W -Wall -Wextra -Wpedantic -Wformat=2"

CFILES="source/*.c source/include/*.c source/include/screen/*.c"

EXEFILE="./build/arena"
ASSETS="/home/$(whoami)/.local/share/arena"

function print_help() {
  echo "Usage: $0 [dev:d|compile:c|run:r|install:i]"
  exit 1
}

function compile() {
  if [ ! -d "./assets" ]; then
    echo "- Please cd the Arena's root directory for compiling"
    exit 1
  fi

  rm -rf "${ASSETS}"
  mkdir -p "${ASSETS}"
  cp -r "./assets" "${ASSETS}"

  gcc ${CFILES} ${CFLAGS} ${WARNFLAGS} -DASSETS=\"${ASSETS}/assets\" \
    $(pkg-config --libs raylib) \
    $(cat compile_flags.txt) \
    -o "${EXEFILE}" && echo "+ Compiled successfully."
}

function install() {
  if [ ! -f "${EXEFILE}" ]; then
    echo "- Please compile the source code first."
    exit 1
  fi

  sudo cp "${EXEFILE}" "/usr/local/bin"
}

if [ $# -eq 0 ]; then
  print_help
fi

while [ $# -gt 0 ]; do
  case "${1}" in
  "fps")
    gcc source/others/ps2.c -o ./build/ps2 \
      $(pkg-config --libs raylib) && ./build/ps2
    exit
    ;;
  "test")
    gcc source/others/test.c -o ./build/test \
      $(pkg-config --libs raylib) && ./build/test
    exit
    ;;
  "dev") ;&
  "d")
    CFLAGS="${CFLAGS} -DDEVMODE=1"
    ;;
  "compile") ;&
  "c")
    compile
    ;;
  "run") ;&
  "r")
    "${EXEFILE}"
    ;;
  "install") ;&
  "i")
    install
    ;;
  *)
    echo "- Invalid option: ${0} ${1}."
    print_help
    ;;
  esac

  shift
done
