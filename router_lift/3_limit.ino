static bool DSW1, ESW1;   // bottom switch
static bool DSW2, ESW2;   // light dependent resistor sensor module

void limit_checker( void )
{
  static bool PSW1, PSW2;
  DSW1 = !digitalRead( SW1 ); ESW1 = DSW1 ^ PSW1 & DSW1; PSW1 = DSW1;
  DSW2 = !digitalRead( SW2 ); ESW2 = DSW2 ^ PSW2 & DSW2; PSW2 = DSW2;
}

static uint8_t Multiplier = 3;

long multiplier_result( void )
{
  switch ( Multiplier ) {
    case 1: return ( 80 ); break;    //  0.1 mm
    case 2: return ( 800 ); break;   //  1.0 mm
    case 3: return ( 4000 ); break;  //  5.0 mm 
    case 4: return ( 8000 ); break;  //  1.0 cm
    case 5: return ( 16000 ); break; //  2.0 cm
  }
}

static long Value[] = { 0, 0, 0 };

void divide( void )
{
  long d = stepper.currentPosition();
  Value[2] = d / 8000; d %= 8000;
  Value[1] = d / 800;  d %= 800;
  Value[0] = d / 80;
}
