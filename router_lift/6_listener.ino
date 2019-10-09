//////////////////////////////////////////////////////////////////////////////
//  READY  READY  READY  READY  READY  READY  READY  READY  READY  READY
//////////////////////////////////////////////////////////////////////////////
void _00( void )
{
  display.print( "----" );
  ssc.Distance = -99999; // seek the bottom location.
  stepper_preparation();
  EventID++;
}
void _01( void )
{
  if( DSW1 ) 
  {
    stepper.setCurrentPosition(0);
    EventID++;
  } else 
    stepper.run();
}
void _02( void )
{
  ssc.Distance = HomePosition; // 18mm
  stepper_preparation();
  while( stepper.currentPosition() < HomePosition ) stepper.run();
  stepper.stop();
  stepper.runToPosition();
  stepper.setCurrentPosition(0);
  EventID++;
}
//////////////////////////////////////////////////////////////////////////////
//  CLEAR  CLEAR  CLEAR  CLEAR  CLEAR  CLEAR  CLEAR  CLEAR  CLEAR  CLEAR
//////////////////////////////////////////////////////////////////////////////
void _03( void )
{
  stepper.disableOutputs();
  print_target_position(0);
  display.blink();
  EventID++;
}
//////////////////////////////////////////////////////////////////////////////
//  SELECT  SELECT  SELECT  SELECT  SELECT  SELECT  SELECT  SELECT  SELECT
//////////////////////////////////////////////////////////////////////////////
void _04( void )
{
  switch ( CurrentValue ) {
    case _UP    : EventID = E05; break;
    case _DOWN  : EventID = E06; break;
    case _LEFT  : EventID = E07; break;
    case _RIGHT : EventID = E08; break;
    case _STAR  : EventID = E09; break;
    case _NUMBER: EventID = E10; break;
    case _CENTER: EventID = E11; break;
    case _0 : EventID = E12; break;
    case _1 : EventID = E12; break;
    case _2 : EventID = E12; break;
    case _3 : EventID = E12; break;
    case _4 : EventID = E12; break;
    case _5 : EventID = E12; break;
    case _6 : EventID = E12; break;
    case _7 : EventID = E12; break;
    case _8 : EventID = E12; break;
    case _9 : EventID = E12; break;
  }
}
//////////////////////////////////////////////////////////////////////////////
//  UP    UP    UP    UP    UP    UP    UP    UP    UP    UP    UP    UP
//////////////////////////////////////////////////////////////////////////////
void _05( void )
{
  long Limit;
  if ( DSW2 ) Limit = UpperLimit; else Limit = TopMostLimit;
  if ( stepper.currentPosition() == Limit ) { EventID = E03; return; }
  ssc.Distance = multiplier_result();
  if ( stepper.currentPosition() + ssc.Distance > Limit )
    ssc.Distance = Limit - stepper.currentPosition();
  print_target_position( ssc.Distance );
  stepper_preparation();  
  while( stepper.run() );
  event_switcher( E04 );
  divide();
}
//////////////////////////////////////////////////////////////////////////////
//  DOWN  DOWN  DOWN  DOWN  DOWN  DOWN  DOWN  DOWN  DOWN  DOWN  DOWN  DOWN
//////////////////////////////////////////////////////////////////////////////
void _06( void )
{
  if ( stepper.currentPosition() == BottomLimit ) display.blink();
  else {
    long Limit = BottomLimit;
    ssc.Distance = -multiplier_result();
    if ( stepper.currentPosition() + ssc.Distance < Limit )
      ssc.Distance = Limit - stepper.currentPosition();
    print_target_position( ssc.Distance );
    stepper_preparation();
    while( stepper.run() );
    divide();
  }
  event_switcher( E04 );
}
//////////////////////////////////////////////////////////////////////////////
//  LEFT  LEFT  LEFT  LEFT  LEFT  LEFT  LEFT  LEFT  LEFT  LEFT  LEFT  LEFT
//////////////////////////////////////////////////////////////////////////////
void _07( void )
{
  if ( Multiplier < 5 ) Multiplier++;
  print_multiplier();
  EventID = E04;
}
//////////////////////////////////////////////////////////////////////////////
//  RIGHT  RIGHT  RIGHT  RIGHT  RIGHT  RIGHT  RIGHT  RIGHT  RIGHT  RIGHT
//////////////////////////////////////////////////////////////////////////////
void _08( void )
{
  if ( Multiplier > 1 ) Multiplier--;
  print_multiplier();
  EventID = E04;
}
//////////////////////////////////////////////////////////////////////////////
//  STAR  STAR  STAR  STAR  STAR  STAR  STAR  STAR  STAR  STAR  STAR  STAR
//////////////////////////////////////////////////////////////////////////////
void _09( void )
{
  if ( stepper.currentPosition() == Offset ) event_switcher( E04 );
  else {
    Offset = stepper.currentPosition();
    EventID = E03;
  }
  divide();
}
//////////////////////////////////////////////////////////////////////////////
//  NUMBER  NUMBER  NUMBER  NUMBER  NUMBER  NUMBER  NUMBER  NUMBER  NUMBER
//////////////////////////////////////////////////////////////////////////////
void _10( void )
{
  if( stepper.currentPosition() == Offset ) event_switcher( E04 );
  else {
    display.home();
    display.print( "   0" );
    stepper_preparation();
    stepper.moveTo( Offset );
    while( stepper.run() );
    EventID = E03;
  }
  divide();
}
//////////////////////////////////////////////////////////////////////////////
//  CENTER  CENTER  CENTER  CENTER  CENTER  CENTER  CENTER  CENTER  CENTER
//////////////////////////////////////////////////////////////////////////////
void _11( void )
{
  long Limit;
  if ( DSW2 ) Limit = UpperLimit; else Limit = TopMostLimit;
  long Val = Value[2] * 8000 + Value[1] * 800 + Value[0] * 80 + Offset;
  if ( Val != stepper.currentPosition() + Offset ) {
    if ( Val > Limit ) {
      Val = Limit;
      display.setCursor( 0, 1 );
      display.print( ( Val - Offset) / 80 );
    }
    stepper_preparation();
    stepper.moveTo( Val );
    while( stepper.run() );
  }
  print_target_position( 0 );
  divide();
  event_switcher( E04 );
}
//////////////////////////////////////////////////////////////////////////////
//  FIGURE  FIGURE  FIGURE  FIGURE  FIGURE  FIGURE  FIGURE  FIGURE  FIGURE
//////////////////////////////////////////////////////////////////////////////
void _12( void )
{
  Value[0] = Value[1] = Value[2] = 0;
  RemoteControler();
  Value[0] = Figure;  
  display.clear();
  display.setCursor( 0, 3 );
  display.print( Value[0] );
  event_switcher( E13 );
}
void _13( void )
{
  RemoteControler();
  Value[1] = Value[0];
  Value[0] = Figure;
  display.clear();
  display.setCursor( 0, 3 );
  display.print( Value[0] );
  display.setCursor( 0, 2 );
  display.print( Value[1] );
  event_switcher( E14 );
}
void _14( void )
{
  RemoteControler();
  Value[2] = Value[1];
  Value[1] = Value[0];
  Value[0] = Figure;
  display.clear();
  display.setCursor( 0, 3 );
  display.print( Value[0] );
  display.setCursor( 0, 2 );
  display.print( Value[1] );
  display.setCursor( 0, 1 );
  display.print( Value[2] );
  event_switcher( E04 );
}
void RemoteControler( void ) {
  switch ( CurrentValue ) {
    case _UP    : EventID = E05; return;
    case _DOWN  : EventID = E06; return;
    case _LEFT  : EventID = E07; return;
    case _RIGHT : EventID = E08; return;
    case _STAR  : EventID = E09; return;
    case _NUMBER: EventID = E10; return;
    case _CENTER: EventID = E11; return;
    case _0 : Figure = 0; break;
    case _1 : Figure = 1; break;
    case _2 : Figure = 2; break;
    case _3 : Figure = 3; break;
    case _4 : Figure = 4; break;
    case _5 : Figure = 5; break;
    case _6 : Figure = 6; break;
    case _7 : Figure = 7; break;
    case _8 : Figure = 8; break;
    case _9 : Figure = 9; break;
    default : return;
  }
}
//////////////////////////////////////////////////////////////////////////////
//  event_switcher()  event_switcher()  event_switcher()  event_switcher()
//////////////////////////////////////////////////////////////////////////////
void _15( void )
{
  stepper.disableOutputs();
  if ( DirectSwitch ) return;
  EventID = TemporaryEventID;
}
