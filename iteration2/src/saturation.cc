/*******************************************************************************
 * Name            : saturation.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/10/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_SATURATION_CC
#define INCLUDE_SATURATION_CC

/****************************************************************************
includes
****************************************************************************/

#include <cmath>
#include "include/filter.h"
#include "include/saturation.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/****************************************************************************
constructors / destructors
****************************************************************************/


/****************************************************************************
function definitions
****************************************************************************/

void Saturation::ModifyPixel(int x, int y, image_tools::PixelBuffer *canvas,
  double adjustment) {
    // setup new color
    double red, green, blue;
    red = (canvas->get_pixel(x, y).getRed());
    blue = (canvas->get_pixel(x, y).getBlue());
    green = (canvas->get_pixel(x, y).getGreen());

    // multiplies the difference between the color value,
    // and the middle color value by adjustment
    red = (red - 0.5) * adjustment + 0.5;
    green = (green - 0.5) * adjustment + 0.5;
    blue = (blue - 0.5) * adjustment + 0.5;

    // makes sure color is within range
    if (red > 1.0) red = 1.0;
    if (red < 0.0) red = 0.0;
    if (green > 1.0) green = 1.0;
    if (green < 0.0) green = 0.0;
    if (blue > 1.0) blue = 1.0;
    if (blue < 0.0) blue = 0.0;

    // assign new color data
    image_tools::ColorData new_color(red, green,  blue);
    canvas->set_pixel(x, y , new_color);
}

void Saturation::ApplyFilter(image_tools::PixelBuffer *canvas,
  double adjustment) {
    for (int x = 0 ; x++ ; x < canvas->width()) {
        for (int y = 0 ; y++ ; y < canvas->height()) {
            ModifyPixel(x, y, canvas, adjustment);
        }
    }
}

#endif
