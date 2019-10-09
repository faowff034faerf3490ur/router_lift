// IR code
#define _VALID   0xFF0000
#define _0       0xFF9867
#define _1       0xFFA25D
#define _2       0xFF629D
#define _3       0xFFE21D
#define _4       0xFF22DD
#define _5       0xFF02FD
#define _6       0xFFC23D
#define _7       0xFFE01F
#define _8       0xFFA857
#define _9       0xFF906F
#define _LEFT    0xFF10EF
#define _RIGHT   0xFF5AA5
#define _UP      0xFF18E7
#define _DOWN    0xFF4AB5
#define _CENTER  0xFF38C7
#define _STAR    0xFF6897
#define _NUMBER  0xFFB04F
#define _REPEAT  0xFFFFFF

static boolean  DirectSwitch;     // direct response switch
static boolean  OneShotSwitch;    // up edge trigger switch
static uint32_t RepeatCounter;    // not used in this project
static uint32_t CurrentValue;     // raw data
static char     CurrentCode;      // ascii numeral code
static uint8_t Figure;            // 1 to 9 number code

void infrared_checker( void )
{
  DirectSwitch = OneShotSwitch = false;
  if ( irrecv.decode( &results ) )
  {
    if ( results.decode_type == NEC )
    {
      if ( ( results.value & _VALID ) == _VALID )
      {
        DirectSwitch = true;
        if ( results.bits  ) OneShotSwitch = true;
        if ( results.bits  ) CurrentValue = results.value;
        else RepeatCounter++;
      }
    } else RepeatCounter = 0;
    irrecv.resume();
  }
  else CurrentValue = '\0';
}
