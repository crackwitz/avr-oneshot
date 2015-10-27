bool timerphase = 0;

ISR(TIMER0_OVF_vect)
{
  OCRA = -OCRA;
  timerphase = !timerphase;
}

void setup_timer0()
{
  TCCR0A = 0b10 << COM0A0;
  //TCCR0A |= 0b10 << COM0B0;

  // wgm 3, b011
  TCCR0A |= _BV(WGM01) | _BV(WGM00);
  TCCR0B = 0*_BV(WGM02);
  TCCR0B |= 0b011 << CS00; // 011=64

  OCR0A = 1;

  //TIMSK0 |= _BV(OCIE0B);
  //TIMSK0 |= _BV(OCIE0A);
  //TIMSK0 |= _BV(TOIE0);
}

int main()
{
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  Serial.println("Hallo!");

  // wgm: 14: TOP=ICR1
  TCCR1A = _BV(WGM11) | 0*_BV(WGM10);
  TCCR1B = _BV(WGM13) | _BV(WGM12);
  TCCR1B |= 0b101 << CS10; // b101 = /1024

  TIMSK1 |= _BV(OCIE1A);
  TIMSK1 |= _BV(OCIE1B);
  TIMSK1 |= _BV(TOIE1);

  ICR1 = 0x0000;
  TCNT1 = 0;

  start = (int16_t)(-0.008 * 16e6 / 1024);
  OCR1A = (int16_t)(-0.004 * 16e6 / 1024);
  OCR1B = (int16_t)(-1);

  // start = -2;  OCR1B = -1;

  Serial.println(OCR1A);
  Serial.println(OCR1B);

  sei();

  while (true)
  {
    if (Serial.available() > 0)
    {
      Serial.read();
      TCNT1 = start;
      Serial.println("Bang!");
    }
    if (TCNT1 > 0)
    {
      //Serial.println(TCNT1);
    }
  }
}

