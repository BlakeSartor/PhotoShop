/*******************************************************************************
 * Name            : sharpen.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/14/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef SHARPEN_CC
#define SHARPEN_CC

/****************************************************************************
includes
****************************************************************************/

#include "include/sharpen.h"
#include <cmath>
#include "include/filter.h"
#include "include/convolution_filter.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/****************************************************************************
constructors/destructors
****************************************************************************/

Sharpen::Sharpen() {
    kernal_ = NULL;
}

Sharpen::~Sharpen() {
    if (kernal_ != NULL) {
        delete kernal_;
    }
}

/****************************************************************************
function definitions
****************************************************************************/

void Sharpen::SetMask() {
    if (kernal_ != NULL) {
        delete kernal_;
    }
    kernal_ = new Mask(5, 5);
}

void Sharpen::SetMask(int size) {
    if (kernal_ != NULL) {
        delete kernal_;
    }
    kernal_ = new Mask(size, size);
    int center = floor(size/2);
    int sum = 0;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            int radius = (sqrt(pow(center - x, 2)
              + pow(center - y, 2)) <= center);
            kernal_->SetOpacity(x, y, - radius);
            sum += radius;
        }
    }
    kernal_->SetOpacity(center, center, sum + 1);
}

#endif
