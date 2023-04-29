#include <WiFi.h>
#include <FirebaseESP32.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your Wi-Fi network credentials
const char* ssid = "AIRLANGGA-HOTSPOT";
const char* password = "@irlangg@";

// Replace with your Firebase project's settings
#define FIREBASE_HOST "https://arsenik-v2-default-rtdb.firebaseio.com"
#define FIREBASE_API_KEY "AIzaSyB4COq4ZQ44HzgP3osGIUa5OA9XHjt7Xgs"

FirebaseData firebaseData;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200, 60000);

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_API_KEY);

  timeClient.begin();
  timeClient.setTimeOffset(25200);
  configTime(25200, 0, "pool.ntp.org"); // Get the time from the NTP server

}

void dataUpload(){
 //Date and Time
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  
  // Format the date in DD/MM/YYYY format
  char date[11]; // Allocate a buffer to store the formatted date
  strftime(date, 11, "%d/%m/%Y", timeinfo);
  String dateString = String(date); // Convert the char array to a String

  // Format the time in 00:00:00 format
  char time[9]; // Allocate a buffer to store the formatted time
  strftime(time, 9, "%T", timeinfo);
  String timeString = String(time); // Convert the char array to a String


 // Stored Objects
  String a = "A";
  int suhu = random(18, 29);
  int ph = random(8, 14);
  int tds = random(500, 1000);
  int volTur = random(5);
  int ecVal = random(1, 4);
  int orp = random(-50, 100);
  int disOx = random(4, 12);
  String latid = "-7.265484";
  String longit = "112.784754"; 

  // Store the numbers in a string
  String dataStr1 = "";
  dataStr1 += String(a) + ",";
  dataStr1 += String(tds) + ",";
  dataStr1 += String(suhu) + ",";
  dataStr1 += String(orp) + ",";
  dataStr1 += String(ph) + ",";
  dataStr1 += String(volTur) + ",";
  dataStr1 += String(ecVal) + ",";
  dataStr1 += String(disOx) + ",";
  dataStr1 += String(latid) + ",";
  dataStr1 += String(longit) + ",";
  dataStr1 += String(dateString) + ",";
  dataStr1 += String(timeString) + ",";
  dataStr1 += String(a);

  Serial.println("dataStr1 " + dataStr1);

  // Upload the string to Firebase Realtime Database
  if (Firebase.setString(firebaseData, "/dataStr1", dataStr1)) {
    Serial.println("Data uploaded to Firebase");
  } else {
    Serial.println("Failed to upload data to Firebase");
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {
  dataUpload();
  delay(5000);
}
