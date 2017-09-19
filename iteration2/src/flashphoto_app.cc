/*******************************************************************************
 * Name            : flashphoto_app.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of FlashPhoto
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 11/7/16
 * Original Author : Modified by Blake Sartor
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/flashphoto_app.h"
#include <cmath>
#include <iostream>
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/ui_ctrl.h"
#include "include/tool.h"
#include "include/pen.h"
#include "include/eraser.h"
#include "include/calligraphy.h"
#include "include/highlighter.h"
#include "include/spray_can.h"
#include "include/special.h"
#include "include/blur_tool.h"
#include "include/stamp.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoApp::FlashPhotoApp(int width, int height) : BaseGfxApp(width, height),
                                                      filter_manager_(),
                                                      io_manager_(),
                                                      state_manager_(),
                                                      glui_ctrl_hooks_(),
                                                      display_buffer_(nullptr),
                                                      cur_tool_(0),
                                                      cur_color_red_(0.0),
                                                      cur_color_green_(0.0),
                                                      cur_color_blue_(0.0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void FlashPhotoApp::Init(
    int argc,
    char* argv[],
    int x,
    int y,
    ColorData background_color) {
  BaseGfxApp::Init(argc, argv,
                   x, y,
                   GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                   true,
                   width()+51,
                   50);

  // Set the name of the window
  set_caption("FlashPhoto");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  InitGlui();
  InitGraphics();

  /** Initialize tools */
  InitTools();

  /** Set prev_x, prev_y to default -1 */
  prev_x = -1;
  prev_y = -1;
}

void FlashPhotoApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

FlashPhotoApp::~FlashPhotoApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
  }
}


void FlashPhotoApp::MouseDragged(int x, int y) {
    /** Slope between two points, used with interpolation */
    float slope;

    /** 1 if slope is y/x, 0 if x/y; tells us which slope to use */
    int slopeSwitch;

    /** Current tool applied to pixelBuffer once */
    (*vector_of_tools[cur_tool_]).ApplyMask(x, y, display_buffer_,
        ColorData(cur_color_red_, cur_color_green_, cur_color_blue_));

    /** if previous x and previous y are default; do nothing */
    if ((prev_x == -1) || (prev_y == -1)) {
    } else if ((prev_x != -1) && (prev_y != -1)) {
        if ((prev_x-x) == 0) {
            slopeSwitch = 1;
            slope = 0;
        } else {
            slope = static_cast<float>(-1.0*(prev_y - y)/(prev_x - x));
            slopeSwitch = 0;

            if ((slope > 1) || (slope < -1 )) {
                slope = 1.0/slope;
                slopeSwitch = 1;
        }
    }

    Interpolate(x, y, prev_x, prev_y, slope, slopeSwitch);

    /** set previous x and previous y to current */
    prev_x = x;
    prev_y = y;
    }
}
/** This function connects two sets of coordinates
by stepping along a straight line between them */
void FlashPhotoApp::Interpolate(int x, int y, int prev_x, int prev_y,
  float slope, int slopeSwitch) {
    int interp_size;
    int next_y;

    if (cur_tool_ == 2) {
        interp_size = 5;

    } else if (cur_tool_ == 4) {
        interp_size = 4;

    } else if (cur_tool_ == 5) {
        interp_size = 4;

    } else { interp_size = 1;
}
    /** if slope is x/y */
    if (slopeSwitch == 0) {
        /** drawing to the right on the canvas */
        for (int i = prev_x; i < x; i+=interp_size) {
            next_y = GetNextY(prev_x, prev_y, slope, i);
            (*vector_of_tools[cur_tool_]).
                ApplyMask(i, next_y, display_buffer_, ColorData
                    (cur_color_red_, cur_color_green_, cur_color_blue_));
        }
        /** drawing to the left on the canvas */
        for (int i = prev_x; i > x; i-=interp_size) {
            next_y = GetNextY(prev_x, prev_y, slope, i);
            (*vector_of_tools[cur_tool_]).
                ApplyMask(i, next_y, display_buffer_, ColorData
                    (cur_color_red_, cur_color_green_, cur_color_blue_));
            }

    /** if slope is y/x */
    } else if (slopeSwitch == 1) {
        /** drawing to the right on the canvas */
        for (int i = prev_y; i < y; i+=interp_size) {
            next_y = GetNextY(prev_y, prev_x, slope, i);
            (*vector_of_tools[cur_tool_]).
                ApplyMask(next_y, i, display_buffer_, ColorData
                    (cur_color_red_, cur_color_green_, cur_color_blue_));
        }
        /** drawing to the left on the canvas */
        for (int i = prev_y; i > y; i-=interp_size) {
            next_y = GetNextY(prev_y, prev_x, slope, i);
            (*vector_of_tools[cur_tool_]).
                ApplyMask(next_y, i, display_buffer_, ColorData
                    (cur_color_red_, cur_color_green_, cur_color_blue_));
        }
    }
}

/** Calculates the next y coordinate from our slope, and previous coordinates */
int FlashPhotoApp::GetNextY(int prev_x, int prev_y, float slope, int next_x) {
    return (-1.0*((slope*next_x)-(slope*prev_x)-prev_y));
}

void FlashPhotoApp::MouseMoved(int x, int y) {}

void FlashPhotoApp::LeftMouseDown(int x, int y) {
  std::cout << "mousePressed " << x << " " << y << std::endl;
  state_manager_.receivePixelBuffer(display_buffer_);
  /** Current tool applied to pixelBuffer once */
  (*vector_of_tools[cur_tool_]).ApplyMask(x, y, display_buffer_,
     ColorData(cur_color_red_, cur_color_green_, cur_color_blue_));

  /** set previous x and previous y to current */
  prev_x = x;
  prev_y = y;
}

void FlashPhotoApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;

  /** set previous x and previous y to default -1 */
  prev_x = -1;
  prev_y = -1;
}

void FlashPhotoApp::InitializeBuffers(ColorData background_color,
    int width, int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

/** Initialize tools here */
void FlashPhotoApp::InitTools(void) {
    vector_of_tools.push_back(new Pen());
    vector_of_tools.push_back(new Eraser());
    vector_of_tools.push_back(new SprayCan());
    vector_of_tools.push_back(new Calligraphy());
    vector_of_tools.push_back(new Highlighter(display_buffer_));
    vector_of_tools.push_back(new Stamp());
    vector_of_tools.push_back(new BlurTool());
    // vector_of_tools.push_back(new Special());
}

void FlashPhotoApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  GLUI_Panel *toolPanel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Eraser");
    new GLUI_RadioButton(radio, "Spray Can");
    new GLUI_RadioButton(radio, "Caligraphy Pen");
    new GLUI_RadioButton(radio, "Highlighter");
    new GLUI_RadioButton(radio, "Stamp");
    new GLUI_RadioButton(radio, "Blur");
  }

  GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");
  {
    cur_color_red_ = 0;
    glui_ctrl_hooks_.spinner_red  = new GLUI_Spinner(color_panel, "Red:",
                                                     &cur_color_red_,
                                                     UICtrl::UI_COLOR_R,
                                                     s_gluicallback);
    glui_ctrl_hooks_.spinner_red->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    glui_ctrl_hooks_.spinner_green = new GLUI_Spinner(color_panel, "Green:",
                                                      &cur_color_green_,
                                                      UICtrl::UI_COLOR_G,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_green->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    glui_ctrl_hooks_.spinner_blue  = new GLUI_Spinner(color_panel, "Blue:",
                                                      &cur_color_blue_,
                                                      UICtrl::UI_COLOR_B,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_blue->set_float_limits(0, 1.0);

    new GLUI_Button(color_panel, "Red", UICtrl::UI_PRESET_RED,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Orange", UICtrl::UI_PRESET_ORANGE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Yellow", UICtrl::UI_PRESET_YELLOW,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Green", UICtrl::UI_PRESET_GREEN,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Blue", UICtrl::UI_PRESET_BLUE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Purple", UICtrl::UI_PRESET_PURPLE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "White", UICtrl::UI_PRESET_WHITE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Black", UICtrl::UI_PRESET_BLACK,
                    s_gluicallback);
  }

  /* Initialize state management (undo, redo, quit) */
  state_manager_.InitGlui(glui(), s_gluicallback);

  new GLUI_Button(const_cast<GLUI*>(glui()),
                "Quit", UICtrl::UI_QUIT,
                static_cast<GLUI_Update_CB>(exit));

  /* Initialize Filtering */
  filter_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize image I/O */
  io_manager_.InitGlui(glui(), s_gluicallback);
  return;
}

void FlashPhotoApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_PRESET_RED:
      cur_color_red_ = 1;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_ORANGE:
      cur_color_red_ = 1;
      cur_color_green_ = 0.5;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_YELLOW:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_GREEN:
      cur_color_red_ = 0;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_BLUE:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_PURPLE:
      cur_color_red_ = 0.5;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_WHITE:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_BLACK:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_APPLY_BLUR:
      state_manager_.receivePixelBuffer(display_buffer_);

      filter_manager_.ApplyBlur(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SHARP:
      state_manager_.receivePixelBuffer(display_buffer_);

      filter_manager_.ApplySharpen(display_buffer_);
      break;
    case UICtrl::UI_APPLY_MOTION_BLUR:
      state_manager_.receivePixelBuffer(display_buffer_);

      filter_manager_.ApplyMotionBlur(display_buffer_);
      break;
    case UICtrl::UI_APPLY_EDGE:
      state_manager_.receivePixelBuffer(display_buffer_);

      filter_manager_.ApplyEdgeDetect(display_buffer_);
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      state_manager_.receivePixelBuffer(display_buffer_);

      filter_manager_.ApplyThreshold(display_buffer_);
      break;
    case UICtrl::UI_APPLY_DITHER:
      state_manager_.receivePixelBuffer(display_buffer_);

      filter_manager_.ApplyThreshold(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SATURATE:
      state_manager_.receivePixelBuffer(display_buffer_);

      filter_manager_.ApplySaturate(display_buffer_);
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      state_manager_.receivePixelBuffer(display_buffer_);

      filter_manager_.ApplyChannel(display_buffer_);
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      state_manager_.receivePixelBuffer(display_buffer_);

      filter_manager_.ApplyQuantize(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SPECIAL_FILTER:
      state_manager_.receivePixelBuffer(display_buffer_);

      filter_manager_.ApplySpecial(display_buffer_);
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      io_manager_.LoadImageToCanvas(&display_buffer_);

      SetWindowDimensions(display_buffer_->width(), display_buffer_->height());

      state_manager_.Clear();
      break;
    case UICtrl::UI_LOAD_STAMP_BUTTON:
      // send io_manager the stamp tool, to load its mask
      io_manager_.LoadImageToStamp(reinterpret_cast<Stamp*>
        (vector_of_tools[5]));

      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      io_manager_.SaveCanvasToFile(display_buffer_);
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      break;
    case UICtrl::UI_FILE_NAME:
      io_manager_.set_image_file(io_manager_.file_name());
      break;
    case UICtrl::UI_UNDO:
      state_manager_.UndoOperation(display_buffer_);
      break;
    case UICtrl::UI_REDO:
      state_manager_.RedoOperation(display_buffer_);
      break;
    default:
      break;
  }

  // Forces canvas to update changes made in this function
  glui()->post_update_main_gfx();
}

/*******************************************************************************
 * Member Functions For Managing GLUI Interface
 ******************************************************************************/
void FlashPhotoApp::update_colors(void) {
  glui_ctrl_hooks_.spinner_blue->set_float_val(cur_color_blue_);
  glui_ctrl_hooks_.spinner_green->set_float_val(cur_color_green_);
  glui_ctrl_hooks_.spinner_red->set_float_val(cur_color_red_);
}

void FlashPhotoApp::InitGraphics(void) {
  // Initialize OpenGL for 2D graphics as used in the BrushWork app
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0, width(), 0, height());
  glViewport(0, 0, width(), height());
}

}  /* namespace image_tools */
