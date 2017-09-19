/*******************************************************************************
 * Name            : rgb_levels.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/10/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_RGB_LEVELS_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_RGB_LEVELS_H_

/****************************************************************************
includes
****************************************************************************/

#include "filter.h"
#include "pixel_buffer.h"
#include "color_data.h"

/****************************************************************************
class definitions
****************************************************************************/

class RGBLevels : public Filter {
 public:
    RGBLevels() {}
    ~RGBLevels() {}
    void ApplyFilter(image_tools::PixelBuffer *canvas, float r_mod,
      float g_mod, float b_mod);

 protected:
    void virtual ModifyPixel(int x, int y, image_tools::PixelBuffer *canvas,
      float r_mod, float g_mod, float b_mod);
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_RGB_LEVELS_H_
