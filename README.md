# ofxSpectralSaliency

Spectral Residual Saliency Map addon for OpenFrameworks

![Saliency Map Example](https://raw.githubusercontent.com/bemoregt/ofxSpectralSaliency-/master/ScrShot%2016.png "Saliency Map")
![Saliency Map Example 2](https://raw.githubusercontent.com/bemoregt/ofxSpectralSaliency-/master/ScrShot%208.png "Saliency Map 2")

## Description

This addon implements the spectral residual approach for detecting visually salient regions in images. The algorithm works by analyzing the log spectrum of an image and extracting the spectral residual, which highlights visually distinctive parts of the image. Based on the paper "Saliency Detection: A Spectral Residual Approach" by Xiaodi Hou and Liqing Zhang.

## Dependencies

- OpenFrameworks 0.10.0+
- ofxOpenCv
- ofxCv
- ofxGui

## Installation

1. Download the repository
2. Copy the ofxSpectralSaliency folder into the OpenFrameworks/addons folder
3. Add the required addons to your project

## Usage

```cpp
// Include the addon
#include "ofxSpectralSaliency.h"

// In your app
ofxSpectralSaliency saliency;
ofImage inputImage;
ofImage outputImage;

// In setup()
inputImage.load("your_image.jpg");

// In update() or where needed
saliency.computeSaliencyMap(inputImage, outputImage);

// Optional: adjust parameters
saliency.setGaussianSize(11);  // Must be odd number
saliency.setKernelSize(5);     // Must be odd number
```

## Parameters

- **Gaussian Size**: Controls the Gaussian blur applied to the magnitude spectrum (default: 9)
- **Kernel Size**: Controls the box filter size for smoothing the log amplitude spectrum (default: 3)

## Example

The example demonstrates how to use the addon to:
- Load images (including drag and drop)
- Compute saliency maps
- Adjust parameters using GUI
- Save results

## Reference

```
@inproceedings{
title = {Saliency Detection: A Spectral Residual Approach},
author = {Xiaodi Hou, Liqing Zhang},
booktitle={Conference on Computer Vision and Pattern Recognition (CVPR)},
year = {2007}}
```

Find the paper at www.houxiaodi.com/assets/papers/cvpr07.pdf

## License

MIT License
