/*******************************************************************************
 * Name            : pen.h
 * Project         : BrushWork
 * Description     : Implementation of BrushWrok
 * Copyright       : Copyright 2016. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_PEN_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_PEN_H_

/****************************************************************************
includes
****************************************************************************/

#include "include/tool.h"
#include "include/mask.h"

/****************************************************************************
class declaration
****************************************************************************/

class Pen : public Tool {
 public:
    Pen();
    ~Pen();
    void virtual SetMask();
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_PEN_H_
