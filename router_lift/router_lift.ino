//  Router Lift ( since 8 March 2019 ) YouTube : https://youtu.be/iJBeFyT2lb0　My Blog : https://plaza.rakuten.co.jp/kachyun/diary/?ctgy=9

void setup()
{
  setup_limit_switch();
  setup_infrared();
  setup_stepper();
  setup_7_segment();
}

void loop()
{
  limit_checker();
  infrared_checker();
  event_dispatcher();
}

// event dispatcher
enum  EVENT_ID_number { E00,E01,E02,E03,E04,E05,E06,E07,E08,E09,E10,E11,E12,E13,E14,E15 };
void ( *event[] )() = { _00,_01,_02,_03,_04,_05,_06,_07,_08,_09,_10,_11,_12,_13,_14,_15 };
static uint8_t EventID = E00;
void event_dispatcher( void ) { ( *event[ EventID ] )(); }

static uint8_t TemporaryEventID;
void event_switcher( uint8_t e )
{
  TemporaryEventID = e;
  EventID = E15;
}
