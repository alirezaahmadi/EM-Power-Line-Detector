/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% by: Alireza Ahmadi                                     %
% University of Bonn- MSc Robotics & Geodetic Engineering%
% Alireza.Ahmadi@uni-bonn.de                             %
% AlirezaAhmadi.xyz                                      %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
void EEPROM_Write_default()
{
  byte i=0;
  byte EE_Array[16];
  i=0;
  
  for(byte EE_cnt=0 ; EE_cnt<16 ; EE_cnt++)
  {
    EE_Array[i]=EEPROM.read(EE_cnt);
  }
  i=0;
  
  for(byte EE_line=0 ; EE_line<16 ; EE_line++)
  {
    for(byte EE_cul=0 ; EE_cul<2 ; EE_cul++)
    {
      limit_tmp[EE_line][EE_cul] = EE_Array[i];
      i++;
    }
  }
  i=0;
  TMP_to_Main_EEPROM(0);

  for(byte EE_cnt=GA_EEPROM_ADD ; EE_cnt<8 ; EE_cnt++)
  {
    EE_Array[i]=EEPROM.read(EE_cnt);
  }
  i=0;
  
  ///?????


  
  for(byte EE_cnt=Pow_Setting_EEPROM_ADD ; EE_cnt<4 ; EE_cnt++)
  {
    EE_Array[i]=EEPROM.read(EE_cnt);
  }
  i=0;
  
  ///?????
  
}

void EEPROM_Read(int start_add)
{
  byte i=0;
  byte EE_Array[16];
  i=0;
  
  for(byte EE_cnt=start_add ; EE_cnt<start_add+16 ; EE_cnt++)
  {
    EE_Array[i]=EEPROM.read(EE_cnt);
    //Serial.println(EE_Array[i]);
    i++;
  }
  i=0;
  
  for(byte EE_line=0 ; EE_line<16 ; EE_line++)
  {
    for(byte EE_cul=0 ; EE_cul<2 ; EE_cul++)
    {
      limit_tmp[EE_line][EE_cul] = EE_Array[i];
      i++;
    }
  }
  i=0;
}

void Reset_EEPROM(void)
{
  for(int EE_cnt=0 ; EE_cnt<27 ; EE_cnt++)
  {
    EEPROM.write(EE_cnt,0);
  }
}

void TMP_to_Main_EEPROM(byte Action)
{
  if(Action==0)
  {
    for(byte _y=0 ; _y<16 ; _y++)
    {
      for(byte _x=0 ; _x<2 ; _x++)
      {
        limit[_y][_x] = limit_tmp[_y][_x];
      }
    }
  }
  if(Action==1)
  {
    for(byte _y=0 ; _y<16 ; _y++)
    {
      for(byte _x=0 ; _x<2 ; _x++)
      {
        limit_tmp[_y][_x] = limit[_y][_x];
      }
    }
  }
}

void Backup_to_Main_EE(void)
{
  byte EE_Array[27];
  EEPROM.write(99,103);
  for(int EE_cnt=30 ; EE_cnt<57 ; EE_cnt++)
  {
    EE_Array[EE_cnt - 30]=EEPROM.read(EE_cnt);
    delay(5);
    EEPROM.write(EE_cnt - 30 ,EE_Array[EE_cnt - 30]);
    delay(5);
  }

  EEPROM_Read(0);
  TMP_to_Main_EEPROM(0);

}



