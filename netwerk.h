boolean file_handler(TinyWebServer& web_server);
boolean index_handler(TinyWebServer& web_server);

void send_file_name(TinyWebServer& web_server, const char* filename) {
  LED('W');
  if (!filename) {
    web_server.send_error_code(404);
    web_server << F("Could not parse URL");
  } else {
    TinyWebServer::MimeType mime_type = TinyWebServer::get_mime_type_from_filename(filename);
    web_server.send_error_code(200);
    if (file.open(&root, filename, O_READ)) {
      web_server.send_content_type(mime_type);
      web_server.end_headers();
      Serial << F("Read file "); Serial.println(filename);
      web_server.send_file(file);
      file.close();
  } else {
      web_server.send_content_type("text/plain");
      web_server.end_headers();
      Serial << F("Could not find file: "); Serial.println(filename);
      web_server << F("Could not find file: ") << filename << "\n";
    }
  }
}

boolean file_handler(TinyWebServer& web_server) {
  char* filename = TinyWebServer::get_file_from_path(web_server.get_path());
  send_file_name(web_server, filename);
  free(filename);
  return true;
}

boolean index_handler(TinyWebServer& web_server) {
  send_file_name(web_server, "INDEX.HTM");
  return true;
}

boolean boileraltijdaan_handler(TinyWebServer& web_server) {
  Serial.print("Boiler aan");
  boileraltijdaan = !boileraltijdaan;
  eepromwl.write(16, boileraltijdaan);
  boileraltijduit = 0;
  eepromwl.write(17, boileraltijduit);
  return true; 
}

boolean boileraltijduit_handler(TinyWebServer& web_server) {
  Serial.print("Boiler uit");
  boileraltijduit = !boileraltijduit;
  eepromwl.write(17, boileraltijduit);
  boileraltijdaan = 0;
  eepromwl.write(16, boileraltijdaan);
  return true; 
}

boolean boilerreset_handler(TinyWebServer& web_server) {
  Serial.print("Boiler reset");
  boilerstatus = 0;
  eepromwl.write(13, boilerstatus);
  boileraan = 5;
  eepromwl.write(14, boileraan);
  boileruit = 7;
  eepromwl.write(15, boileruit);
  boileraltijdaan = 0;
  eepromwl.write(16, boileraltijdaan);
  boileraltijduit = 0;
  eepromwl.write(17, boileraltijduit);
  return true; 
}

boolean reboot_handler(TinyWebServer& web_server) {
  Serial.print("Herstarten!");
  while(true);
}

TinyWebServer::PathHandler handlers[] = {
  {"/", TinyWebServer::GET, &index_handler },
  {"/" "status.xml*", TinyWebServer::GET, &xml_handler },
<<<<<<< HEAD
  {"/PEER/" "*", TinyWebServer::GET, &file_handler },
=======
>>>>>>> parent of 0dcebcd... Aanpassing HTML om laden sneller te krijgen
  {"/" "schakelaar*", TinyWebServer::GET, &schakelaar_handler },
  {"/" "alloff*", TinyWebServer::GET, &alloff_handler },
  {"/" "boileraltijdaan*", TinyWebServer::GET, &boileraltijdaan_handler },
  {"/" "boileraltijduit*", TinyWebServer::GET, &boileraltijduit_handler },
  {"/" "boilerreset*", TinyWebServer::GET, &boileraltijduit_handler },
  {"/" "reboot", TinyWebServer::GET, &reboot_handler },
  {"/" "*", TinyWebServer::GET, &file_handler },
  {NULL},
};

TinyWebServer web = TinyWebServer(handlers, NULL);

void Netwerkinit(){ //Netwerk initialisatie
    LED('W');
    Ethernet.begin(MAC, IP, DNS, GATEWAY, SUBNET); //Alleen MAC voor DHCP
    web.begin();
    Dns.begin(Ethernet.dnsServerIP()); //DNS
    udp.begin(5678); //zet UDP poort 5678
}

byte socketStat[MAX_SOCK_NUM];

void ShowSockStatus()
{
  for (int i = 0; i < MAX_SOCK_NUM; i++) {
    Serial.print(F("Socket#"));
    Serial.print(i);
    uint8_t s = W5100.readSnSR(i);
    socketStat[i] = s;
    Serial.print(F(":0x"));
    Serial.print(s,16);
    Serial.print(F(" "));
    Serial.print(W5100.readSnPORT(i));
    Serial.print(F(" D:"));
    uint8_t dip[4];
    W5100.readSnDIPR(i, dip);
    for (int j=0; j<4; j++) {
      Serial.print(dip[j],10);
      if (j<3) Serial.print(".");
    }
    Serial.print(F("("));
    Serial.print(W5100.readSnDPORT(i));
    Serial.println(F(")"));
  }
}

