boolean xml_handler(TinyWebServer& web_server) {
    Client& client = web_server.get_client();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/xml");
    client.println("Connection: keep-alive");
    client.println();
    client.println("<?xml version=\"1.0\"?>");
    client.println("<Lampen>");
    client.print("  <DatumTijd>");
    if(hour() < 10)client.print("0");client.print(hour()); client.print(":");if(minute() < 10)client.print("0");client.print(minute());
    client.print(" ");
    client.print(day());client.print("/");client.print(month());client.print("/");client.print(year());
    client.println("</DatumTijd>");
    client.println("  <input-schakelaar>");
    client.print("    <schakelaar1>");client.print(lamp1status);client.println("</schakelaar1>");
    client.print("    <schakelaar2>");client.print(lamp2status);client.println("</schakelaar2>");
    client.print("    <schakelaar3>");client.print(lamp3status);client.println("</schakelaar3>");
    client.print("    <schakelaar4>");client.print(lamp4status);client.println("</schakelaar4>");
    client.println("  </input-schakelaar>");
    client.println("  <input-dimmer>");
    client.print("    <dimmer1>");client.print(20);client.println("</dimmer1>");
    client.print("    <dimmer2>");client.print(0);client.println("</dimmer2>");
    client.print("    <dimmer3>");client.print(80);client.println("</dimmer3>");
    client.print("    <dimmer4>");client.print(50);client.println("</dimmer4>");
    client.println("  </input-dimmer>");
    client.println("</Lampen>");
    return true;
}
