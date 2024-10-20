//#include <ThingSpeak.h>               // add librery
//#include <ESP8266WiFi.h>
//
//#include <LiquidCrystal.h>
//const int RS = D2, EN = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;
//LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);
//
//WiFiClient  client;
//unsigned long counterChannelNumber = 2327395;                // Channel ID
//const char * myCounterReadAPIKey = "A1RB4Z1EVJI3Y4MT";      // Read API Key
//const int FieldNumber1 = 1;                                 // The field you wish to read
//String presentStr,previousStr = " ";
//
//void setup()
//{
//  lcd.begin(16, 2);
//  Serial.begin(115200);
//  Serial.println();
//
//  WiFi.begin("iMx", "9313511918");                 // write wifi name & password 511918
//
//  Serial.print("Connecting");
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println();
//  Serial.print("Connected, IP address: ");
//  Serial.println(WiFi.localIP());
//  ThingSpeak.begin(client);
//}
//
//void loop() 
//{
// presentStr = ThingSpeak.readStringField((counterChannelNumber), (FieldNumber1), myCounterReadAPIKey);
//
//
//if (presentStr[0]== '0'){
//  presentStr = presentStr.substring(1);
//}
// 
// if(presentStr != previousStr)
// {
//  lcd.clear();
//  Serial.println(presentStr);
//  lcd.setCursor(0, 0);
//  lcd.autoscroll();
//  lcd.print(presentStr);
////  lcd.setCursor(0,0);
////  lcd.print(presentStr);
//  previousStr = presentStr;
// }
//}



#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>

const int RS = D2, EN = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

WiFiClient client;
unsigned long counterChannelNumber = 2327395;                // Channel ID
const char *myCounterReadAPIKey = "A1RB4Z1EVJI3Y4MT";      // Read API Key
const int FieldNumber1 = 1;                                 // The field you wish to read
String presentStr, previousStr = " ";
int scrollPosition = 15;
int scrollDelay = 5;  // Adjust this value to control scrolling speed

void setup() {
  lcd.begin(16, 2);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("iMx", "9313511918");                 // write wifi name & password
  WiFi.begin("MR. Nk MISHRA", "Navinkumarrrr");                 // write wifi name & password

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() {
  presentStr = ThingSpeak.readStringField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);

  if (presentStr[0] == '0') {
    presentStr = presentStr.substring(1);
  }

  if (presentStr != previousStr) {
    lcd.clear();
    Serial.println(presentStr);
    scrollPosition = 0; // Reset scroll position
    lcd.setCursor(0, 0);
    lcd.print(presentStr.substring(scrollPosition, 16)); // Display the first 16 characters
    previousStr = presentStr;
  }

  // Scroll the text
  if (presentStr.length() > 16) {
    delay(scrollDelay);
    scrollPosition++;
    if (scrollPosition > presentStr.length() - 16) {
      scrollPosition = 0; // Reset scroll position when the end is reached
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(presentStr.substring(scrollPosition, scrollPosition + 16));
  }
}
