/*******************************************************************************
* Name            : stamp.h
* Project         : FlashPhoto
* Description     : Implementation of BrushWrok
* Copyright       : Copyright 2016. All rights reserved.
* Creation Date   : 11/22/16
* Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
*
******************************************************************************/


#ifndef PROJECT_ITERATION2_SRC_INCLUDE_STAMP_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_STAMP_H_

#include "include/pixel_buffer.h"
#include "include/color_data.h"
#include "include/tool.h"


class Stamp : public Tool {
 public:
    Stamp();
    ~Stamp();
    void applyStamp(int x, int y, image_tools::PixelBuffer* canvas,
        image_tools::PixelBuffer* stamp);
    void LoadStamp(image_tools::PixelBuffer* new_mask);
    // std::String getName();
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_STAMP_H_
