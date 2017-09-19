/*******************************************************************************
 * Name            : state_manager.cc
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Implementation of StateManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 11/12/16
 * Original Author : Modified by Raghav Mutneja
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/state_manager.h"
#include <iostream>
#include <deque>
#include "include/ui_ctrl.h"
#include "include/pixel_buffer.h"
#include "include/flashphoto_app.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {
  std::deque<PixelBuffer> undo;
  std::deque<PixelBuffer> redo;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
StateManager::StateManager(void) :
    undo_btn_(nullptr),
    redo_btn_(nullptr) {
    }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void StateManager::InitGlui(const GLUI *const glui,
                            void (*s_gluicallback)(int)) {
  undo_btn_ = new GLUI_Button(const_cast<GLUI*>(glui), "Undo", UICtrl::UI_UNDO,
                              s_gluicallback);
  undo_toggle(false);

  redo_btn_  = new GLUI_Button(const_cast<GLUI*>(glui), "Redo", UICtrl::UI_REDO,
                               s_gluicallback);
  redo_toggle(false);
}

void StateManager::receivePixelBuffer(image_tools::PixelBuffer *canvas) {
  if (undo.size() >= 50) {
    undo.pop_back();
    undo.push_front(*canvas);
  } else {
    undo.push_front(*canvas);
  }
  redo.clear();
  redo_toggle(false);

  undo_toggle(true);
}

void StateManager::UndoOperation(image_tools::PixelBuffer *canvas) {
  std::cout << "Undoing..." << std::endl;
        /* Need the original canvas before its modified, 
         to push onto the redo this copy needs to be created
         before mousedragged happens*/
  image_tools::PixelBuffer temp = *canvas;
  *canvas = undo.front();
    if (undo.size() >= 50) {
      undo.pop_front();
      // undo.push_back(*canvas);
      redo.push_front(temp);
    } else {
      undo.pop_front();
      // undo.push_back(*canvas);
      redo.push_front(temp);
    }
    redo_toggle(true);
    if (undo.empty()) {
        undo_toggle(false);
    }
}

void StateManager::Clear() {
    undo.clear();
    redo.clear();

    undo_toggle(false);
    redo_toggle(false);
}
void StateManager::RedoOperation(image_tools::PixelBuffer *canvas) {
  std::cout << "Redoing..." << std::endl;

  undo.push_front(*canvas);

  image_tools::PixelBuffer temp = *canvas;
  *canvas = redo.front();

  redo.pop_front();


    undo_toggle(true);
    if (redo.empty()) {
        redo_toggle(false);
    }
}
}  /* namespace image_tools */
