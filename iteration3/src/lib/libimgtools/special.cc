/*******************************************************************************
 * Name            : special.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/19/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_SPECIAL_CC
#define INCLUDE_SPECIAL_CC

/**************************************************************************//**
* includes
****************************************************************************/

#include <cmath>
#include "include/special.h"
#include "include/tool.h"
#include "include/mask.h"

/**************************************************************************//**
* Constructors/destructors
****************************************************************************/
Special::Special() {
    //! A Constructor */
    SetMask();
}

Special::~Special() {
    //! A Destructor */
    delete mask_;
}

/**************************************************************************//**
* member functions
****************************************************************************/

void Special::SetMask() {
    /*! Sets a mask for the Special Filter */
    int height = 11;
    int width = 3;
    int pixel_value = 0;
    mask_ = new Mask(height, width);

    for (int x = 0; x < height; x++) {
        // pixel_value = 1-pixel_value;
        for (int y = 0; y < width; y++) {
            pixel_value = 1-pixel_value;  // rotates between 0 and 1.
            mask_->SetOpacity(x, y, pixel_value);
        }
    }
}

#endif
