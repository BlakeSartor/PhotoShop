/*******************************************************************************
 * Name            : state_manager.h
 * Project         : FlashPhoto
 * Module          : state_manager
 * Description     : Header for IoHandler class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 11/12/16
 * Original Author : Modified by Raghav Mutneja
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_STATE_MANAGER_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_STATE_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "GL/glui.h"
#include "ui_ctrl.h"
#include "pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The manager for simulation state in FlashPhoto.
 *
 * Simulation state is defined as the sequence of operations that comprises the
 * current canvas. An operation is defined as what happens during 1 click/drag
 * operation, or when 1 button on the control panel that affects the canvas is
 * clicked.
 *
 * A sequence of undos followed by some edits, followed by more undos will
 * FIRST undo the new edits, until you get back to the state before you made the
 * edits. You will not be able to go back any further.
 */
class StateManager {
 public:
  StateManager();
  ~StateManager() {}

  void InitGlui(const GLUI *const glui,
                void (*s_gluicallback)(int));

  /**
   * @brief Undoes the last operation applied to the canvas (not permanently; it
   * can still be re-done later)
   *
   */
  void UndoOperation(image_tools::PixelBuffer *canvas);

  /**
   * @brief Re-does the last un-done operation applied to the canvas (not
   * permanently; it can be undone again later)
   *
   */
  void RedoOperation(image_tools::PixelBuffer *canvas);

  /**
    * @brief Receives the current pixel_buffer i.e. the canvas.
    */

  void receivePixelBuffer(image_tools::PixelBuffer *canvas);
  // receives the buffer, right before changes are made in flashphoto_app

  void Clear();
  // clears both stacks, called when a new image is loaded

 private:
  void redo_toggle(bool select) {
    UICtrl::button_toggle(redo_btn_, select);
  }

  void undo_toggle(bool select) {
    UICtrl::button_toggle(undo_btn_, select);
  }

  /* Copy/move assignment/construction disallowed */
  StateManager(const StateManager &rhs) = delete;
  StateManager& operator=(const StateManager &rhs) = delete;

  /* data members */
  GLUI_Button *undo_btn_;
  GLUI_Button *redo_btn_;
};

}  /* namespace image_tools */

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_STATE_MANAGER_H_
