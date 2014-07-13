/*
Adressen in EEPROM:
1 t/m 6 lampen
7 t/m 12 dimmers (1 byte is 255 dimwaardes)
13 t/m 16 boiler
lamp1status = 1 
lamp2status = 2
lamp3status = 3
lamp4status = 4
lamp5status = 5
lamp6status = 6

boilerstatus = 13
boileraan = 14
boileruit = 15
boileroverride = 16
*/

void EEPROMinit(){
  eepromwl.write(127, 223);
  if(eepromwl.read(127) == 223){
    lamp1status = eepromwl.read(1);
    lamp2status = eepromwl.read(2);
    lamp3status = eepromwl.read(3);
    lamp4status = eepromwl.read(4);
    lamp5status = eepromwl.read(5);
    lamp6status = eepromwl.read(6);
    boilerstatus = eepromwl.read(13);
    boileroverride = eepromwl.read(16);
    if(boilerstatus > 1 || boileroverride > 1){
      boilerstatus = 0;
      eepromwl.write(13, boilerstatus);
      boileroverride = 0;
      eepromwl.write(16, boileroverride);
    }
    boileraan = eepromwl.read(14);
    boileruit = eepromwl.read(15);
    if(boileraan < 0 || boileruit > 24){
      boileraan = 5;
      eepromwl.write(14, boileraan);
      boileruit = 7;
      eepromwl.write(15, boileruit);
    }
  }else{
    while(true)LED('C');
  }
}
