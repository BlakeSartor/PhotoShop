/*******************************************************************************
 * Name            : spray_can.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/19/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_SPRAY_CAN_CC
#define INCLUDE_SPRAY_CAN_CC

/**************************************************************************//**
* includes
****************************************************************************/

#include <cmath>
#include "include/spray_can.h"
#include "include/tool.h"
#include "include/mask.h"

/**************************************************************************//**
* Constructors/destructors
****************************************************************************/
SprayCan::SprayCan() {
    //! A Constructor */
    SetMask();
}

SprayCan::~SprayCan() {
    //! A Destructor */
    delete mask_;
}

/**************************************************************************//**
* member functions
****************************************************************************/

void SprayCan::SetMask() {
    /*! Sets mask for Spray Can. */
    int size = 41;
    int center = floor(size/2);
    mask_ = new Mask(size, size);
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            /*! calculates distance of a point (x1,y1) from the center(x,y) */
            double distanceFromCenter = (sqrt(pow(center-x, 2)
                + pow(center-y, 2))*0.01);

            /*! we subtract the value from 0.2 i.e 20% color at the center. */
            mask_->SetOpacity(x, y, 0.2-distanceFromCenter);

            /*! we have to make sure opacity is never negative. */
            if (mask_->GetOpacity(x, y) < 0) {
                mask_->SetOpacity(x, y, 0);
            }
        }
    }
}

#endif
