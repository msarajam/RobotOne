/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\msara                                            */
/*    Created:      Sat Oct 12 2019                                           */
/*    Description:  V5 project                                                */
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

int grabSpeed = 100;
int elevSpeed = 100;
int motorSpeed = 100;
bool controllerSwitch = true;
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

void elevatorUnload() {
  // 2100
  if (ElevM.position(degrees) < 1200) {
    grabSpeed = 40;
    elevSpeed = 100;
    grabberML.spin(reverse);
    grabberMR.spin(reverse);
    ElevM.spinToPosition(1100, degrees);
    vex::task::sleep(10);
    grabberML.stop();
    grabberMR.stop();
    grabSpeed = -10;
    elevSpeed = 30;
    vex::task::sleep(100);
    grabberML.spin(forward);
    grabberMR.spin(forward);
    ElevM.spinToPosition(1500, degrees);
    elevSpeed = 140;
    driveHold = true;
    motorSpeed = 20;
    vex::task::sleep(500);
    grabberML.stop();
    grabberMR.stop();
    driveMotor('F', 'F');
    vex::task::sleep(500);
    driveMotor('S', 'S');
        motorSpeed = -20;
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
  controllerSwitch = true;
  grabSpeed = 100;
  grabberML.spin(forward);
  grabberMR.spin(forward);
  vex::task::sleep(500);
  // F 3
  driveMotor('F', 'F');
  vex::task::sleep(3000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // TL 2
  driveMotor('B', 'F');
  vex::task::sleep(2000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // F 3
  driveMotor('F', 'F');
  vex::task::sleep(3000);
  driveMotor('S', 'S');
  vex::task::sleep(500);
  // TR 3
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
  elevatorUnload();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  vex::task::sleep(10);
  ElevM.setVelocity(300, rpm);
  ElevM.spin(reverse);
  vex::task::sleep(500);
  // elevSpeed = 100;
  Brain.Screen.clearLine(1, color::black);
  Brain.Screen.setCursor(1, 0);
  Brain.Screen.print("Prigram Started");
  ElevM.setPosition(0, degrees);

  // running tasks
  vex::task speedController(SpeedController);
  vex::task driveController(DriveController);

  while (true) {

    grabberController();
    elevatorController();
    ControllerSwitch();

    /*
        if (Controller1.ButtonR1.pressing()){

      Brain.Screen.clearLine(1, color::black);
      Brain.Screen.setCursor(1, 0);
      Brain.Screen.print("%f",ElevM.position(degrees));

        }
      */
  }
}
