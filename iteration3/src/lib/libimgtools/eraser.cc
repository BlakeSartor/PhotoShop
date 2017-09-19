/*******************************************************************************
 * Name            : eraser.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 10/19/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_ERASER_CC
#define INCLUDE_ERASER_CC

/**************************************************************************//**
* includes
****************************************************************************/

#include <cmath>
#include "include/eraser.h"
#include "include/tool.h"
#include "include/mask.h"

/**************************************************************************//**
* Constructors/destructors
****************************************************************************/
Eraser::Eraser() {
    //! A Constructor */
    SetMask();
}
Eraser::~Eraser() {
    //! A Destructor */
    delete mask_;
}

/**************************************************************************//**
* member functions
****************************************************************************/

void Eraser::SetMask() {
    int size = 21;  
    /*! the diameter of the eraser, its a circular one. */
    int center = floor(size/2);
    mask_ = new Mask(size, size);
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            int withinRadius = (sqrt(pow(x - center, 2) + pow(y - center, 2))
                <= center);  /*! returns either 1 or 0. */
            mask_->SetOpacity(x, y, withinRadius);
        }
    }
}

void Eraser::ApplyMask(int mouse_x, int mouse_y,
    image_tools::PixelBuffer *canvas,
    image_tools::ColorData active_color) {
        for (int maskX = 0; maskX < mask_->GetWidth(); maskX++) {
            for (int maskY = 0; maskY < mask_->GetHeight(); maskY++) {
                int applyX = maskX + mouse_x - floor(mask_->GetWidth()/2);
                int applyY = (maskY + mouse_y - floor(mask_->GetHeight()/2));

                /*! hardcoding difference in baseGFXApp coordinates,
                    \and pixel_buffer coordinates 
                 */
                applyY = canvas->height() - applyY;
                image_tools::ColorData applyColor =
                    canvas->background_color() *
                    mask_->GetOpacity(maskX, maskY)
                    + canvas->get_pixel(applyX, applyY) *
                    (1 - mask_->GetOpacity(maskX, maskY));
                canvas->set_pixel(applyX, applyY, applyColor);
            }
        }
}

#endif
