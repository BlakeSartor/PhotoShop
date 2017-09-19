/*******************************************************************************
 * Name            : threshold.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/05/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_THRESHOLD_CC
#define INCLUDE_THRESHOLD_CC

/**************************************************************************//**
* includes
****************************************************************************/

#include <cmath>
#include "include/filter.h"
#include "include/threshold.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/**************************************************************************//**
* constructors / destructors
****************************************************************************/


/**************************************************************************//**
* Member Functions
****************************************************************************/

void Threshold::ModifyPixel(int x, int y, image_tools::PixelBuffer *canvas,
  double thresh) {
    /*! setup new color. */
    double red, green, blue;
    red = (canvas->get_pixel(x, y).getRed() > thresh);
    blue = (canvas->get_pixel(x, y).getBlue() > thresh);
    green = (canvas->get_pixel(x, y).getGreen() > thresh);

    /*! assign new color data. */
    image_tools::ColorData new_color(red, green, blue);
    canvas->set_pixel(x, y , new_color);
}

void Threshold::ApplyFilter(image_tools::PixelBuffer *canvas, double thresh) {
    for (int x = 0 ; x < canvas->width(); x++) {
        for (int y = 0 ; y < canvas->height(); y++) {
            ModifyPixel(x, y, canvas, thresh);
        }
    }
}

#endif
