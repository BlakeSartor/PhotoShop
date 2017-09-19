/*******************************************************************************
 * Name            : filter.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/05/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_FILTER_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_FILTER_H_

/****************************************************************************
includes
****************************************************************************/

#include "include/pixel_buffer.h"
#include "include/color_data.h"

/****************************************************************************
class definitions
****************************************************************************/

class Filter {
 public:
    Filter();
    virtual ~Filter();
    void ApplyFilter(image_tools::PixelBuffer *canvas);
 protected:
    void virtual ModifyPixel(int x, int y, image_tools::PixelBuffer *canvas) {}
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_FILTER_H_
