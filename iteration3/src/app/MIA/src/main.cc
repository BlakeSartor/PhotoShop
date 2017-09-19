/*******************************************************************************
 * Name            : main.cc
 * Project         : MIA
 * Module          : main
 * Description     : Entry point for MIA application
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 1/15/15
 * Author          : Blake Sartor
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
/* FIXME: ADDITIONAL INCLUDES AS NECESSARY HERE :-) */

#include <stdio.h>
#include <string>
/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char** argv) {
  if (argc == 1) {
    image_tools::MIAApp *app = new image_tools::MIAApp(
        400,
        400,
        "resources/marker.png");
    app->Init(argc, argv, 50, 50,
              image_tools::ColorData(1, 1, static_cast<float>(0.95)));
    app->RunMainLoop();
    delete app;
  } else {
  	image_tools::MIAAPP *app = new image_tools::MIAAPP(
  		400, 400, "resources/marker.png");
  	app->CMD(argc, argv);
    delete app;
  }
  return 0;
} /* main() */
