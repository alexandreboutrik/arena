#!/bin/bash

mkdir -p ./build

CC="cc"

RAYLIB_STATIC="./dependencies/raylib-5.5/build/raylib"

LFLAGS="-L${RAYLIB_STATIC} -l:libraylib.a -lm"
CFLAGS="-std=c99 -pipe"
WARNFLAGS="-W -Wall -Wextra -Wpedantic -Wformat=2"

CINCL="-I./include -I./source"
CFILES="source/*.c source/include/*.c source/include/screen/*.c"

EXEFILE="./build/arena"
ASSETS="/home/$(whoami)/.local/share/arena"

function print_help() {
  echo "Usage: $0 [dev:d|compile:c|run:r|install:i|clean:cl|uninstall:un]"
  exit 1
}

function check_dependencies() {
  if [ ! -f "${RAYLIB_STATIC}/libraylib.a" ]; then
    LSB_RELEASE=$(cat /etc/lsb-release)

    echo "${LSB_RELEASE}" | grep -i -q ubuntu
    if [ $? -eq 0 ]; then
      echo "! Distribution detected: Ubuntu"
      sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
    fi

    echo "${LSB_RELEASE}" | grep -i -q fedora
    if [ $? -eq 0 ]; then
      echo "! Distribution detected: Fedora"
      sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic
    fi

    echo "${LSB_RELEASE}" | grep -i -q arch
    if [ $? -eq 0 ]; then
      echo "! Distribution detected: Arch Linux"
      sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
    fi

    compile_raylib
  fi
}

function compile_raylib() {
  if [ ! -d "./dependencies/raylib-5.5/" ]; then
    unzip ./dependencies/raylib-5.5.zip -d ./dependencies/

    if [ $? -ne 0 ]; then
      echo "- Please cd the Arena's root directory first."
      exit 1
    fi
  fi

  mkdir ./dependencies/raylib-5.5/build
  cmake -B ./dependencies/raylib-5.5/build -S ./dependencies/raylib-5.5/
  make PLATFORM=PLATFORM_DESKTOP -B -C ./dependencies/raylib-5.5/build/

  if [ $? -ne 0 ]; then
    echo "- Error while compiling the dependency: Raylib"
    exit 1
  fi

  echo "+ Dependency: Raylib compiled successfully."
}

function compile() {
  if [ ! -d "./assets" ]; then
    echo "- Please cd the Arena's root directory first."
    exit 1
  fi

  rm -rf "${ASSETS}"
  mkdir -p "${ASSETS}"
  cp -r "./assets" "${ASSETS}"

  ${CC} ${CINCL} ${CFILES} ${CFLAGS} ${WARNFLAGS} ${LFLAGS} \
    -DASSETS=\"${ASSETS}/assets\" \
    -o "${EXEFILE}" && echo "+ Arena compiled successfully."
}

function install() {
  if [ ! -f "${EXEFILE}" ]; then
    echo "- Please compile the source code first."
    exit 1
  fi

  sudo cp "${EXEFILE}" "/usr/local/bin"
}

function clean() {
  if [ ! -d "./assets" ]; then
    echo "- Please cd the Arena's root directory first."
    exit 1
  fi

  rm -rf ./dependencies/raylib-5.5/
  rm -rf ./build && mkdir ./build
  rm -rf "${ASSETS}"

  echo "+ Cleaned."
}

function uninstall() {
  sudo rm "/usr/local/bin/arena" 1>/dev/null 2>&1
  echo "+ Executable removed."
}

if [ $# -eq 0 ]; then
  print_help
fi

while [ $# -gt 0 ]; do
  case "${1}" in
  "ps2")
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
  "clean") ;&
  "cl")
    clean
    ;;
  "uninstall") ;&
  "un")
    uninstall
    exit
    ;;
  *)
    echo "- Invalid option: ${0} ${1}."
    print_help
    ;;
  esac

  shift
done
