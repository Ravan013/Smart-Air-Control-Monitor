#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Miramin2";
const char* password = "miramin123";

AsyncWebServer server(80);



#include <SoftwareSerial.h>


#define irsensor1 D1
#define irsensor2 D2
#define irsensor3 D7
#define irsensor4 D8

String sensor1;
String sensor2;
String sensor3;
String sensor4;


String com_data = "";



void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  delay(1000);

  pinMode(irsensor1, INPUT);
  pinMode(irsensor2, INPUT);
  pinMode(irsensor3, INPUT);
  pinMode(irsensor4, INPUT);
  Serial.println("Vehicle Detection");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    String html = "<html><head><meta http-equiv=\"refresh\" content=\"3\"></head><body>";
    html += "<h1>Parking Lot Status</h1>";
    html += "<p>Slot 1: " + sensor1 + "</p>";
    html += "<p>Slot 2: " + sensor2 + "</p>";
    html += "<p>Slot 3: " + sensor3 + "</p>";
    html += "<p>Slot 4: " + sensor4 + "</p>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });
  server.begin();
}



void loop() {
  slot1();
  slot2();
  slot3();
  slot4();


  digitalWrite(irsensor1, HIGH);
  digitalWrite(irsensor2, HIGH);
  digitalWrite(irsensor3, HIGH);
  digitalWrite(irsensor4, HIGH);

  // Get the current time
  time_t now = time(nullptr);
  // Format the time to "hours:minutes:seconds"
  char buf[sizeof "HH:MM:SS"];
  strftime(buf, sizeof buf, "%H:%M:%S", localtime(&now));
  // Print the formatted time followed by the sensor data
  Serial.print(buf);
  Serial.print(":");
  com_data = "Slot 1:" + sensor1 + "," + "Slot 2:" + sensor2 + "," + "Slot 3:" + sensor3 + "," + "Slot 4:" + sensor4;
  Serial.println(com_data);
  delay(3000); // 100 milli seconds
}




void slot1()
{
  if ( digitalRead(irsensor1) == HIGH)
  {
    sensor1 = "Occupied";
  }
  else
  {
    sensor1 = "Vacant";
  }

}



void slot2()
{
  if ( digitalRead(irsensor2) == HIGH)
  {
    sensor2 = "Occupied";
  }
  else
  {
    sensor2 = "Vacant";

  }
}

void slot3()
{
  if ( digitalRead(irsensor3) == HIGH)
  {
    sensor3 = "Occupied";

  }
  else
  {
    sensor3 = "Vacant";

  }
}


void slot4()
{
  if ( digitalRead(irsensor4) == HIGH)
  {
    sensor4 = "Occupied";

  }
  else
  {
    sensor4 = "Vacant";

  }
}
