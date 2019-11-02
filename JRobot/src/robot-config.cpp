#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor MFL = motor(PORT1, ratio18_1, false);
motor MFR = motor(PORT5, ratio18_1, false);
motor MBL = motor(PORT11, ratio18_1, false);
motor MBR = motor(PORT20, ratio18_1, false);
motor ArmL = motor(PORT15, ratio18_1, false);
motor ArmR = motor(PORT16, ratio18_1, false);
motor Claw = motor(PORT8, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}