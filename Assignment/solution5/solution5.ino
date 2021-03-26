#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Wi-fi SSID";                       // Enter wi-fi SSID
const char* password = "Wi-fi Password";               //Enter wi-fi password
const char* mqttServerIP = "broker.mqttdashboard.com"; // Enter server IP or localhost IP address (If you are using a local mqtt broker) 
const int mqttPort = 1883;                             // Port for MQTT protocol
int threshold_value = 200;                             // Threshold value of CO2
WiFiClient espClient3;
PubSubClient client(espClient3);
char* Topic = "IotAssignment_Shubham";                 // Write topic name for publish
String datasensor;

void reconnect(){                                      // Function to connect MQTT broker
    while(!client.connected()){                          // MQTT Begin
    Serial.println("Connecting to MQTT Server..");
    Serial.print("IP MQTT Server : ");
    Serial.println(mqttServerIP);

    bool hasConnection = client.connect("ESPclient3"); // Change client name "ESPclient3", in case of multiple clients 
    if(hasConnection){
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Success connected to MQTT Broker");
    } else {
      digitalWrite(LED_BUILTIN, LOW);                  // Turn ON the builtin LED until device connects with mqtt broker
      Serial.print("Failed connected");
      Serial.println(client.state());
     
      delay(1000);
      Serial.println("Try to connect...");
    }
  }
}


void setup() {
  
  Serial.begin(115200);                                           
  pinMode(LED_BUILTIN, OUTPUT);  
  pinMode(A0, INPUT);                    
 
  Serial.print("Connecting to ");
  Serial.println(ssid);                                   
  WiFi.begin(ssid, password);                                     // Connecting to wi-fi
  while (WiFi.status() != WL_CONNECTED) {                 
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqttServerIP, mqttPort);
//  client.setCallback(callback);
  

 
}
char dataPublish[150];
void publishMQTT(char* topics, String data){
   data.toCharArray(dataPublish, data.length() + 1);
   client.publish(topics, dataPublish);
}


void loop() {
  
   if (!client.connected()) {
    reconnect();
  }
int CO2_DATA = analogRead(A0);
datasensor =   String(CO2_DATA);
Serial.print("Sensor value is: ");  
Serial.println(datasensor);                                              // Printing the Data on Serial Monitor.

if(CO2_DATA>=threshold_value){                                       // Iam not using the ppm value for threshold but using the 0-1024 value   
datasensor = "Alert! CO2 at danger level: " + String(CO2_DATA);
publishMQTT(Topic, datasensor);                                       // Publishing Data through MQTT
Serial.println(datasensor);
  }
delay(5000);                                                          // Delay for 5 second
}
