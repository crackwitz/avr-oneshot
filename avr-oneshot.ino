ISR(TIMER1_COMPB_vect)
{
  digitalWrite(13, !digitalRead(13));
  //digitalWrite(13, 1);
}

ISR(TIMER1_OVF_vect)
{
  digitalWrite(13, !digitalRead(13));
  //digitalWrite(13, 0);
}

int main()
{
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  Serial.println("Hallo!");

  // wgm: 15: TOP=OCR1A
  TCCR1A = _BV(WGM11) | _BV(WGM10);
  TCCR1B = _BV(WGM13) | _BV(WGM12);
  TCCR1B |= 0b101 << CS10; // b101 = /1024

  TIMSK1 |= _BV(OCIE1B);
  //TIMSK1 |= _BV(TOIE1);

  OCR1A = 0x0000;
  TCNT1 = 0;

  uint16_t start = (int16_t)(-0.2 * 16e6 / 1024)-1;
  OCR1B = (int16_t)(-0.2 * 16e6 / 1024);

  start = -2;
  OCR1B = -1;

  Serial.println(start);
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
      Serial.println(TCNT1);
    }
  }
}

