/*******************************************************************************
 * Name            : blur_tool.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/17/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_BLUR_TOOL_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_BLUR_TOOL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "color_data.h"
#include "pixel_buffer.h"
#include "tool.h"
#include "mask.h"

 /*******************************************************************************
 * Class Definitions
 ******************************************************************************/

class BlurTool : public Tool {
 public:
    BlurTool();
    ~BlurTool();
    void SetMask();
    void ApplyMask(int mouse_x, int mouse_y,
      image_tools::PixelBuffer *canvas, image_tools::ColorData active_color);
    image_tools::ColorData
      ApplyKernal(int buffer_x, int buffer_y, image_tools::PixelBuffer *canvas);
 protected:
    image_tools::PixelBuffer *old_canvas_;
    Mask *kernal_;
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_BLUR_TOOL_H_
