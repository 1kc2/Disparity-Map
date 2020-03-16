# Disparity Map Generator

## Compile
Both files can be compiled using the shell script which can be ran with `./compile.sh`.

## Usage

### To generate a disparity map for two images (same size)
Execute `./disparity <LEFT_IMG_FILENAME> <RIGHT_IMG_FILENAME>`.
Pairs of images to test with can be found in the `Stereo Pairs` directory

### To generate a random dot test case
Execute `./stereogram` to generate two random dot stereograms, `left.png` and `right.png` in the same directory as the program.

These can be passed as arguments like so `./disparity left.png right.png` to generate a disparity map for the random dot stereograms.

## Prerequisites

* `clang` with C++11 support

* `opencv`
