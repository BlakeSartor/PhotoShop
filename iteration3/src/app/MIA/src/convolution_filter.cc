/*******************************************************************************
 * Name            : tool.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/05/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_CONVOLUTION_FILTER_CC
#define INCLUDE_CONVOLUTION_FILTER_CC

/****************************************************************************
includes
****************************************************************************/

#include <cmath>
#include "include/mask.h"
#include "include/convolution_filter.h"
#include "include/filter.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"
#include "include/ui_ctrl.h"

/****************************************************************************
constructors / destructors
****************************************************************************/

ConvolutionFilter::ConvolutionFilter() {
}

ConvolutionFilter::~ConvolutionFilter() {
}

/****************************************************************************
Function Definitions
****************************************************************************/

image_tools::ColorData ConvolutionFilter::ApplyMask
  (int mouse_x, int mouse_y, image_tools::PixelBuffer *canvas) {
    image_tools::ColorData new_color(0, 0, 0);
    float divisor = 0;
    int center_x = floor(kernal_->GetWidth() / 2);
    int center_y = floor(kernal_->GetHeight() / 2);

    for (int mask_x = 0; mask_x < kernal_->GetWidth(); mask_x++) {
        for (int mask_y = 0; mask_y < kernal_->GetHeight(); mask_y++) {
            int apply_x = mouse_x + mask_x - center_x;
            int apply_y = mouse_y + mask_y - center_y;

            // check if pixel is in bounds
            if (apply_x >= 0 && apply_y >= 0 && apply_x < canvas->width()
              && apply_y < canvas->height()) {
                divisor += kernal_->GetOpacity(mask_x, mask_y);
                new_color = new_color + (canvas->get_pixel(apply_x, apply_y)
                  * kernal_->GetOpacity(mask_x, mask_y));
            }
        }
    }
    if (divisor != 0) new_color = new_color * (1 / divisor);

    // check if color is in bounds
    if (new_color.getRed() > 1.0) new_color.red(1.0);
    if (new_color.getRed() < 0.0) new_color.red(0.0);
    if (new_color.getGreen() > 1.0) new_color.green(1.0);
    if (new_color.getGreen() < 0.0) new_color.green(0.0);
    if (new_color.getBlue() > 1.0) new_color.blue(1.0);
    if (new_color.getBlue() < 0.0) new_color.blue(0.0);

    return new_color;
}

void ConvolutionFilter::ApplyFilter(image_tools::PixelBuffer *canvas) {
    image_tools::PixelBuffer *new_canvas
      = new image_tools::PixelBuffer(*canvas);

    for (int x = 0; x < canvas->width(); x++) {
        for (int y = 0; y < canvas->height(); y++) {
            canvas->set_pixel(x, y, ApplyMask(x, y, new_canvas));
        }
    }
    delete new_canvas;
}

void ConvolutionFilter::
  ApplyFilter(image_tools::PixelBuffer *canvas, int size) {
    SetMask(size);
    ApplyFilter(canvas);
}

void ConvolutionFilter::ApplyFilter
  (image_tools::PixelBuffer *canvas, int size,
      enum image_tools::UICtrl::MotionBlurDirection direction) {
    SetMask(size, direction);
    ApplyFilter(canvas);
}

#endif
