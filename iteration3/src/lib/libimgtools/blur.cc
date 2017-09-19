/*!******************************************************************************
 * Name            : blur.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/14/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef BLUR_CC
#define BLUR_CC

/**************************************************************************//**
* includes
****************************************************************************/

#include "include/blur.h"
#include <cmath>
#include <iostream>
#include "include/filter.h"
#include "include/convolution_filter.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/**************************************************************************//**
* function definitions
****************************************************************************/

Blur::Blur() {
    //! A Constructor */
    kernal_ = NULL;
}

Blur::~Blur() {
    //! A Destructor */
    if (kernal_ != NULL) {
        delete kernal_;
    }
}

/**************************************************************************//**
* function definitions
****************************************************************************/

void Blur::SetMask() {
    /*! Creating new mask for Blur Filter */
    if (kernal_ != NULL) {
        delete kernal_;
    }
    kernal_ = new Mask(5, 5);
}

void Blur::SetMask(int size) {
    if (kernal_ != NULL) {
        delete kernal_;
    }
    /*! The algorithm which the mask uses to create the Blur effect. */
    kernal_ = new Mask(size, size);
    int center = floor(size / 2);
    std::cout << "new mask is:\n";
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            int withinRadius = (sqrt(pow(center - x, 2)
                + pow(center - y, 2)) <= center);
            kernal_->SetOpacity(x, y, withinRadius);
            std::cout << kernal_->GetOpacity(x, y) << "\t";
        }
        std::cout << "\n";
    }
}

#endif
