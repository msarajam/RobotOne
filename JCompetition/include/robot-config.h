using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor MFL;
extern motor MFR;
extern motor MBL;
extern motor MBR;
extern motor ArmL;
extern motor ArmR;
extern motor Claw;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );