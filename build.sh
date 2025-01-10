#!/bin/bash

mkdir -p ./build

RAYLIB_STATIC="./dependencies/raylib-5.5/build/raylib"

LFLAGS="-lm -L${RAYLIB_STATIC} -lraylib"
CFLAGS="-std=c99 -O3 -pipe"
WARNFLAGS="-W -Wall -Wextra -Wpedantic -Wformat=2"

CINCL="-I./include -I./source"
CFILES="source/*.c source/include/*.c source/include/screen/*.c"

EXEFILE="./build/arena"
ASSETS="/home/$(whoami)/.local/share/arena"

function print_help() {
  echo "Usage: $0 [dev:d|compile:c|run:r|install:i]"
  exit 1
}

function check_dependencies() {
  if [ ! -f "${RAYLIB_STATIC}/libraylib.a" ]; then
    compile_raylib
  fi
}

function compile_raylib() {
  if [ ! -d "./dependencies/raylib-5.5/" ]; then
    unzip ./dependencies/raylib-5.5.zip -d ./dependencies/
  fi

  mkdir ./dependencies/raylib-5.5/build
  cmake -B ./dependencies/raylib-5.5/build -S./dependencies/raylib-5.5/
  make PLATFORM=PLATFORM_DESKTOP -B -C ./dependencies/raylib-5.5/build/

  if [ $? -ne 0 ]; then
    echo "- Error while compiling the dependency: Raylib"
    exit 1
  fi

  echo "+ Dependency: Raylib compiled successfully."
}

function compile() {
  if [ ! -d "./assets" ]; then
    echo "- Please cd the Arena's root directory for compiling"
    exit 1
  fi

  rm -rf "${ASSETS}"
  mkdir -p "${ASSETS}"
  cp -r "./assets" "${ASSETS}"

  gcc ${CINCL} ${CFILES} ${CFLAGS} ${WARNFLAGS} ${LFLAGS} \
    -DASSETS=\"${ASSETS}/assets\" \
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
    check_dependencies
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
