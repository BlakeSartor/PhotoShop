/*******************************************************************************
 * Name            : tool.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/19/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_TOOL_CC
#define INCLUDE_TOOL_CC

/****************************************************************************
includes
****************************************************************************/

#include <cmath>
#include "include/tool.h"
#include "include/mask.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"

/****************************************************************************
constructors / destructors
****************************************************************************/

Tool::Tool() {
    SetMask();
}

Tool::~Tool() {
    delete mask_;
}

/****************************************************************************
Function Definitions
****************************************************************************/

// Will be defined in each child class
void Tool::SetMask() {
}

void Tool::ApplyMask(int mouse_x, int mouse_y, image_tools::PixelBuffer *canvas,
    image_tools::ColorData active_color) {
        for (int maskX = 0; maskX < mask_->GetWidth(); maskX++) {
            for (int maskY = 0; maskY < mask_->GetHeight(); maskY++) {
                int applyX = maskX + mouse_x - floor(mask_->GetWidth()/2);
                int applyY = (maskY + mouse_y - floor(mask_->GetHeight()/2));

                // hardcoding difference in baseGFXApp coordinates,
                // and pixel_buffer coordinates
                applyY = canvas->height() - applyY;
                image_tools::ColorData applyColor = active_color *
                    mask_->GetOpacity(maskX, maskY)
                + canvas->get_pixel(applyX, applyY) *
                    (1 - mask_->GetOpacity(maskX, maskY));
                canvas->set_pixel(applyX, applyY, applyColor);
            }
        }
}

#endif
