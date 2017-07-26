#!/bin/bash

TARGET_BUILD_FOLDER=../build

mkdir $TARGET_BUILD_FOLDER
mkdir $TARGET_BUILD_FOLDER/run_pixy

cd $TARGET_BUILD_FOLDER/run_pixy
cmake ../../src/host/run_pixy
make
