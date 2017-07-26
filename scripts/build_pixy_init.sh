#!/bin/bash

TARGET_BUILD_FOLDER=../build

mkdir $TARGET_BUILD_FOLDER
mkdir $TARGET_BUILD_FOLDER/pixy_init

cd $TARGET_BUILD_FOLDER/pixy_init
cmake ../../src/host/pixy_init
make
