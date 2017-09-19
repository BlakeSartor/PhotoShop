/*******************************************************************************
 * Name            : eraser.h
 * Project         : BrushWork
 * Description     : Implementation of BrushWrok
 * Copyright       : Copyright 2016. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Raghav Mutneja
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_ERASER_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_ERASER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "tool.h"
#include "mask.h"

/*******************************************************************************
 * Class Declaration
 ******************************************************************************/

class Eraser : public Tool{
 public:
    Eraser();
    ~Eraser();
    void virtual SetMask();
    void virtual ApplyMask(int mouse_x, int mouse_y,
        image_tools::PixelBuffer *canvas, image_tools::ColorData active_color);
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_ERASER_H_
