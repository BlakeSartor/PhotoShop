/*******************************************************************************
 * Name            : highlighter.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/19/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_HIGHLIGHTER_CC
#define INCLUDE_HIGHLIGHTER_CC

/****************************************************************************
includes
****************************************************************************/

#include <stdio.h>
#include <cmath>
#include "include/highlighter.h"
#include "include/tool.h"
#include "include/mask.h"

/****************************************************************************
Constructors/destructors
****************************************************************************/

Highlighter::Highlighter() {
    SetMask();
}

Highlighter::Highlighter(image_tools::PixelBuffer *canvas) {
    SetMask();

    // Initialize global mask, used to keep track of what pixels
    // have recently been affected
    global_mask_ = new Mask(canvas->width(), canvas->height());
    for (int x = 0; x < canvas->width(); x++) {
        for (int y = 0; y < canvas->height(); y++) {
            global_mask_->SetOpacity(x, y, 0);
        }
    }

    // initializing previous mouse positions to impossible points this way
    // it will never assume places have been recently drawn on incorrectly
    for (int i = 0; i < 25; i++) {
        last_x_[i] == -512;
        last_y_[i] == -512;
    }
}

Highlighter::~Highlighter() {
    delete mask_;
}

/****************************************************************************
member functions
****************************************************************************/

// Checks to see if pixel has been touched in the last 10 calls of ApplyMask
int Highlighter::RecentlyDrawn(int pixel_x, int pixel_y,
    image_tools::PixelBuffer *canvas) {
        if (global_mask_->GetOpacity(pixel_x, pixel_y) != 0) {
            return 1;
        }
        return 0;
}

// Updates list of previous mouse positions and adds the mask of the most recent
// to the global mask, and removes the least recent
void Highlighter::UpdateMousePositions(int mouse_x, int mouse_y,
    image_tools::PixelBuffer *canvas) {

        for (int maskX = 0; maskX < mask_->GetWidth(); maskX++) {
            for (int maskY = 0; maskY < mask_->GetHeight(); maskY++) {
                int applyX = maskX + last_x_[0] - floor(mask_->GetWidth()/2);
                int applyY = (maskY + last_y_[0] - floor(mask_->GetHeight()/2));

                // hardcoding difference in baseGFXApp coordinates,
                // and pixel_buffer coordinates
                applyY = canvas->height() - applyY;

                global_mask_->SetOpacity(applyX, applyY, 0);
            }
        }

        for (int i = 0; i < 24; i++) {
            last_x_[i] = last_x_[i+1];
            last_y_[i] = last_y_[i+1];
        }
        last_x_[24] = mouse_x;
        last_y_[24] = mouse_y;

        for (int maskX = 0; maskX < mask_->GetWidth(); maskX++) {
            for (int maskY = 0; maskY < mask_->GetHeight(); maskY++) {
                int applyX = maskX + mouse_x - floor(mask_->GetWidth()/2);
                int applyY = (maskY + mouse_y - floor(mask_->GetHeight()/2));

                // hardcoding difference in baseGFXApp coordinates,
                // and pixel_buffer coordinates
                applyY = canvas->height() - applyY;

                global_mask_->SetOpacity(applyX, applyY, 1);
            }
        }
}

void Highlighter::ApplyMask(int mouse_x, int mouse_y,
    image_tools::PixelBuffer *canvas, image_tools::ColorData active_color) {

        for (int maskX = 0; maskX < mask_->GetWidth(); maskX++) {
            for (int maskY = 0; maskY < mask_->GetHeight(); maskY++) {
                int applyX = maskX + mouse_x - floor(mask_->GetWidth()/2);
                int applyY = (maskY + mouse_y - floor(mask_->GetHeight()/2));

                // hardcoding difference in baseGFXApp coordinates,
                // and pixel_buffer coordinates
                applyY = canvas->height() - applyY;
                image_tools::ColorData applyColor =
                    active_color * mask_->GetOpacity(maskX, maskY)
                + canvas->get_pixel(applyX, applyY) *
                    (1 - mask_->GetOpacity(maskX, maskY));

                // Only draws if pixel has not been changed recently
                if (RecentlyDrawn(applyX, applyY, canvas) == 0) {
                    canvas->set_pixel(applyX, applyY, applyColor);
                }
            }
        }
        UpdateMousePositions(mouse_x, mouse_y, canvas);
}

void Highlighter::SetMask() {
    int height = 5;
    int width = 15;
    mask_ = new Mask(height, width);
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            mask_->SetOpacity(x, y, 0.4);
        }
    }
}

#endif
