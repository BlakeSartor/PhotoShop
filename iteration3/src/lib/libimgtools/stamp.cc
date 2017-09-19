/*******************************************************************************
 * Name            : stamp.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/22/16
 * Original Author : by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef STAMP_CC
#define STAMP_CC

/**************************************************************************//**
 * includes
 ****************************************************************************/

#include <iostream>
#include "include/pixel_buffer.h"
#include "include/color_data.h"
#include "include/stamp.h"
#include "include/tool.h"


Stamp::Stamp() {
    //! A Constructor */
    mask_ = new Mask(1, 1);
    mask_->SetOpacity(0, 0, 1);
}

Stamp::~Stamp() {
    //! A Destructor */
    delete mask_;
}

/*! makes a mask out of the pixel buffer object passed in as an argument. */
void Stamp::LoadStamp(image_tools::PixelBuffer* new_mask) {
    delete mask_;
    /*! set up dimensions. */
    int height = new_mask->height();
    int width = new_mask->width();
    mask_ = new Mask(width, height);
    float lum;  /*! stamp uses the brightness of each pixel in the image
                    \as the opacity of each pixel in the mask
                */

    for (int x = 0; x < width; x ++) {
        for (int y = 0; y < height; y ++) {
            /*! gets appropriate luminance value from image. */
            lum = new_mask->get_pixel(x, y).luminance();
             /*! sets it as the opacity in the mask */
            mask_->SetOpacity(x, y, lum);
        }
    }
}


/*
std::String Stamp::getName() {
    return "Stamp Tool";
    
}
*/

#endif
