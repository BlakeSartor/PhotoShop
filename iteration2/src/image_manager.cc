/*******************************************************************************
 * Name            : image_manager.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W. All rights reserved.
 * Creation Date   : 11/22/16
 * Original Author : Modified by Raghav Mutneja, Blake Sartor, Zechariah Nelson
 *
 ******************************************************************************/

#ifndef INCLUDE_IMAGE_MANAGER_CC
#define INCLUDE_IMAGE_MANAGER_CC

/****************************************************************************
 includes
 ****************************************************************************/

#include "include/image_manager.h"
#include <stdio.h>
#include <string.h>
#include <iostream>


using std::cout;
using std::endl;

/****************************************************************************
 Constructors/destructors
 ****************************************************************************/

ImageManager::ImageManager() {
}

ImageManager::~ImageManager() {
}

/****************************************************************************
 member functions
 ****************************************************************************/

/** This function determintes whether to save image using jpeg
 or png libraries */
void ImageManager::saveimage(const std::string & filename,
  image_tools::PixelBuffer* buffer) {
    if (isjpeg(filename)) {
        savejpg(fopen(filename.c_str(), "wb"),
          buffer -> getHeight(), buffer -> getWidth(), buffer);

    } else if (ispng(filename)) {
        savepng(filename, buffer -> getHeight(), buffer -> getWidth(), buffer);

    } else {
        std::cout << "Error saving image" << std::endl;
    }
}

/** Determines to load image from using jpeg or png libraries */
image_tools::PixelBuffer* ImageManager::loadimage
  (const std::string & filename, int & height, int & width,
  image_tools::ColorData backgroundColor) {
    if (isjpeg(filename)) {
        image_tools::PixelBuffer *newBuffer = loadjpg
          (fopen(filename.c_str(), "rb"), height, width, backgroundColor);
        return newBuffer;

    } else if (ispng(filename)) {
        image_tools::PixelBuffer *newBuffer =
          loadpng(filename, height, width, backgroundColor);
        return newBuffer;

    } else {
        return NULL;
    }
}

/* Saves image using png libraries */
void ImageManager::savepng(const std::string fileName,
  int height, int width, image_tools::PixelBuffer* bufferToSave) {
    png_image image;

    memset(&image, 0, (sizeof image));
    image.height = bufferToSave->getHeight();
    image.width = bufferToSave->getWidth();
    image.version = PNG_IMAGE_VERSION;
    image.opaque = NULL;
    image.format = PNG_FORMAT_RGBA;

    png_bytep buffer = new png_byte[PNG_IMAGE_SIZE(image)];

    for (int y = image.height-1; y >= 0; y--) {
        for (int x = 0; x < image.width; x++) {
            image_tools::ColorData currentPixel = bufferToSave->get_pixel(x, y);
            buffer[((image.height - (y + 1)) * image.width + x) * 4] =
              (png_byte) (currentPixel.getRed() * 255.0);
            buffer[((image.height - (y + 1)) * image.width + x) * 4 + 1] =
              (png_byte) (currentPixel.getGreen() * 255.0);
            buffer[((image.height - (y + 1)) * image.width + x) * 4 + 2] =
              (png_byte) (currentPixel.getBlue() * 255.0);
            buffer[((image.height - (y + 1)) * image.width + x) * 4 + 3] =
              (png_byte) (currentPixel.getAlpha() * 255.0);
        }
    }

    if (png_image_write_to_file(&image, fileName.c_str(), 0,
                                buffer, 0, NULL) != 0) {
    } else {
    }

    delete[] buffer;
    return;
}

/** Loads image using png libraries */
image_tools::PixelBuffer* ImageManager::loadpng(const std::string fileName,
  int &Height, int &Width, image_tools::ColorData backgroundColor) {
    image_tools::PixelBuffer* loadedImageBuffer = NULL;

    png_image image;
    memset(&image, 0, (sizeof image));
    image.version = PNG_IMAGE_VERSION;

    if (png_image_begin_read_from_file(&image, fileName.c_str())) {
        loadedImageBuffer = new image_tools::PixelBuffer
          (image.width, image.height, image_tools::ColorData(0.0, 0.0, 0.0));

        png_bytep buffer;
        image.format = PNG_FORMAT_RGBA;
        buffer = new png_byte[PNG_IMAGE_SIZE(image)];
        Height = image.height;
        Width = image.width;
        if (buffer && png_image_finish_read(&image, NULL, buffer, 0, NULL)) {
            for (int y = 0; y < static_cast<int>(image.height); y++) {
                for (int x = 0; x < static_cast<int>(image.width); x++) {
                    int r, g, b, a = 0;
                    r = static_cast<int>(buffer[(y * image.width * 4)
                        + (x * 4)]);
                    g = static_cast<int>(buffer[(y * image.width * 4)
                        + (x * 4) + 1]);
                    b = static_cast<int>(buffer[(y * image.width * 4)
                        + (x * 4) + 2]);
                    a = static_cast<int>(buffer[(y * image.width * 4)
                        + (x * 4) + 3]);
                    loadedImageBuffer->set_pixel(x, image.height - (y + 1),
                      image_tools::ColorData
                      (r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f));
                }
            }
        }

        delete[] buffer;
    }

    return loadedImageBuffer;
}

/** Loads image using jpeg libraries */
image_tools::PixelBuffer* ImageManager::loadjpg(FILE* infile,
    int& Height, int& Width, image_tools::ColorData backgroundColor) {
    double r, g, b;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    if (infile == NULL) {
        perror("fopen fail");
        return 0;
    }

    jpeg_stdio_src(&cinfo, infile);
    (void)jpeg_read_header(&cinfo, TRUE);
    cinfo.out_color_space = JCS_RGB;
    (void)jpeg_start_decompress(&cinfo);
    JSAMPARRAY pJpegBuffer;

    int row_stride = cinfo.output_width * cinfo.output_components;
    pJpegBuffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo,
        JPOOL_IMAGE, row_stride, 1);
    Height = cinfo.output_height;
    Width = cinfo.output_width;
    image_tools::PixelBuffer* newBuffer =
        new image_tools::PixelBuffer(Width, Height, backgroundColor);

    while (cinfo.output_scanline < cinfo.output_height) {
        (void)jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
        for (int x = 0; x < Width; x++) {
            r = pJpegBuffer[0][cinfo.output_components * x];
            if (cinfo.output_components > 2) {
                g = pJpegBuffer[0][cinfo.output_components * x + 1];
                b = pJpegBuffer[0][cinfo.output_components * x + 2];
            } else {
                g = r;
                b = r;
            }
            newBuffer->set_pixel(static_cast<int>(x),
              (Height - cinfo.output_scanline),
                image_tools::ColorData(r / 255, g / 255, b / 255));
        }
    }
    fclose(infile);
    (void)jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    return newBuffer;
}

/** Saves image using jpeg libraries */
void ImageManager::savejpg(FILE* outfile, int Height,
  int Width, image_tools::PixelBuffer* bufferToSave) {
    struct jpeg_compress_struct cinfo;

    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    int row_stride;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = bufferToSave->getWidth();
    cinfo.image_height = bufferToSave->getHeight();
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, 100, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    row_stride = cinfo.image_width * 3;

    const int width = bufferToSave->getWidth();
    const int height = bufferToSave->getHeight();
    JSAMPLE* image_buffer = new JSAMPLE[row_stride*cinfo.image_height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image_tools::ColorData currentPixel = bufferToSave->get_pixel(x, y);
            image_buffer[((height - (y + 1)) * width + x) * 3] =
              (JSAMPLE) (currentPixel.getRed() * 255.0);
            image_buffer[((height - (y + 1)) * width + x) * 3 + 1] =
              (JSAMPLE) (currentPixel.getGreen() * 255.0);
            image_buffer[((height - (y + 1)) * width + x) * 3 + 2] =
              (JSAMPLE) (currentPixel.getBlue() * 255.0);
        }
    }

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    delete[] image_buffer;


    jpeg_finish_compress(&cinfo);
    fclose(outfile);

    jpeg_destroy_compress(&cinfo);
}

/** Returns true if image has suffix .jpg or .jpeg */
bool ImageManager::isjpeg(const std::string & name) {
    return hasSuffix(name, ".jpg")|| hasSuffix(name, ".jpeg");
}

/** Returns true if png has suffix png */
bool ImageManager::ispng(const std::string & name) {
    return hasSuffix(name, ".png");
}

/** Returns true if image has a suffix */
bool ImageManager::hasSuffix(const std::string & str,
    const std::string & suffix) {
  return str.find(suffix, str.length()-suffix.length()) != std::string::npos;
}

#endif
