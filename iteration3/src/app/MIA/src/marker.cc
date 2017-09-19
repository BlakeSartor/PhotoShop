/*******************************************************************************
 * Name            : marker.cc
 * Project         : BrushWork
 * Description     : Implementation of BrushWrok
 * Copyright       : Copyright 2016. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_MARKER_CC
#define INCLUDE_MARKER_CC

/****************************************************************************
includes
****************************************************************************/

#include <cmath>
#include "include/marker.h"
#include "include/tool.h"
#include "include/mask.h"

/****************************************************************************
Constructors/destructors
****************************************************************************/

Marker::Marker() {
    SetMask();
}

Marker::~Marker() {
    delete mask_;
}

/****************************************************************************
member functions
****************************************************************************/

void Marker::SetMask() {
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

void Marker::ApplyMask(int mouse_x, int mouse_y, image_tools::PixelBuffer *canvas,
    image_tools::ColorData active_color) {
    image_tools::ColorData red_color = image_tools::ColorData(1,0,0);
    for (int maskX = 0; maskX < mask_->GetWidth(); maskX++) {
        for (int maskY = 0; maskY < mask_->GetHeight(); maskY++) {
            int applyX = maskX + mouse_x - floor(mask_->GetWidth()/2);
            int applyY = (maskY + mouse_y - floor(mask_->GetHeight()/2));

            // hardcoding difference in baseGFXApp coordinates,
            // and pixel_buffer coordinates
            applyY = canvas->height() - applyY;
            image_tools::ColorData applyColor = red_color *
                mask_->GetOpacity(maskX, maskY)
            + canvas->get_pixel(applyX, applyY) *
                (1 - mask_->GetOpacity(maskX, maskY));
            canvas->set_pixel(applyX, applyY, applyColor);
        }
    }
}
#endif
