using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor grabberML;
extern motor grabberMR;
extern motor ElevM;
extern motor MFL;
extern motor MBL;
extern motor MFR;
extern motor MBR;
extern motor ArmL;
extern motor ArmR;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );