#!/bin/bash

TARGET_BUILD_FOLDER=../build

mkdir $TARGET_BUILD_FOLDER
mkdir $TARGET_BUILD_FOLDER/close_pixy

cd $TARGET_BUILD_FOLDER/close_pixy
cmake ../../src/host/close_pixy
make
