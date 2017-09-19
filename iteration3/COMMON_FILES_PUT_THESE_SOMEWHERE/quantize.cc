/*******************************************************************************
 * Name            : quantize.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/10/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_QUANTIZE_CC
#define INCLUDE_QUANTIZE_CC

/****************************************************************************
includes
****************************************************************************/

#include <cmath>
#include "include/filter.h"
#include "include/quantize.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/****************************************************************************
constructors / destructors
****************************************************************************/


/****************************************************************************
function definitions
****************************************************************************/

void Quantize::ModifyPixel(int x, int y, image_tools::PixelBuffer *canvas,
  int partitions) {
    // setup new color
    double red, green, blue;
    red = (canvas->get_pixel(x, y).getRed());
    blue = (canvas->get_pixel(x, y).getBlue());
    green = (canvas->get_pixel(x, y).getGreen());

    // calculate new color
    red = floor(red * partitions + 0.5) / partitions;
    blue = floor(blue * partitions + 0.5) / partitions;
    green = floor(green * partitions + 0.5) / partitions;

    // makes sure color is within range
    if (red > 1.0) red = 1.0;
    if (red < 0.0) red = 0.0;
    if (green > 1.0) green = 1.0;
    if (green < 0.0) green = 0.0;
    if (blue > 1.0) blue = 1.0;
    if (blue < 0.0) blue = 0.0;

    // assign new color data
    image_tools::ColorData new_color(red, green, blue);
    canvas->set_pixel(x, y , new_color);
}

void Quantize::ApplyFilter(image_tools::PixelBuffer *canvas, int partitions) {
    for (int x = 0 ; x < canvas->width() ; x++) {
        for (int y = 0 ; y < canvas->height() ; y++) {
            ModifyPixel(x, y, canvas, partitions);
        }
    }
}

#endif
