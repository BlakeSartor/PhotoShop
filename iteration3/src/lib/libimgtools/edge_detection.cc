/*******************************************************************************
 * Name            : edge_detection.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/20/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef EDGE_DETECTION_CC
#define EDGE_DETECTION_CC

/**************************************************************************//**
* includes
****************************************************************************/

#include "include/edge_detection.h"
#include <cmath>
#include <iostream>
#include "include/filter.h"
#include "include/convolution_filter.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/**************************************************************************//**
* constructors/destructors
****************************************************************************/

EdgeDetection::EdgeDetection() {
    //! A Constructor */
    SetMask();
}

EdgeDetection::~EdgeDetection() {
    //! A Destructor */
    delete kernal_;
}

/**************************************************************************//**
* function definitions
****************************************************************************/

void EdgeDetection::SetMask() {
    /*! Setting up Mask for Edge Detection. */
    kernal_ = new Mask(3, 3);

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y ++) {
            kernal_->SetOpacity(x, y, 0);
        }
    }
    kernal_->SetOpacity(1, 0, 1);
    kernal_->SetOpacity(1, 1, -1);
}

#endif
