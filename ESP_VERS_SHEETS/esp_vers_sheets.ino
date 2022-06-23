#include "Arduino.h"
#include "Wire.h"

#include "HX711.h"
#define DOUT1 D2
#define CLK1 D3

HX711 scale; // on appelle une balance scale
// s'il s'agit d'un ESP8266
#include <ESP8266WiFi.h>

#include <WiFiClientSecure.h>

const char *ssid = "esp8266"; // nom du réseau wifi 
const char *password = "bc61eeb00507"; //mot de passe wifi
const char* host = "script.google.com";
String url;

//à remplacer par le fingerprint SHA1 de votre App Script
// utile pour l'ESP8266 mais pas pour l'ESP32
const char fingerprint[] PROGMEM = "95 39 EF 6C 90 41 5F 8D CE 30 F8 F0 B4 75 FB 0A DB BB 18 62"; 

int compteur = 0;

void setup()
{
  //ESP8266
  Serial.begin(115200);//Pas besoin de mettre le baudrate en 9600
  delay(100);
  Serial.println();
  Serial.println();
  Serial.print("Connexion a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connecte");
 
  //HX711Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
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
 
}

void loop()
{
 
  Serial.print("Connexion a ");
  Serial.println(host);

  WiFiClientSecure client;

  const int httpPort = 443;

  client.setFingerprint(fingerprint);// car il s'agit d'un esp8266
 

  if (!client.connect(host, httpPort))
  {
    Serial.println("Echec de la connexion");
    delay(5000);
    return;
  }


  float lecture = scale.get_units()*1.11; // On récupère la valeur de la balance(une seule lecture)
  String str_lecture = String(lecture,2);     // On convertit le float en string pour pouvoir le coller dans l’url après (il ira dans la 1ère colonne du sheets
 
 
  float lecture_avg = scale.get_units(10)*1.11; // / On récupère la valeur de la balance(moyenne des 10 dernières lectures)
  String str_lecture_avg = String(lecture_avg,2);     // On reconvertir le float en string pour pouvoir aussi le coller dans l’url (il ira dans la 2ème colonne du sheets

  // à remplacer par l'url de votre web app:
  url = "https://script.google.com/macros/s/AKfycbyWGZ3hrh8XjKNoY7_yF9k6xFHs3zobp9edlYbrIAjppOB6WPE9/exec?func=addData&val1=" + String(str_lecture) + "&val2=" + String(str_lecture_avg);
  Serial.print("URL: ");
  Serial.println(url); //Ici on prend l’url de notre script, on y ajoute “?func=addData&val1” on appelle la fonction addData puis on précisera les valeurs que devront prendre la colonne 1 et 2 avec par exemple &val1=String(str_lecture)

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");//On récupère l’url que l’on met sur le client (web)
  delay(500);
  String section = "header";
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println("Fermeture de la connexion.");
  delay(9500); // on envoie les prochaines données dans 10 secondes ( 9500 + 500ms du dessus)
}
