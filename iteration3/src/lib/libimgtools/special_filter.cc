/*******************************************************************************
 * Name            : special_filter.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/20/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef SPECIAL_FILTER_CC
#define SPECIAL_FILTER_CC

/**************************************************************************//**
* includes
****************************************************************************/

#include "include/special_filter.h"
#include <cmath>
#include "include/filter.h"
#include "include/convolution_filter.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/**************************************************************************//**
* constructors/destructors
****************************************************************************/

SpecialFilter::SpecialFilter() {
    //! A Constructor */
    SetMask();
}

SpecialFilter::~SpecialFilter() {
    //! A Destructor */
    if (kernal_ != NULL) {
        delete kernal_;
    }
}

/**************************************************************************//**
* function definitions
****************************************************************************/

void SpecialFilter::SetMask() {
    if (kernal_ != NULL) {
        delete kernal_;
    }
    int size = 9;
    int center = floor(size/2);
    kernal_ = new Mask(size, size);

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            kernal_->SetOpacity(x, y, 0);
        }
    }
    
    kernal_->SetOpacity(center, 0, 1);
    kernal_->SetOpacity(center, size - 1, 1);
}

void SpecialFilter::SetMask(int size) {
    /*! Sets special filter */
    if (kernal_ != NULL) {
        delete kernal_;
}
    kernal_ = new Mask(size, size);
    int center = floor(size / 2);
    int sum = 0;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            int radius = (sqrt(pow(center - x, 2) +
                pow(center - y, 2)) <= center);
            kernal_->SetOpacity(x, y, - radius);
            sum += radius;
        }
    }
}

#endif
