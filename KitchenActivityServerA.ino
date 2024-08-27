/*
  Secure time request demo
  using esp32 
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "Add network name";
const char* password = "Add network pw";


// global wifi client
WiFiClientSecure *client = new WiFiClientSecure;
WiFiServer server(80);


// holds request headers
String header;

volatile unsigned long lastPressMs;

char lastBuff[100] = "Running";

// button
#define sensorPin 26

// NTP server to request epoch time
const char* ntpServer = "pool.ntp.org";

// Variable to save current epoch time
unsigned long epochTime;

// html constants
String upperHtml = "<!doctype html> <html lang=\"en\"> <head> <meta charset=\"utf-8\" /> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" /> <title>system info</title> <style> body { font-family: arial, sans-serif; background-color: #f0f0f0; color: #333; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; } .container { background-color: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); text-align: center; } h1 { margin-bottom: 20px; } p { font-size: 1.2em; margin: 10px 0; } .recentactivity{ background-color:aqua; border-radius:5px; } </style> </head> <br> <div class=\"container\"> <h1>kitchen dashboard</h1> <p id=\"boottime\">boot time:</p> <div id=\"recentactivity\" class=\"recentactivity\"> <h1>recent activity</h1> <p id=\"lastupdate\">last update time:</p> </div> </div> <br> <script> const startuptime =";

String lowerHtml = "function formatdate(date) { return date.toLocaleString(); } window.onload = function() { const boottime = new Date( startuptime * 1000); document.getElementById(\"boottime\").innerHTML = \"boot time: \" + formatdate(boottime); }; async function updatetimes() { const url = \"http://192.168.0.21/update\"; try{ const response = await fetch(url); if( !response.ok){ throw new Error(`response status: ${response.status}`); } const updatetext = await response.text(); const update = Number(updatetext); const hrs = Math.floor(update / 60); const mins = update % 60; let updatebgcolor = \"green\"; if(update <= 5){ updatebgcolor = \"red\"; } const updateelem = document.getElementById(\"lastupdate\"); updateelem.textContent = \"last activity: \" + hrs+ \":\" + mins; const activityelem = document.getElementById(\"recentactivity\"); activityelem.style.backgroundColor = updatebgcolor; }catch(error){ console.error(error.message); } } updatetimes(); setInterval(updatetimes, 30000); </script> </body> </html>";

// chose to use an isr here so the main loop while remain available for requests
void IRAM_ATTR setTimeLocal(){
 
    lastPressMs = millis();

}
 
 

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  // Initialize Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  // have to double check this private ip is the same as in the fetch request in lowerHtml 
  Serial.println(WiFi.localIP());
  
    delay(2000);

    server.begin();

    // setting up the PIR sensor
    pinMode(sensorPin,INPUT_PULLDOWN);

  attachInterrupt(sensorPin,setTimeLocal,RISING);

  // get the startup time ( just for system up time)
    configTime(0, 0, ntpServer);

    do{
      epochTime = getTime();
    }while( epochTime == 0);
    
    Serial.print("epoch time:");
    Serial.println(epochTime);

}





// when request comes in gets the time from last activity
void getTimeFromLast(){
    unsigned long curr = millis();

    // get duration in ms
    if(lastPressMs != NULL){
    unsigned long diff_ms = curr - lastPressMs;

    unsigned long mins = diff_ms /  60000;

    sprintf(lastBuff,"%d", mins);
    Serial.println(lastBuff);
    }

}


void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients


  
  if (client) {                             // If a new client connects,

    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {  // loop while the client's connected

      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:

            getTimeFromLast();
           
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
           // return current update value only
           
            if (header.indexOf("GET /update") >= 0) {
              Serial.println(lastBuff);
              client.println(lastBuff);
              client.println();
              break;
            }
            
            // Display the HTML web page
            client.println(upperHtml);
            
            // send boot time 
            String bootTime = String(epochTime);

            client.println(bootTime);

            // send the rest of the page
            client.println(lowerHtml);

            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  
}
