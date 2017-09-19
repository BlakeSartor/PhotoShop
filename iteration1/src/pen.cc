/*******************************************************************************
 * Name            : pen.cc
 * Project         : BrushWork
 * Description     : Implementation of BrushWrok
 * Copyright       : Copyright 2016. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_PEN_CC
#define INCLUDE_PEN_CC

/****************************************************************************
includes
****************************************************************************/

#include <cmath>
#include "include/pen.h"
#include "include/tool.h"
#include "include/mask.h"

/****************************************************************************
Constructors/destructors
****************************************************************************/

Pen::Pen() {
    SetMask();
}

Pen::~Pen() {
    delete mask_;
}

/****************************************************************************
member functions
****************************************************************************/

void Pen::SetMask() {
    int size = 3;
    int center = floor(size/2);
    mask_ = new Mask(size, size);
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            int withinRadius = (sqrt(pow(center-x, 2) + pow(center - y, 2))
                <= center);
            mask_->SetOpacity(x, y, withinRadius);
        }
    }
}

#endif
