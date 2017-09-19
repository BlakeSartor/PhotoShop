/*******************************************************************************
 * Name            : highlighter.h
 * Project         : BrushWork
 * Description     : Implementation of BrushWrok
 * Copyright       : Copyright 2016. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_IMAGE_MANAGER_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_IMAGE_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <png.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <string>
#include <cstdlib>
#include "pixel_buffer.h"
#include "color_data.h"

/*******************************************************************************
 * Class Declaration
 ******************************************************************************/

class ImageManager{
 public :
    ImageManager();
    ~ImageManager();
    image_tools::PixelBuffer* loadimage(const std::string & filename,
        int &height, int &width, image_tools::ColorData backgroundColor);
    void saveimage(const std::string & filename,
    image_tools::PixelBuffer *buffer);
 private :
    bool isjpeg(const std::string & name);
    bool ispng(const std::string & name);
    bool isValidImageFileName(const std::string & name);
    bool isValidFile(const std::string & name);
    bool hasSuffix(const std::string & str, const std::string & suffix);
    void savepng(const std::string fileName, int height, int width,
        image_tools::PixelBuffer *buffer);
    void savejpg(FILE* infile, int height, int width,
        image_tools::PixelBuffer *buffer);
    image_tools::PixelBuffer* loadpng(const std::string fileName, int &height,
        int &width, image_tools::ColorData backgroundColor);
    image_tools::PixelBuffer* loadjpg(FILE *infile, int &height, int &width,
        image_tools::ColorData backgroundColor);
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_IMAGE_MANAGER_H_
