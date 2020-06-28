# Disparity Map Generator

## Stereo Matching

When our eyes view a scene, the left and right eyes see slightly different things. The left and right images are known as a stereo pair. By matching the corresponding points in the two images, we are able to infer the depth of the scene.

<p align="center">
  <img src="Stereo%20Pairs/Pair%202/view1.png" />
  <img src="Stereo%20Pairs/Pair%202/view2.png" />
</p>

<p align="center">
  <img src="Stereo%20Pairs/Pair%202/disp1.png" />
</p>

The paper below proposes using a dynamic programming algorithm to perform stereo matching, which I have implemented in C++.

> Cox, I.J., Hingorani, S., Maggs, B.M. and Rao, S.B. (1992). Stereo Without Disparity Gradient Smoothing: A Bayesian Sensor Fusion Solution. Procedings of the British Machine Vision Conference 1992. [online] Available at: http://www.bmva.org/bmvc/1992/bmvc-92-035.pdf.

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

* `opencv4`
