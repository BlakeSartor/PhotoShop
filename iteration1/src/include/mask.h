/*******************************************************************************
 * Name            : mask.h
 * Project         : BrushWork
 * Description     : Implementation of BrushWrok
 * Copyright       : Copyright 2016. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/


#ifndef PROJECT_ITERATION1_SRC_INCLUDE_MASK_H_
#define PROJECT_ITERATION1_SRC_INCLUDE_MASK_H_

/****************************************************************************
class definitions
****************************************************************************/

class Mask {
 public:
    Mask();
    Mask(int x, int y);
    void SetOpacity(int x, int y, double value);
    double GetOpacity(int x, int y);
    int GetWidth();
    int GetHeight();
    virtual ~Mask();
 private:
    int width_;
    int height_;
    double **opacity_;
};


#endif  // PROJECT_ITERATION1_SRC_INCLUDE_MASK_H_
