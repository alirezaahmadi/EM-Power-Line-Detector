void mode_change(byte selection_index)
{
  if (selection_index == 0) {
    digitalWrite(A1, 0);
    digitalWrite(A2, 0);
    digitalWrite(A3, 0);
  }
  if (selection_index == 1) {
    digitalWrite(A1, 1);
    digitalWrite(A2, 0);
    digitalWrite(A3, 0);
  }
  if (selection_index == 2) {
    digitalWrite(A1, 0);
    digitalWrite(A2, 1);
    digitalWrite(A3, 0);
  }
  if (selection_index == 3) {
    digitalWrite(A1, 1);
    digitalWrite(A2, 1);
    digitalWrite(A3, 0);
  }
  if (selection_index == 4) {
    digitalWrite(A1, 0);
    digitalWrite(A2, 0);
    digitalWrite(A3, 1);
  }
  if (selection_index == 5) {
    digitalWrite(A1, 1);
    digitalWrite(A2, 0);
    digitalWrite(A3, 1);
  }
  if (selection_index == 6) {
    digitalWrite(A1, 0);
    digitalWrite(A2, 1);
    digitalWrite(A3, 1);
  }
  if (selection_index == 7) {
    digitalWrite(A1, 1);
    digitalWrite(A2, 1);
    digitalWrite(A3, 1);
  }
}

void Signal_show_value(byte Channel, byte _x, byte _y, byte add_x2, byte add_y2, byte txt_size)
{
  myGLCD.setFont(MediumNumbers);
  if (Channel == 0)
  {
    analog_value = analogRead(A0);
    tmp = (analog_value * 5.0) / 1024.0;
    Signal[0]=tmp*10;
    myGLCD.printNumI(Signal[0],_x, _y);
  }
  if (Channel == 1)
  {
    analog_value = analogRead(A6);
    tmp = (analog_value * 5.0) / 1024.0;
    Signal[1]=tmp*10;
    myGLCD.printNumI(Signal[1],_x, _y);
  }
  if (Channel == 2)
  {
    analog_value = analogRead(A0);
    tmp = (analog_value * 5.0) / 1024.0;
    Signal[0]=tmp*10;
    myGLCD.printNumF(Signal[0],0,_x, _y);
    
    analog_value = analogRead(A6);
    tmp = (analog_value * 5.0) / 1024.0;
    Signal[1]=tmp*10;
    myGLCD.printNumF(Signal[1],1,_x + add_x2, _y + add_y2);
  }
  if (Channel == 3)
  {
    analog_value = analogRead(A0);
    tmp = (analog_value * 5.0) / 1024.0;
    Signal[0]=tmp*10;
    myGLCD.printNumF(Signal[0],1,_x, _y);
    
    analog_value = analogRead(A6);
    tmp = (analog_value * 5.0) / 1024.0;
    Signal[1]=tmp*10;
    myGLCD.printNumF(Signal[1],1,_x + add_x2, _y + add_y2);
  }
  myGLCD.setFont(SmallFont);
}

void Update_Signals(void)
{
  analog_value = analogRead(A0);
  tmp = (analog_value * 5.0) / 1024.0;
  Signal[0]=tmp*10;
  delay(5);
  analog_value = analogRead(A6);
  tmp = (analog_value * 5.0) / 1024.0;
  Signal[1]=tmp*10;
  delay(5);
}

byte button_press(byte Btn_Num, unsigned short Debaouce)
{
  Debaouce=100;
  if (digitalRead(Btn_Num) == 0)
  {
    elapsed = (unsigned short)millis();
    for (;;)
    {
      if ((unsigned short)Debaouce < (unsigned short)(millis() - elapsed))
      {
        
        if (Btn_Num == Select_Btn)
        {
          Buzzer(10, 255, 1);
        }
        else
        {
          Buzzer(10, 10, 1);
        }
        elapsed=0;
        myGLCD.clrScr();
        return 0;
        break;
      }
    }
  }
}

void Buzzer(byte _delay, byte volume, byte Count)
{
  if(EEPROM.read(Pow_Setting_EEPROM_ADD+1)==1)volume=0;
  for (cnt = 0; cnt < Count; cnt++)
  {
    analogWrite(10, volume);
    delay(_delay);
    analogWrite(10, 0);
    if (Count > 1)
    {
      delay(_delay);
    }
  }
}


