/*******************************************************************************
 * Name            : marker.h
 * Project         : BrushWork
 * Description     : Implementation of BrushWrok
 * Copyright       : Copyright 2016. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_MARKER_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_MARKER_H_

/****************************************************************************
includes
****************************************************************************/

#include "tool.h"
#include "mask.h"

/****************************************************************************
class declaration
****************************************************************************/

class Marker : public Tool {
 public:
    Marker();
    ~Marker();
    void virtual SetMask();
    void ApplyMask(int mouse_x, int mouse_y, image_tools::PixelBuffer *canvas,
    	image_tools::ColorData active_color);
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_MARKER_H_
