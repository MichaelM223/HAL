void RTCopstart(){
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet){
      LED('Y');
      delay(1000);
      tijdcheck = 0;
      Serial.println("RTC niet gevonden");
  } else {
  tijdcheck = 1;
  Serial.println("RTC tijd:");
  if(hour() < 10)Serial.print("0");Serial.print(hour()); Serial.print(":");if(minute() < 10)Serial.print("0");Serial.print(minute());Serial.print(":");if(second() < 10)Serial.print("0");Serial.print(second());
  Serial.print(" ");
  Serial.print(day());Serial.print("/");Serial.print(month());Serial.print("/");Serial.println(year());
  }
}

void Boilercheck(){
  if(hour() < boileruit && hour() >= boileraan && boilerstatus == 0 && boileraltijduit == 0){
    boilerstatus = 1;
    eepromwl.write(13, boilerstatus); 
  }else if((hour() >= boileruit || hour() < boileraan) && boilerstatus == 1 && boileraltijdaan == 0){
    boilerstatus = 0;
    eepromwl.write(13, boilerstatus); 
  }else if(boilerstatus == 0 && boileraltijdaan == 1){
    boilerstatus = 1;
    eepromwl.write(13, boilerstatus); 
  }
  delay(1000); //delay voor veiligheid in geval van fout in bovenstaande loop
  digitalWrite(8, boilerstatus);
}
