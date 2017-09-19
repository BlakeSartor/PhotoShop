/*******************************************************************************
 * Name            : tool.h
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/19/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_TOOL_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_TOOL_H_

/****************************************************************************
includes
****************************************************************************/

#include "mask.h"
#include "pixel_buffer.h"
#include "color_data.h"

/****************************************************************************
class definitions
****************************************************************************/

class Tool {
 public:
    Tool();
    virtual ~Tool();
    void virtual SetMask();  // SetMask will be defined for each child
    void virtual ApplyMask(int mouse_x, int mouse_y,
        image_tools::PixelBuffer *canvas, image_tools::ColorData active_color);
 protected:
    Mask* mask_;
};


#endif  // PROJECT_ITERATION2_SRC_INCLUDE_TOOL_H_
