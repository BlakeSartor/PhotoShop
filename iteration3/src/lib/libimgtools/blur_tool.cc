/*!******************************************************************************
 * Name            : blur_tool.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/17/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef BLUR_TOOL_CC
#define BLUR_TOOL_CC

/**************************************************************************//**
* includes
****************************************************************************/

#include "include/blur_tool.h"
#include <cmath>
#include "include/tool.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"
#include "include/mask.h"

/**************************************************************************//**
* constructors/destructors
****************************************************************************/

BlurTool::BlurTool() {
    //! A Constructor */
    SetMask();
}

BlurTool::~BlurTool() {
    //! A Destructor */
    delete mask_;
    delete kernal_;
}

/**************************************************************************//**
* member functions
****************************************************************************/

void BlurTool::SetMask() {
    int size = 11;
    int center = 5;
    /*! Set up the tool mask and the blur kernal.
        \By default, these are the same size.
    */
    mask_ = new Mask(11, 11);
    kernal_ = new Mask(11, 11);

    for (int x = 0; x < size; x ++) {
        for (int y = 0; y < size; y ++) {
            /*! Calculate the distance from pixel (x,y) to center of mask. */
            double distance = sqrt(pow(center - x, 2) + pow(center - y, 2));

            double opacity = center - distance;  // sets up opacity
            if (opacity < 0) {  
                /*! if opacity is negative, makes it zero. */
                opacity = 0;
            }

            /*! Sets both masks to be equal to the calculated opacity. */
            mask_->SetOpacity(x, y, opacity);
            kernal_->SetOpacity(x, y, opacity);
        }
    }
}

void BlurTool::ApplyMask(int mouse_x, int mouse_y,
        image_tools::PixelBuffer *canvas,
        image_tools::ColorData active_color) {
    /*! creates a new canvas, so, blurs don't affect each other. */
    old_canvas_ = new image_tools::PixelBuffer(*canvas);

    /*! assumes mask is square, so, one int is
       \used for the horizontal, and vertical center. 
    */
    int center = floor(mask_->GetWidth() / 2);

    /*! loops through every pixel in mask_ */
    for (int mask_x = 0; mask_x < mask_->GetWidth(); mask_x++) {
        for (int mask_y = 0; mask_y < mask_->GetHeight(); mask_y++) {
            int apply_x = mouse_x + mask_x - center;
            int apply_y = mouse_y + mask_y - center;
            /*! hardcode difference in buffer coordinates, and mouse coordinates. */
            apply_y = canvas->height() - apply_y;
            /*! makes sure pixel to modify is within bounds of canvas. */
            if (apply_y >= 0 && apply_x >= 0 && apply_y < canvas->height()
              && apply_x < canvas->width()) {
                /*! calculates new color. */
                image_tools::ColorData new_color
                    = ApplyKernal(apply_x, apply_y, old_canvas_);
                float alpha = mask_->GetOpacity(mask_x, mask_y);
                if (alpha > 1.0) alpha = 1.0;
                if (alpha < 0.0) alpha = 0.0;
                new_color = (new_color * alpha)
                    + (canvas->get_pixel(apply_x, apply_y) * (1 - alpha));

                if (new_color.getRed() > 1.0) new_color.red(1.0);
                if (new_color.getRed() < 0.0) new_color.red(0.0);
                if (new_color.getBlue() > 1.0) new_color.blue(1.0);
                if (new_color.getBlue() < 0.0) new_color.blue(0.0);
                if (new_color.getGreen() > 1.0) new_color.green(1.0);
                if (new_color.getGreen() < 0.0) new_color.green(0.0);

                /*! sets canvas pixel to that color. */
                canvas->set_pixel(apply_x, apply_y, new_color);
            }
        }
    }
    delete old_canvas_;
}

image_tools::ColorData
  BlurTool::ApplyKernal(int x, int y, image_tools::PixelBuffer *canvas) {
    image_tools::ColorData new_color(0, 0, 0);
    float divisor = 0;
    int center_x = floor(kernal_->GetWidth() / 2);
    int center_y = floor(kernal_->GetHeight() / 2);

    for (int mask_x = 0; mask_x < kernal_->GetWidth(); mask_x++) {
        for (int mask_y = 0; mask_y < kernal_->GetHeight(); mask_y++) {
            int apply_x = x + mask_x - center_x;
            int apply_y = y + mask_y - center_y;

            /*! checks if pixel is in bounds. */
            if (apply_x >= 0 && apply_y >= 0 && apply_x < canvas->width()
                && apply_y < canvas->height()) {
              divisor += kernal_->GetOpacity(mask_x, mask_y);
                new_color = new_color + (canvas->get_pixel(apply_x, apply_y)
                * kernal_->GetOpacity(mask_x, mask_y));
            }
        }
    }
    if (divisor != 0) {new_color = new_color * (1 / divisor);}

    /*! checks if color is in bounds. */
    if (new_color.getRed() > 1.0) new_color.red(1.0);
    if (new_color.getRed() < 0.0) new_color.red(0.0);
    if (new_color.getGreen() > 1.0) new_color.green(1.0);
    if (new_color.getGreen() < 0.0) new_color.green(0.0);
    if (new_color.getBlue() > 1.0) new_color.blue(1.0);
    if (new_color.getBlue() < 0.0) new_color.blue(0.0);

    return new_color;
}

#endif
