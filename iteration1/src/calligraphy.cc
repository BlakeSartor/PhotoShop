/*******************************************************************************
 * Name            : calligraphy.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/19/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_CALLIGRAPHY_CC
#define INCLUDE_CALLIGRAPHY_CC

/****************************************************************************
includes
****************************************************************************/
#include <cmath>
#include "include/calligraphy.h"
#include "include/tool.h"
#include "include/mask.h"

/****************************************************************************
Constructors/destructors
****************************************************************************/
Calligraphy::Calligraphy() {
  SetMask();
}
Calligraphy::~Calligraphy() {
  delete mask_;
}

/****************************************************************************
member functions
****************************************************************************/

void Calligraphy::SetMask() {
  int height = 15;
  int width = 5;
  mask_ = new Mask(width, height);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
        mask_->SetOpacity(x, y, 1);
    }
  }
}

#endif
