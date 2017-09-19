/*******************************************************************************
 * Name            : motion_blur.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/15/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef MOTION_BLUR_CC
#define MOTION_BLUR_CC

/****************************************************************************
includes
****************************************************************************/

#include "include/motion_blur.h"
#include <cmath>
#include "include/filter.h"
#include "include/convolution_filter.h"
#include "include/pixel_buffer.h"
#include "include/color_data.h"
#include "include/ui_ctrl.h"

/****************************************************************************
constructors/destructors
****************************************************************************/

MotionBlur::MotionBlur() {
    kernal_ = NULL;
}

MotionBlur::~MotionBlur() {
    if (kernal_ != NULL) {
        delete kernal_;
    }
}

/****************************************************************************
function definitions
****************************************************************************/

void MotionBlur::SetMask() {
}

void MotionBlur::SetMask(int size,
  enum image_tools::UICtrl::MotionBlurDirection direction) {
    if (kernal_ != NULL) {
        delete kernal_;
}
    kernal_ = new Mask(size, size);
    int center = floor(size / 2);
    switch (direction) {
        case image_tools::UICtrl::UI_DIR_N_S :
            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    kernal_->SetOpacity(x, y, 0);
                }
                kernal_->SetOpacity(center, x, 1);
            }
            break;

        case image_tools::UICtrl::UI_DIR_E_W :
            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    kernal_->SetOpacity(x, y, 0);
                }
                kernal_->SetOpacity(x, center, 1);
            }
            break;

        case image_tools::UICtrl::UI_DIR_NE_SW :
            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    kernal_->SetOpacity(x, y, 0);
                }
                kernal_->SetOpacity(x, x, 1);
            }
            break;

        case image_tools::UICtrl::UI_DIR_NW_SE :
            for (int x = 0; x < size; x++) {
                for (int y = 0; y < size; y++) {
                    kernal_->SetOpacity(x, y, 0);
                }
                kernal_->SetOpacity(x, size - x - 1, 1);
            }
            break;

        default :
            break;
            // ERROR
    }
}

#endif
