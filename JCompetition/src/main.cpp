/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// MFL                  motor         1               
// MFR                  motor         5               
// MBL                  motor         11              
// MBR                  motor         20              
// ArmL                 motor         15              
// ArmR                 motor         16              
// Claw                 motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

int armspeed = 300;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  ArmL.setVelocity(armspeed, rpm);
  ArmR.setVelocity(armspeed, rpm);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    if (Controller1.ButtonL1.pressing()) {
      ArmL.spin(forward);
      ArmR.spin(forward);
    } else if (Controller1.ButtonL2.pressing()) {
      ArmL.spin(reverse);
      ArmR.spin(reverse);
    } else {
      ArmL.stop();
      ArmR.stop();
    }

    if (Controller1.ButtonR1.pressing()) {
      Claw.spin(forward);
    } else if (Controller1.ButtonR2.pressing()) {
      Claw.spin(reverse);
    } else {
      Claw.stop();
    }
    MFL.setVelocity(Controller1.Axis3.value() * 3, rpm);
    MBL.setVelocity(Controller1.Axis3.value() * 3, rpm);
    MFR.setVelocity(Controller1.Axis2.value() * 3, rpm);
    MBR.setVelocity(Controller1.Axis2.value() * 3, rpm);
    MFL.spin(forward);
    MBL.spin(forward);
    MFR.spin(forward);
    MBR.spin(forward);
    wait(100, msec);
  }
}
