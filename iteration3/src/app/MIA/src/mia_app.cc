/*******************************************************************************
 * Name            : mia_app.cc
 * Project         : MIA
 * Module          : App
 * Description     : Implementation of MIA
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/app/MIA/src/mia_app.h"
#include <string>
#include "mia_filter_manager.h"
#include "mia_io_manager.h"
#include "tool.h"
#include "filter.h"
#include "convolution_filter.h"
#include "marker.h"
#include "stamp.h"
#include "edge_detection.h"
#include "sharpen.h"
#include "threshold.h"
#include "rgb_levels.h"
#include "saturation.h"
#include "quantize.h"
#include "blur.h"
#include <iostream>

/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAApp::MIAApp(int width, int height,
               const std::string& marker_fname) : BaseGfxApp(width, height),
                                                  filter_manager_(),
                                                  io_manager_(),
                                                  state_manager_(),
                                                  display_buffer_(nullptr),
                                                  marker_fname_(marker_fname),
                                                  cur_tool_(0) {}

  
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MIAAPP::CMD(int argc, char** argv) {
	if (argv[1] == "-h") {
		cout << "Usage:\n-h\t\t\tDisplay help optinos\n"
		 << "<file1> <file2>\t\tOpen <file1> and save it as <file2>\n"
		 << "<file> <operations>\t\tOpen <file> and perform <operations> on it\n"
		 << "<file1> <operations> <file2>\tOpen <file1>, perform <operations> on it, and"
		 		<< " save it as <file2>\n"
		 << "-sharpen <float>\t\tSharpen the image by <float> amount\n"
		 << "-edge\t\t\tApply edge detection\n"
		 << "-threshold <float>\t\tApply threshold filter with cutoff of <float>\n"
		 << "-quantize <int>\t\tApply quantize filter with <int> bins\n"
		 << "-blur <float>\t\t Apply blur filter with strength <float>\n"
		 << "-saturate <float>\t\tApply saturate filter with strength <float>\n"
		 << "-channel <float1> <float2> <float3>\tModify the RGB levels by <float>\n"
		 << "-compare\t\t\t  \n"
  	}
  	ImageManager * image = new ImageManager();
    
  	int height;
  	int width;
    PixelBuffer * newCanvas = image->loadimage
      (argv[1], height, width, (*display_buffer_)->getBackgroundColor());
	delete display_buffer_;
	display_buffer_ = newCanvas;
  	
 	int current_argument = 2;
 	std::string open_file = "";
 	std::string save_file;
 	
 	while(current_argument < argc) {
		switch (argv[current_argument]) {
			case "-sharpen" :
				if (open_file != "" and argc > current_argument+1) {
					filter_manager_.ApplySharpen(display_buffer, argv[current_argument+1]);
				}
				else {
					current_argument = argc;
					cout << "Error, command not recognized, use "
						 << "-h for more information\n";
				}
				
			case "-edge" :
				if (open_file != "") {
					filter_manager_.ApplyEdgeDetect(display_buffer, argv[current_argument+1]);
				}
				else {
					current_argument = argc;
					cout << "Error, command not recognized, use "
						 << "-h for more information\n";
				}	
			case "-threshold" :
				if (open_file != "" and argc > current_argument+1) {
					filter_manager_.ApplyThreshold(display_buffer, argv[current_argument+1]);
					
				}
				else {
					current_argument = argc;
					cout << "Error, command not recognized, use "
						 << "-h for more information\n";
				}
			case "-quantize" :
				if (open_file != "" and argc > current_argument+1) {
					filter_manager_.ApplyQuantize(display_buffer, argv[current_argument+1]);
				}
				else {
					current_argument = argc;
					cout << "Error, command not recognized, use "
						 << "-h for more information\n";
				}
			case "-blur" :
				if (open_file != "" and argc > current_argument+1) {
					filter_manager_.ApplyBlur(display_buffer, argv[current_argument+1]);
				}
				else {
					current_argument = argc;
					cout << "Error, command not recognized, use "
						 << "-h for more information\n";
				}
			case "-saturate" :
				if (open_file != "" and argc > current_argument+1) {
					filter_manager_.ApplySaturate(display_buffer, argv[current_argument+1]);
					
				}
				else {
					current_argument = argc;
					cout << "Error, command not recognized, use "
						 << "-h for more information\n";
				}
			case "-channel" :
				if (open_file != "" and argc > current_argument+1) {
					filter_manager_.ApplySharpen(display_buffer, argv[current_argument+1]);
				}
				else {
					current_argument = argc;
					cout << "Error, command not recognized, use "
						 << "-h for more information\n";
				}
			default :
				if (current_argument == argc - 1) {
					image->saveimage(argv[current_argument], display_buffer_);
				}
				current_argument = argc;
				cout << "Error, argument "
					<< current_argument
					<< " not recognized, use -h for more information\n";
			
		}
 	}
 	delete image;
}
void MIAApp::Init(
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
  set_caption("MIA");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  InitGlui();
  InitGraphics();
}

void MIAApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

MIAApp::~MIAApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
  }
}


void MIAApp::LeftMouseDown(int x, int y) {
  std::cout << "mousePressed " << x << " " << y << std::endl;
}


void MIAApp::InitializeBuffers(ColorData background_color,
                               int width, int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

void MIAApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  new GLUI_Column(glui(), false);
  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Marker");
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

void MIAApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_APPLY_SHARP:
      filter_manager_.ApplySharpen();
      break;
    case UICtrl::UI_APPLY_MOTION_BLUR:
      filter_manager_.ApplyMotionBlur();
      break;
    case UICtrl::UI_APPLY_EDGE:
      filter_manager_.ApplyEdgeDetect();
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      filter_manager_.ApplyThreshold();
      break;
    case UICtrl::UI_APPLY_SATURATE:
      filter_manager_.ApplySaturate();
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      filter_manager_.ApplyChannel();
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      filter_manager_.ApplyQuantize();
      break;
    case UICtrl::UI_APPLY_BLUR:
      filter_manager_.ApplyBlur();
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      io_manager_.LoadImageToCanvas();
      break;
    case UICtrl::UI_LOAD_STAMP_BUTTON:
      io_manager_.LoadImageToStamp();
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      io_manager_.SaveCanvasToFile();
      break;
    case UICtrl::UI_NEXT_IMAGE_BUTTON:
      io_manager_.LoadNextImage();
      break;
    case UICtrl::UI_PREV_IMAGE_BUTTON:
      io_manager_.LoadPreviousImage();
      break;
    case UICtrl::UI_FILE_NAME:
      io_manager_.set_image_file(io_manager_.file_name());
      break;
    case UICtrl::UI_UNDO:
      state_manager_.UndoOperation();
      break;
    case UICtrl::UI_REDO:
      state_manager_.RedoOperation();
      break;
    default:
      break;
  }

  // Forces canvas to update changes made in this function
  glui()->post_update_main_gfx();
}
void MIAApp::InitGraphics(void) {
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
