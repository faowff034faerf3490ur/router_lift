void print_multiplier( void )
{
  display.setCursor( 0, 0 );
  switch( Multiplier ) {
    case 1: display.print( "   1" ); break;
    case 2: display.print( "  10" ); break;
    case 3: display.print( "  50" ); break;
    case 4: display.print( " 100" ); break;
    case 5: display.print( " 200" ); break;
  }
  display.blink();
  print_target_position(0);
}

static long Offset;

void print_target_position( long t )
{
  long t1 = stepper.currentPosition() - Offset + t;
  long t2 = abs( t1 );
  display.clear();
  if ( t1 < 0 ) {
    display.setCursor( 0, 3 - get_digit( t2 / 80 ) );
    display.print( "-" );
  }
  display.setCursor( 0, 4 - get_digit( t2 / 80 ) );
  display.print( t2 / 80 );
}

unsigned get_digit(unsigned num)
{
    unsigned digit = 0;
    while( num != 0 ) { num /= 10; digit++; }
    return digit;
}