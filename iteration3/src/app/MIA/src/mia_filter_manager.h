/*******************************************************************************
 * Name            : mia_filter_manager.h
 * Project         : MIA
 * Module          : filter_manager
 * Description     : Header for MIAFilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef SRC_APP_MIA_SRC_MIA_FILTER_MANAGER_H_
#define SRC_APP_MIA_SRC_MIA_FILTER_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "pixel_buffer.h"
#include "GL/glui.h"
#include "ui_ctrl.h"
#include "blur.h"
#include "filter.h"
#include "convolution_filter.h"
#include "motion_blur.h"
#include "quantize.h"
#include "rgb_levels.h"
#include "saturation.h"
#include "sharpen.h"
#include "threshold.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/


/**
 * @brief Manager for all aspects of filters in FlashPhoto, including
 * initialization of GLUI control elements for filters, filter creation,
 * application, deletion.
 */
class MIAFilterManager : public FilterManager {
 public:
  MIAFilterManager();

 /**
   * @brief Apply a blur filter to the buffer, blurring sharply defined edges
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyBlur(PixelBuffer *canvas, float amount);

  /**
   * @brief Apply a sharpening filter to the buffer, sharpening blurry/undefined
   * edges
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplySharpen(PixelBuffer *canvas, float amount);
  
  /**
   * @brief Apply an edge detection filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyEdgeDetect(PixelBuffer *canvas);

  /**
   * @brief Apply a threshold detection filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyThreshold(PixelBuffer *canvas, float thresh);

  /**
   * @brief Apply a channel filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyChannels(PixelBuffer *canvas, float red, float green, float blue);

  /**
   * @brief Apply a channel filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplySaturate(PixelBuffer *canvas, float amount);


  /**
   * @brief Apply a quantization filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyQuantize(PixelBuffer *canvas, int bins);

  GLUI_Panel* InitGlui(const GLUI *const glui,
                       void (*s_gluicallback)(int));
};

}  /* namespace image_tools */

#endif  /* SRC_APP_MIA_SRC_MIA_FILTER_MANAGER_H_ */
