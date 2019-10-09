const long TopMostLimit =  44000;  //  55mm
const long UpperLimit   =  24000;  //  30mm
const long BottomLimit  = -12000;  // -15mm
const long HomePosition =  12000;  //  15mm

struct stepper_settings_collection
{
  const float STEPPER_ATOM = 1;    // 0.0025mm
  const float STEPPER_SEED = 8;    // 0.01mm
  float StepperAccuracy    = 80;   // 0.1mm
  float Distance           = 0;
  long  CurrentPosition    = 0;
  float AccelerationSpeed  = 7000;
  float MaxSpeed           = 9000;
  float Speed              = 8000;
};
static stepper_settings_collection ssc;

void stepper_preparation ( void )
{
  stepper.setMaxSpeed( ssc.MaxSpeed );
  stepper.setSpeed( ssc.Speed );
  stepper.setAcceleration( ssc.AccelerationSpeed );
  stepper.enableOutputs();
  stepper.move( ssc.Distance );
}