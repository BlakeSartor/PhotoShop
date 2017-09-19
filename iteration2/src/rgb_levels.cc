/*******************************************************************************
 * Name            : rgb_levels.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/10/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_RGB_LEVELS_CC
#define INCLUDE_RGB_LEVELS_CC

/****************************************************************************
includes
****************************************************************************/

#include "include/rgb_levels.h"
#include <cmath>
#include <iostream>
#include "include/filter.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"


/****************************************************************************
constructors / destructors
****************************************************************************/


/****************************************************************************
function definitions
****************************************************************************/

void RGBLevels::ModifyPixel(int x, int y, image_tools::PixelBuffer *canvas,
  float r_mod, float g_mod, float b_mod) {
    // setup new color
    double red, green, blue;
    red = (canvas->get_pixel(x, y).getRed() * r_mod);
    blue = (canvas->get_pixel(x, y).getBlue() * b_mod);
    green = (canvas->get_pixel(x, y).getGreen() * g_mod);

    // keeping colors in bounds
    if (red > 1.0) red = 1.0;
    if (green > 1.0) green = 1.0;
    if (blue > 1.0) blue = 1.0;

    // assign new color data
    image_tools::ColorData new_color(red, green, blue);
    canvas->set_pixel(x, y, new_color);
}

void RGBLevels::ApplyFilter(image_tools::PixelBuffer *canvas, float r_mod,
  float g_mod, float b_mod) {
    std::cout << "RGBLevels ApplyFilter\n";
    for (int x = 0 ; x < canvas->width() ; x++) {
        for (int y = 0 ; y < canvas->height() ; y++) {
            ModifyPixel(x, y, canvas, r_mod, g_mod, b_mod);
            // std::cout << "now looking at pixel: (" << x << ", " << y <<")\n";
        }
    }
}

#endif
