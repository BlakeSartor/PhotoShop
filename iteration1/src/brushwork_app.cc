/*******************************************************************************
 * Name            : brushwork_app.cc
 * Project         : BrushWork
 * Module          : App
 * Description     : Implementation of BrushWork
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Modified by Blake Sartor
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>
#include "include/brushwork_app.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/tool.h"
#include "include/pen.h"
#include "include/eraser.h"
#include "include/calligraphy.h"
#include "include/highlighter.h"
#include "include/spray_can.h"
#include "include/special.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
BrushWorkApp::BrushWorkApp(int width,
                           int height)
    : BaseGfxApp(width,
                 height),
      display_buffer_(nullptr),
      cur_tool_(0.0),
      cur_color_red_(0.0),
      cur_color_green_(0.0),
      cur_color_blue_(0.0),
      spinner_r_(nullptr),
      spinner_g_(nullptr),
      spinner_b_(nullptr) {}

BrushWorkApp::~BrushWorkApp(void) {
    if (display_buffer_) {
        delete display_buffer_;
    }
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void BrushWorkApp::Init(
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
    set_caption("BrushWork");

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

void BrushWorkApp::Display(void) {
    DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

void BrushWorkApp::MouseDragged(int x, int y) {
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
void BrushWorkApp::Interpolate(int x, int y, int prev_x, int prev_y,
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
int BrushWorkApp::GetNextY(int prev_x, int prev_y, float slope, int next_x) {
    return (-1.0*((slope*next_x)-(slope*prev_x)-prev_y));
}

void BrushWorkApp::MouseMoved(int x, int y) {}

void BrushWorkApp::LeftMouseDown(int x, int y) {
    std::cout << "mousePressed " << x << " " << y << std::endl;

    /** Current tool applied to pixelBuffer once */
    (*vector_of_tools[cur_tool_]).ApplyMask(x, y, display_buffer_,
        ColorData(cur_color_red_, cur_color_green_, cur_color_blue_));

    /** set previous x and previous y to current */
    prev_x = x;
    prev_y = y;
}

void BrushWorkApp::LeftMouseUp(int x, int y) {
    std::cout << "mouseReleased " << x << " " << y << std::endl;

    /** set previous x and previous y to default -1 */
    prev_x = -1;
    prev_y = -1;
}

void BrushWorkApp::InitializeBuffers(
    ColorData background_color,
    int width,
    int height) {
    display_buffer_ = new PixelBuffer(width, height, background_color);
}

/** Initialize tools here */
void BrushWorkApp::InitTools(void) {
    vector_of_tools.push_back(new Pen());
    vector_of_tools.push_back(new Eraser());
    vector_of_tools.push_back(new SprayCan());
    vector_of_tools.push_back(new Calligraphy());
    vector_of_tools.push_back(new Highlighter(display_buffer_));
    vector_of_tools.push_back(new Special());
}

void BrushWorkApp::InitGlui(void) {
    // Select first tool (this activates the first radio button in glui)
    cur_tool_ = 0;

    GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel,
                                                 &cur_tool_,
                                                 UI_TOOLTYPE,
                                                 s_gluicallback);

    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Eraser");
    new GLUI_RadioButton(radio, "Spray Can");
    new GLUI_RadioButton(radio, "Caligraphy Pen");
    new GLUI_RadioButton(radio, "Highlighter");
    new GLUI_RadioButton(radio, "Special");

    GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");

    cur_color_red_ = 0;
    spinner_r_  = new GLUI_Spinner(color_panel, "Red:", &cur_color_red_,
                                   UI_COLOR_R, s_gluicallback);
    spinner_r_->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    spinner_g_ = new GLUI_Spinner(color_panel, "Green:", &cur_color_green_,
                                   UI_COLOR_G, s_gluicallback);
    spinner_g_->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    spinner_b_  = new GLUI_Spinner(color_panel, "Blue:", &cur_color_blue_,
                                   UI_COLOR_B, s_gluicallback);
    spinner_b_->set_float_limits(0, 1.0);
    new GLUI_Button(color_panel, "Red", UI_PRESET_RED, s_gluicallback);
    new GLUI_Button(color_panel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
    new GLUI_Button(color_panel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
    new GLUI_Button(color_panel, "Green", UI_PRESET_GREEN, s_gluicallback);
    new GLUI_Button(color_panel, "Blue", UI_PRESET_BLUE, s_gluicallback);
    new GLUI_Button(color_panel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
    new GLUI_Button(color_panel, "White", UI_PRESET_WHITE, s_gluicallback);
    new GLUI_Button(color_panel, "Black", UI_PRESET_BLACK, s_gluicallback);


    new GLUI_Button(glui(), "Quit", UI_QUIT, static_cast<GLUI_Update_CB>(exit));
}


void BrushWorkApp::InitGraphics(void) {
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

void BrushWorkApp::GluiControl(int control_id) {
    switch (control_id) {
    case UI_PRESET_RED:
        cur_color_red_ = 1;
        cur_color_green_ = 0;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_ORANGE:
        cur_color_red_ = 1;
        cur_color_green_ = 0.5;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_YELLOW:
        cur_color_red_ = 1;
        cur_color_green_ = 1;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_GREEN:
        cur_color_red_ = 0;
        cur_color_green_ = 1;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_BLUE:
        cur_color_red_ = 0;
        cur_color_green_ = 0;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_PURPLE:
        cur_color_red_ = 0.5;
        cur_color_green_ = 0;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_WHITE:
        cur_color_red_ = 1;
        cur_color_green_ = 1;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_BLACK:
        cur_color_red_ = 0;
        cur_color_green_ = 0;
        cur_color_blue_ = 0;
        break;
    default:
        break;
    }

    spinner_b_->set_float_val(cur_color_blue_);
    spinner_g_->set_float_val(cur_color_green_);
    spinner_r_->set_float_val(cur_color_red_);
}
}  // namespace image_tools
