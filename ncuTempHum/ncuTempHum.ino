#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>   
#include "DHT.h"
#include <TimeLib.h>
#include <WiFiUdp.h>

static const char ntpServerName[] = "de.pool.ntp.org"; //"us.pool.ntp.org";

const int timeZone = 0;  // UTC
// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

/*Put your SSID & Password*/
const char* ssid = "ssid";  // Enter SSID here
const char* password = "pwd";  //Enter Password here
// Variables needed for NTP
// Elasticsearch needs us to generate timestamps for the data in order to make date histograms in Kibana.
WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets
time_t getNtpTime();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);
// This is the IP address, or DNS name of the Elasticsearch instance.
const char* host = "192.168.2.115";
int sensID = 3;
const int port = 9200;
ESP8266WebServer server(80);

// DHT Sensor
uint8_t DHTPin = D8;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

String timestamp;
time_t start_time;
float Temperature;
float Humidity;
uint32_t t_ms;
uint32_t start_mills;
String run_mills;
byte mac[6];
String mac_string;
int milis_chars;

void setup() {
  Serial.begin(74880);
  WiFiManager wifiManager;
  Serial.println("Waiting for WiFi credentials...");
  wifiManager.autoConnect("Freshly");
  delay(100);

  pinMode(DHTPin, INPUT);

  dht.begin();

  //Serial.println("Connecting to ");
  //Serial.println(ssid);

  //WiFi.config()
  //connect to your local wi-fi network
  //WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
  WiFi.macAddress(mac);
  mac_string = String(mac[0], HEX) + String(mac[1], HEX) + String(mac[2], HEX) + String(mac[3], HEX) + String(mac[4], HEX) + String(mac[5], HEX);

  Serial.println("Setting up NTP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  setSyncInterval(300);
  Serial.print("Start time: ");
  Serial.println(now());
  start_time = now();

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {

  server.handleClient();
  // Use WiFiClient class to create TCP connections, connect to the Elasticsearch instance.
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }
  float temp = dht.readTemperature(); // Gets the values of the temperature
  float hum = dht.readHumidity(); // Gets the values of the humidity
  run_mills = String(millis());
  milis_chars = run_mills.length();
  timestamp = String(now()) + run_mills.charAt(milis_chars - 3) + run_mills.charAt(milis_chars - 2) + run_mills.charAt(milis_chars - 1);
  String data = "{sensID: "+ String(sensID) + ",humidity: " + String(hum) + ",temperature: " + String(temp) + ",timestamp: " +timestamp+ "}";
  Serial.println(data);
  // We now create a URI for the request
  // This is the index of the Elasticsearch document we're creating
  String url = "/weather/reading";
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               // If you're using Shield, you'll need to generate an authentication header
               "Content-Length: " + data.length() + "\r\n" +
               "\r\n" + data);
  // We need this delay in here to give the WiFi Time
  delay(50);
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  // every 10 seconds
  delay(10000);
}

void handle_OnConnect() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity
  server.send(200, "text/html", SendHTML(Temperature, Humidity, sensID, mac_string));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
String SendHTML(float Temperaturestat, float Humiditystat, int sensID, String mac_string) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr += "<title>";
  ptr += (int)sensID + " MAC: " + mac_string;
  ptr += " Status Report</title>\n";
  ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}\n";
  ptr += "body{margin-top: 50px;}\n";
  ptr += "h1 {margin: 50px auto 30px;}\n";
  ptr += ".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n";
  ptr += ".humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 36px;}\n";
  ptr += ".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr += ".humidity{font-weight: 300;font-size: 60px;color: #3498db;}\n";
  ptr += ".temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n";
  ptr += ".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr += ".temperature{font-weight: 300;font-size: 60px;color: #f39c12;}\n";
  ptr += ".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n";
  ptr += ".data{padding: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Status Report Messstation: ";
  ptr += (int)sensID;
  ptr += "</h1>\n";
  ptr += "<div class=\"data\">\n";
  ptr += "<div class=\"side-by-side temperature-icon\">\n";
  ptr += "<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n";
  ptr += "width=\"9.915px\" height=\"22px\" viewBox=\"0 0 9.915 22\" enable-background=\"new 0 0 9.915 22\" xml:space=\"preserve\">\n";
  ptr += "<path fill=\"#FFFFFF\" d=\"M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142\n";
  ptr += "c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491\n";
  ptr += "c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463\n";
  ptr += "c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394\n";
  ptr += "c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z\"/>\n";
  ptr += "</svg>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"side-by-side temperature-text\">Temperature</div>\n";
  ptr += "<div class=\"side-by-side temperature\">";
  ptr += (int)Temperaturestat;
  ptr += "<span class=\"superscript\">°C</span></div>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"data\">\n";
  ptr += "<div class=\"side-by-side humidity-icon\">\n";
  ptr += "<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n\"; width=\"12px\" height=\"17.955px\" viewBox=\"0 0 13 17.955\" enable-background=\"new 0 0 13 17.955\" xml:space=\"preserve\">\n";
  ptr += "<path fill=\"#FFFFFF\" d=\"M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057\n";
  ptr += "c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217\"></path>\n";
  ptr += "</svg>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"side-by-side humidity-text\">Humidity</div>\n";
  ptr += "<div class=\"side-by-side humidity\">";
  ptr += (int)Humiditystat;
  ptr += "<span class=\"superscript\">%</span></div>\n";
  ptr += "</div>\n";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}


/* Copied from https://github.com/PaulStoffregen/Time/blob/master/examples/TimeNTP_ESP8266WiFi/TimeNTP_ESP8266WiFi.ino#L99 */
/*-------- NTP code ----------*/
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
