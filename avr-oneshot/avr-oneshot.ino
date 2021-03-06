uint16_t start = 0;

ISR(TIMER1_COMPA_vect)
{
  PORTB ^= _BV(PORTB5);
}

ISR(TIMER1_COMPB_vect)
{
  PORTB ^= _BV(PORTB5);
}

ISR(TIMER1_OVF_vect)
{
  TCNT1 = start;
  //PORTB ^= _BV(PORTB5);
  //digitalWrite(13, 0);
  //reti();
}

void setup_timer1()
{
  
}

void setup_timer0()
{
  
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

  start = (int16_t)(-0.8 * 16e6 / 1024);
  OCR1A = (int16_t)(-0.2 * 16e6 / 1024);
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

