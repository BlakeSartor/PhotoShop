/*******************************************************************************
 * Name            : spray_can.h
 * Project         : BrushWork
 * Description     : Implementation of BrushWrok
 * Copyright       : Copyright 2016. All rights reserved.
 * Creation Date   : 10/14/16
 * Original Author : Raghav Mutneja
 *
 ******************************************************************************/

#ifndef PROJECT_ITERATION2_SRC_INCLUDE_SPRAY_CAN_H_
#define PROJECT_ITERATION2_SRC_INCLUDE_SPRAY_CAN_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "include/tool.h"
#include "include/mask.h"

/*******************************************************************************
 * Class Declaration
 ******************************************************************************/

class SprayCan : public Tool {
 public:
    SprayCan();
    ~SprayCan();
    void virtual SetMask();
};

#endif  // PROJECT_ITERATION2_SRC_INCLUDE_SPRAY_CAN_H_
