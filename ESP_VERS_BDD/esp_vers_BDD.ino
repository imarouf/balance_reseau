  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
  #include <Wire.h>
  #include "HX711.h"  

  HX711 scale;      // on appelle une balance scale
  #define DOUT1 D2  // Le HX711 est connecté à deux pins pour lire la valeur (D2 et D3)
  #define CLK1 D3

  
  const char* serverName = "http://ilyes84000.000webhostapp.com/index.php";
  String apiKeyValue     = "tPmAT5Ab3j7F9";           //sert à sécuriser le site(seuls ceux qui détiennt la clé peuvent modifier les données)
  const char* ssid       = "esp8266";                 //id wifi
  const char* password   = "bc61eeb00507";            //mdp wifi


void setup() {

    //BEGIN WIFI
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
   //END WIFI


 
  //BEGIN HX711
  Serial.println("Initializing the scale");
  scale.begin(DOUT1, CLK1);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)

  scale.set_scale(48.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // Remet la balance à 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print  a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
  //END HX711
  
}

void loop() {
  
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
     http.begin(client, serverName);
    
    // Specify content-type header
     http.addHeader("Content-Type", "application/x-www-form-urlencoded");
     
    float lecture = scale.get_units()*1.11; // On récupère la valeur de la balance(une seule lecture)
 
    float lecture_avg = scale.get_units(10)*1.11; // / On récupère la valeur de la balance(moyenne des 10 dernières lectures)
    Serial.print(String(lecture,2));
 
    //HTTP POST
    String httpRequestData = "api_key=" + apiKeyValue + "&lecture=" + String(lecture,2) 
                          + "&lecture_avg=" + String(lecture_avg,2) ;
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    int httpResponseCode = http.POST(httpRequestData);
 


      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
    // Free resources
      http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds*
  delay(60000); 

  
  
}
