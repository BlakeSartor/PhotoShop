/*******************************************************************************
 * Name            : mia_filter_manager.cc
 * Project         : MIA
 * Module          : filter_manager
 * Description     : Implementation of MIAFilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:47:02 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/app/MIA/src/mia_filter_manager.h"
#include "iostream"
#include "GL/glui.h"
#include "pixel_buffer.h"
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
#include "color_data.h"
#include "edge_detection.h"
#include "special_filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAFilterManager::MIAFilterManager(void) :
    FilterManager() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void FilterManager::ApplySaturate(PixelBuffer *canvas, float amount) {
  std::cout << "Apply has been clicked for Saturate with amount = "
            << saturation_amount_ << std::endl;
    saturation_->ApplyFilter(canvas, amount);
}

void FilterManager::ApplyBlur(PixelBuffer *canvas, float amount) {
  std::cout << "Apply has been clicked for Blur with amount = "
            << blur_amount_ << std::endl;
    blur_->ApplyFilter(canvas, amount);
}

void FilterManager::ApplySharpen(PixelBuffer *canvas, float amount) {
  std::cout << "Apply has been clicked for Sharpen with amount = "
            << sharpen_amount_ << std::endl;
    sharpen_->ApplyFilter(canvas, amount);
}

void FilterManager::ApplyEdgeDetect(PixelBuffer *canvas) {
  std::cout << "Apply has been clicked for Edge Detect" << std::endl;
    edge_detection_->ApplyFilter(canvas);
}

void FilterManager::ApplyQuantize(PixelBuffer *canvas, int bins) {
  std::cout << "Apply has been clicked for Quantize with bins = "
            << quantize_bins_ << std::endl;
    quantize_->ApplyFilter(canvas, bins);
}
void FilterManager::ApplyThreshold(PixelBuffer *canvas, float thresh) {
  std::cout << "Apply Threshold has been clicked with amount ="
            << threshold_amount_ << std::endl;
    threshold_->ApplyFilter(canvas, thresh);
}
void FilterManager::ApplyChannels(PixelBuffer *canvas, float red, float green, float blue){
  rgb_levels_->ApplyFilter(canvas, red, green, blue);
}
GLUI_Panel* MIAFilterManager::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *filter_panel = new GLUI_Panel(const_cast<GLUI*>(glui), "Filters");
  {
    AddSharpenToGLUI(filter_panel, s_gluicallback);
    AddEdgeDetectToGLUI(filter_panel, s_gluicallback);
    AddThresholdToGLUI(filter_panel, s_gluicallback);
    AddBlurToGLUI(filter_panel, s_gluicallback);

    new GLUI_Column(filter_panel, true);
    // AddSaturationToGLUI(filter_panel, s_gluicallback);
    {
      GLUI_Panel *satur_panel = new GLUI_Panel(filter_panel, "Grayscale");

      new GLUI_Button(satur_panel, "Apply",
      UICtrl::UI_APPLY_SATURATE,
      s_gluicallback);
    }
    AddChannelToGLUI(filter_panel, s_gluicallback);
    AddQuantizationToGLUI(filter_panel, s_gluicallback);
  }

  return filter_panel;
} /* MIAFilterManager::InitGlui() */

}  /* namespace image_tools */
