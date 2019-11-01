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
// grabberML            motor         1
// grabberMR            motor         2
// ElevM                motor         15
// MFL                  motor         14
// MBL                  motor         11
// MFR                  motor         13
// MBR                  motor         12
// ArmL                 motor         4
// ArmR                 motor         5
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

int grabSpeed = 100;
int elevSpeed = 100;
int motorSpeed = 100;
bool controllerSwitch = false;
bool driveHold = false;

// SpeedController is for controlling the speed of motor
int SpeedController() {
  Brain.Screen.clearLine(2, color::black);
  Brain.Screen.setCursor(2, 0);
  Brain.Screen.print("Starting the Task");
  while (true) {
    if (Controller1.ButtonX.pressing()) {
      grabSpeed += 10;
      elevSpeed += 10;
      motorSpeed += 10;
      Brain.Screen.clearLine(2, color::black);
      Brain.Screen.setCursor(2, 0);
      Brain.Screen.print("Speed Set to %d", grabSpeed);
    }
    if (Controller1.ButtonB.pressing()) {
      grabSpeed -= 10;
      elevSpeed -= 10;
      motorSpeed -= 10;
      Brain.Screen.clearLine(2, color::black);
      Brain.Screen.setCursor(2, 0);
      Brain.Screen.print("Speed Set to %d", grabSpeed);
    }
    if (Controller1.ButtonY.pressing() || Controller1.ButtonA.pressing()) {
      grabSpeed = 100;
      elevSpeed = 100;
      motorSpeed = 100;
      Brain.Screen.clearLine(2, color::black);
      Brain.Screen.setCursor(2, 0);
      Brain.Screen.print("Speed Set to %d", grabSpeed);
    }
    vex::task::sleep(50);
    grabberML.setVelocity(grabSpeed, rpm);
    grabberMR.setVelocity(grabSpeed, rpm);
    ElevM.setVelocity(elevSpeed, rpm);
    if (controllerSwitch) {
      MFL.setVelocity(motorSpeed, rpm);
      MBL.setVelocity(motorSpeed, rpm);
      MFR.setVelocity(motorSpeed, rpm);
      MBR.setVelocity(motorSpeed, rpm);
    }
  }
  return 0;
}

// ControllerSwitch is for switch between joystin and button , just for driving
void ControllerSwitch() {
  /*
    if (Controller1.ButtonR2.pressing()) {
      if (controllerSwitch) {
        controllerSwitch = false;
      } else {
        controllerSwitch = true;
      }
    }
    */
}
// grabberController is for control the motion of grabber
void grabberController() {
  if (Controller1.ButtonL1.pressing()) {
    grabberML.spin(forward);
    grabberMR.spin(forward);
  } else if (Controller1.ButtonL2.pressing()) {
    grabberML.spin(reverse);
    grabberMR.spin(reverse);
  } else {
    grabberML.stop();
    grabberMR.stop();
  }
}

void driveMotor(char l, char r) {
  if (l == 'F') {
    MFL.spin(forward);
    MBL.spin(forward);
  } else if (l == 'B') {
    MFL.spin(reverse);
    MBL.spin(reverse);
  }
  if (r == 'F') {
    MFR.spin(forward);
    MBR.spin(forward);
  } else if (r == 'B') {
    MFR.spin(reverse);
    MBR.spin(reverse);
  }
  if (l == 'S' && r == 'S') {
    MFL.stop();
    MBL.stop();
    MFR.stop();
    MBR.stop();
  }
}

void speedSet() {
  grabberML.setVelocity(grabSpeed, rpm);
  grabberMR.setVelocity(grabSpeed, rpm);
  ElevM.setVelocity(elevSpeed, rpm);
  MFL.setVelocity(motorSpeed, rpm);
  MBL.setVelocity(motorSpeed, rpm);
  MFR.setVelocity(motorSpeed, rpm);
  MBR.setVelocity(motorSpeed, rpm);
}

void elevatorUnload() {
    ElevM.setPosition(0, degrees);
  // 2100
  if (ElevM.position(degrees) < 1200) {
    grabSpeed = -40;
    elevSpeed = 100;
    speedSet();
    grabberML.spin(reverse);
    grabberMR.spin(reverse);
    ElevM.spinToPosition(1100, degrees);
    vex::task::sleep(10);
    grabberML.stop();
    grabberMR.stop();
    grabSpeed = -10;
    elevSpeed = 30;
    speedSet();
    vex::task::sleep(100);
    grabberML.spin(forward);
    grabberMR.spin(forward);
    ElevM.spinToPosition(1500, degrees);
    elevSpeed = 140;
    driveHold = true;
    motorSpeed = 20;
    speedSet();

    vex::task::sleep(500);
    grabberML.stop();
    grabberMR.stop();
    // driveMotor('F', 'F');
    vex::task::sleep(500);
    driveMotor('S', 'S');
    motorSpeed = -20;
    speedSet();

    vex::task::sleep(100);
    driveMotor('B', 'B');
    vex::task::sleep(500);
    driveHold = false;
    driveMotor('S', 'S');
    ElevM.spinToPosition(0, degrees);
  }
}

// elevatorController is for control the motion of elevator
void elevatorController() {
  if (Controller1.ButtonR1.pressing() && Controller1.ButtonR2.pressing()) {
    elevatorUnload();
  } else if (Controller1.ButtonR1.pressing()) {
    if (ElevM.position(degrees) > 50) {
      ElevM.spinToPosition(0, degrees);
    }
  } else if (Controller1.ButtonR2.pressing()) {
    ElevM.spin(forward);
  } else {
    ElevM.stop();
  }
}

int DriveController() {
  while (true) {
    if (controllerSwitch) {
      if (Controller1.ButtonUp.pressing()) {
        driveMotor('F', 'F');
      } else if (Controller1.ButtonDown.pressing()) {
        driveMotor('B', 'B');
      } else if (Controller1.ButtonLeft.pressing()) {
        driveMotor('B', 'F');
      } else if (Controller1.ButtonRight.pressing()) {
        driveMotor('F', 'B');
      } else {
        if (!driveHold) {
          driveMotor('S', 'S');
        }
      }
    } else {
      MFL.setVelocity(Controller1.Axis3.value() * 3, rpm);
      MBL.setVelocity(Controller1.Axis3.value() * 3, rpm);
      MFR.setVelocity(Controller1.Axis2.value() * 3, rpm);
      MBR.setVelocity(Controller1.Axis2.value() * 3, rpm);
      MFL.spin(forward);
      MBL.spin(forward);
      MFR.spin(forward);
      MBR.spin(forward);
    }
    vex::task::sleep(10);
  }
  return 0;
}

void autoBlueOneTime() {
  // bool a = controllerSwitch;

  controllerSwitch = true;
  grabSpeed = 200;
  motorSpeed = 100;
  speedSet();
  grabberML.spin(forward);
  grabberMR.spin(forward);
  vex::task::sleep(500);
  // F 3
  driveMotor('F', 'F');
  vex::task::sleep(1500);
  driveMotor('S', 'S');
  motorSpeed = 40;
  speedSet();
  vex::task::sleep(2000);
  /*
    // TL 2
    driveMotor('B', 'F');
    vex::task::sleep(550);
    driveMotor('S', 'S');
    vex::task::sleep(500);
    // F 3
    driveMotor('F', 'F');
    vex::task::sleep(1200);
    driveMotor('S', 'S');
    vex::task::sleep(500);
    grabSpeed = 0;
    speedSet();
    driveMotor('B', 'B');
    vex::task::sleep(100);
    driveMotor('S', 'S');
    vex::task::sleep(500);
      grabSpeed = 200;
    speedSet();
    driveMotor('F', 'F');
    vex::task::sleep(200);
    driveMotor('S', 'S');
    vex::task::sleep(500);
    */
  motorSpeed = 60;
  speedSet();
  driveMotor('B', 'F');
  vex::task::sleep(1300);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  motorSpeed = 100;
  speedSet();
  driveMotor('F', 'F');
  vex::task::sleep(1500);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  grabSpeed=0;
  motorSpeed = 40;
  speedSet();
  driveMotor('B', 'F');
  vex::task::sleep(1000);
  driveMotor('S', 'S');
  vex::task::sleep(500);

  MFL.setVelocity(60, rpm);
  MBL.setVelocity(60, rpm);
  MFR.setVelocity(10, rpm);
  MBR.setVelocity(10, rpm);
  driveMotor('F', 'F');
  vex::task::sleep(500);
  MFL.setVelocity(20, rpm);
  MBL.setVelocity(20, rpm);
  MFR.setVelocity(60, rpm);
  MBR.setVelocity(60, rpm);
  driveMotor('F', 'F');
  vex::task::sleep(700);
  motorSpeed = 20;
  speedSet();
  driveMotor('F', 'F');
  vex::task::sleep(1500);
  driveMotor('S', 'S');

  // TR 3
/*
  grabberML.stop();
  grabberMR.stop();
  driveMotor('F', 'B');
  vex::task::sleep(3000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // F 5
  driveMotor('F', 'F');
  vex::task::sleep(5000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // TL 3
  driveMotor('B', 'F');
  vex::task::sleep(3000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // F 3
  grabberML.spin(forward);
  grabberMR.spin(forward);
  driveMotor('F', 'F');
  vex::task::sleep(3000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // B 10
  grabberML.stop();
  grabberMR.stop();
  driveMotor('B', 'B');
  vex::task::sleep(10000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // F 1
  driveMotor('F', 'F');
  vex::task::sleep(1000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // TR 2
  driveMotor('F', 'B');
  vex::task::sleep(2000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // F 2
  driveMotor('F', 'F');
  vex::task::sleep(2000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // U 5
  */
  
   elevatorUnload();
  motorSpeed = -50;
  speedSet();
  driveMotor('F', 'F');
  vex::task::sleep(300);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // controllerSwitch = a;
}

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
  vex::task::sleep(10);
  ElevM.setVelocity(300, rpm);
  ElevM.spin(reverse);
  vex::task::sleep(500);
  ElevM.stop();
  autoBlueOneTime();
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
  vexcodeInit();
  controllerSwitch = false;

  // elevSpeed = 100;
  Brain.Screen.clearLine(1, color::black);
  Brain.Screen.setCursor(1, 0);
  Brain.Screen.print("Prigram Started");
  ElevM.setPosition(0, degrees);

  // running tasks
  vex::task speedController(SpeedController);
  vex::task driveController(DriveController);
  while (1) {
    grabberController();
    elevatorController();
    ControllerSwitch();
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

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
