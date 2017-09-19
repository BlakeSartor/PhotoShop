/*******************************************************************************
 * Name            : highlighter.h
 * Project         : BrushWork
 * Description     : Implementation of BrushWrok
 * Copyright       : Copyright 2016. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Raghav Mutneja
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_HIGHLIGHTER_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_HIGHLIGHTER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "tool.h"
#include "mask.h"

/*******************************************************************************
 * Class Declaration
 ******************************************************************************/

class Highlighter : public Tool {
 public:
    Highlighter();
    explicit Highlighter(image_tools::PixelBuffer *canvas);
    ~Highlighter();
    void virtual SetMask();
    void virtual ApplyMask(int mouse_x, int mouse_y,
        image_tools::PixelBuffer *canvas, image_tools::ColorData active_color);
 private:
    void UpdateMousePositions(int mouse_x, int mouse_y,
        image_tools::PixelBuffer *canvas);
    int RecentlyDrawn(int pixel_x, int pixel_y,
        image_tools::PixelBuffer *canvas);
    int last_x_[25];
    int last_y_[25];
    Mask *global_mask_;
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_HIGHLIGHTER_H_
