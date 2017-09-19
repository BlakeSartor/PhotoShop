/*******************************************************************************
 * Name            : edge_detection.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/20/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_EDGE_DETECTION_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_EDGE_DETECTION_H_

/****************************************************************************
includes
****************************************************************************/

#include "filter.h"
#include "convolution_filter.h"
#include "pixel_buffer.h"
#include "color_data.h"

/****************************************************************************
class definitions
****************************************************************************/

class EdgeDetection : public ConvolutionFilter {
 public:
    EdgeDetection();
    ~EdgeDetection();
    void SetMask();
    // void SetMask(int size);
 protected:
};

#endif  //  PROJECT_ITERATION2_SRC_INCLUDE_EDGE_DETECTION_H_
