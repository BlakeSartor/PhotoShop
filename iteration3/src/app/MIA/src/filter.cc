/*******************************************************************************
 * Name            : filter.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/05/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_FILTER_CC
#define INCLUDE_FILTER_CC

/****************************************************************************
includes
****************************************************************************/

#include "include/filter.h"
#include <cmath>
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/***************************************************************************
constructors / destructors
****************************************************************************/

Filter::Filter() {
}

Filter::~Filter() {
}

/****************************************************************************
Function Definitions
****************************************************************************/

void Filter::ApplyFilter(image_tools::PixelBuffer *canvas) {
    for (int x = 0; x++; x < canvas->width()) {
        for (int y = 0; y++; y < canvas->height()) {
            ModifyPixel(x, y, canvas);
        }
    }
}

#endif
