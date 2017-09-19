/*******************************************************************************
 * Name            : filter.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/05/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_THRESHOLD_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_THRESHOLD_H_

/****************************************************************************
includes
****************************************************************************/

#include "filter.h"
#include "pixel_buffer.h"
#include "color_data.h"

/****************************************************************************
class definitions
****************************************************************************/

class Threshold : public Filter {
 public:
    Threshold() {}
    ~Threshold() {}
    void ApplyFilter(image_tools::PixelBuffer *canvas, double thresh);

 protected:
    void virtual ModifyPixel(int x, int y, image_tools::PixelBuffer *canvas,
      double thresh);
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_THRESHOLD_H_
