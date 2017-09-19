/*******************************************************************************
 * Name            : mask.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/19/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef MASK_CC
#define MASK_CC

/****************************************************************************
includes
****************************************************************************/
#include <iostream>
#include "include/mask.h"

/****************************************************************************
class definitions
****************************************************************************/

Mask::Mask(void) {
}

Mask::Mask(int x, int y) {
    width_ = x;
    height_ = y;
    // building array
    opacity_ =  new double*[width_];
    for (int column = 0; column < width_; column++) {
        opacity_[column] = new double[height_];
    }
}

Mask::~Mask() {
}

void Mask::SetOpacity(int x, int y, double value) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        opacity_[x][y] = value;
    }
}

double Mask::GetOpacity(int x, int y) {
    if (x < width_ && x >= 0 && y < height_ && y >= 0) {
        return opacity_[x][y];
    }
}

int Mask::GetWidth() {
    return width_;
}

int Mask::GetHeight() {
    return height_;
}

#endif
