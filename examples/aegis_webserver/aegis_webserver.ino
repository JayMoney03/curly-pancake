#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char* ssid = "AEGIS_IDENTITY";
const char* password = "security_handshake"; // You can change this

WebServer server(80);

// This is the HTML that will show up on your phone
String getHTML() {
  String chipID = String((uint32_t)ESP.getEfuseMac(), HEX);
  chipID.toUpperCase();
  
  String page = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<style>";
  page += "body{font-family:monospace; background:#000; color:#0f0; text-align:center; margin:0; padding:20px;}";
  page += ".status{border:2px solid #0f0; padding:20px; margin:20px auto; border-radius:10px; box-shadow:0 0 20px #0f0; max-width:500px;}";
  page += "h1{text-shadow:0 0 10px #0f0; animation:flicker 2s infinite; font-size:2em;}";
  page += "@keyframes flicker{0%,100%{opacity:1;}50%{opacity:0.8;}}";
  page += "p{margin:10px 0; font-size:1.1em;}";
  page += ".highlight{color:#0ff; font-weight:bold;}";
  page += "</style></head>";
  page += "<body><h1>⬢ AEGIS HORIZON ⬢</h1>";
  page += "<div class='status'><h3>SYSTEM STATUS</h3>";
  page += "<p>✓ Identity Chip: <span class='highlight'>ONLINE</span></p>";
  page += "<p>Hardware ID: <span class='highlight'>" + chipID + "</span></p>";
  page += "<p>Uptime: <span class='highlight'>" + String(millis()/1000) + "s</span></p>";
  page += "</div></body></html>";
  return page;
}

void setup() {
  Serial.begin(115200);
  
  // Start the Hotspot
  WiFi.softAP(ssid, password);
  Serial.println("Hotspot Started: " + String(ssid));
  Serial.print("IP Address for Phone: ");
  Serial.println(WiFi.softAPIP());
  
  // Start mDNS
  if (MDNS.begin("aegis")) {
    Serial.println("mDNS responder started: http://aegis.local");
  }
  
  // Handle the web requests
  server.on("/", []() {
    server.send(200, "text/html", getHTML());
  });
  
  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();
}
