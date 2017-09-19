/*******************************************************************************
 * Name            : convolution_filter.h
 * Project         : Flashphoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/5/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_CONVOLUTION_FILTER_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_CONVOLUTION_FILTER_H_

/****************************************************************************
includes
****************************************************************************/

#include "mask.h"
#include "pixel_buffer.h"
#include "color_data.h"
#include "filter.h"
#include "ui_ctrl.h"

/****************************************************************************
class definitions
****************************************************************************/

class ConvolutionFilter : public Filter{
 public:
    ConvolutionFilter();
    virtual ~ConvolutionFilter();
    void virtual SetMask() {}  // SetMask will be defined for each child
    void virtual SetMask(int size) {}
    void virtual SetMask(int size,
      enum image_tools::UICtrl::MotionBlurDirection direction) {}

    image_tools::ColorData virtual ApplyMask(int mouse_x, int mouse_y,
        image_tools::PixelBuffer *canvas);
    void virtual ApplyFilter(image_tools::PixelBuffer *canvas);
    void virtual ApplyFilter(image_tools::PixelBuffer *canvas, int size);
    void virtual ApplyFilter(image_tools::PixelBuffer *canvas, int size,
      enum image_tools::UICtrl::MotionBlurDirection direction);
 protected:
    Mask* kernal_;
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_CONVOLUTION_FILTER_H_
