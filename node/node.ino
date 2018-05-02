#include "ESP8266WiFi.h" // WiFi Library
#include<SoftwareSerial.h> // librarry resposible for comuncation bet nodeMCU an serial 

// to conect the arduino(number 2)  with the wifi/nodeMCU (number 13=7) 
SoftwareSerial nodeMCU(2,13); //rx,tx use 13=D7 as a transmeter 


const char* ssid = "Sarah"; // Name of WiFi Network
const char* password = "sarah1234"; // Password of WiFi Network
WiFiServer server(80); // Define Web Server Port by default 80 

unsigned char buttonpressed = 0;
unsigned char firstrun = 0;
unsigned char CH1 = 100; // طافي 
unsigned char CH2 = 0;
unsigned char CH3 = 0;
String var1 = String(CH1);
String var2 = String(CH2);
String var3 = String(CH3);
String payload = var1 + "," + var2 + "," + var3 ;// send it to arduino 

void setup() {

Serial.begin(115200);// speed to connect with wi-fi 
nodeMCU.begin(9600); //speed to start connect with arduino 
delay(10); // give it chance to comuncate 


// Connect to WiFi network
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);

// Wait until connected to WiFi
while (WiFi.status() != WL_CONNECTED) {
delay(250);
Serial.print(".");

}

// Confirmation that WiFi is connected
Serial.println("");
Serial.println("WiFi connected");

// Start the Web Server
server.begin();
Serial.println("Web Server Started");


// Display IP address
Serial.print("You can connect to the Server here: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println();
Serial.println();

}


void loop() {

// Check if someone is connected
WiFiClient client = server.available();
if (!client) {
return;
}


// Read which button was pressed on the Web Page
String request = client.readStringUntil('\r'); // enter in web means back salsh r we programe

// control the fan based on the button pressed 
if (request.indexOf("/FanHigh=1") != -1) {
CH3= 10 ;
var3 = String(CH3);// update store the new value 
payload = var1 + "," + var2 + "," + var3 ;// when update the var we should update the payload 
nodeMCU.println(payload); // this will send the paylood to nodeMCU WI-FI by the connceted link(2,13) and already  write /r at the last 
buttonpressed = 1;
firstrun=1;// for print we can delet it 

}

if (request.indexOf("/FanMed=1") != -1) {
CH3= 30;
var3 = String(CH3);
payload = var1 + "," + var2 + "," + var3 ;
nodeMCU.println(payload);
buttonpressed = 2;
firstrun=1;
}

if (request.indexOf("/FanLow=1") != -1) {
CH3=50;
var3 = String(CH3);
payload = var1 + "," + var2 + "," + var3 ;
nodeMCU.println(payload);
buttonpressed = 3;
firstrun=1;
}


if (request.indexOf("/FanOff=1") != -1) {
CH3= 0;
var3 = String(CH3);
payload = var1 + "," + var2 + "," + var3 ;
nodeMCU.println(payload);
buttonpressed = 4;
firstrun=1;
}

// Light Up leds based on the button pressed >>>> if we did not use buttonpressed we can use it manually by the link 
if (request.indexOf("/LedHigh=1") != -1) {
CH1= 10 ;
var1 = String(CH1); 
payload = var1 + "," + var2 + "," + var3 ;
nodeMCU.println(payload);
buttonpressed = 5;
firstrun=1;

}

if (request.indexOf("/LedMed=1") != -1) {
CH1= 30;
var1 = String(CH1);
payload = var1 + "," + var2 + "," + var3 ;
nodeMCU.println(payload);
buttonpressed = 6;
firstrun=1;
}

if (request.indexOf("/LedLow=1") != -1) {
CH1=70;
var1 = String(CH1);
payload = var1 + "," + var2 + "," + var3 ;
nodeMCU.println(payload);
buttonpressed = 7;
firstrun=1;
}


if (request.indexOf("/LedOff=1") != -1) {
CH1= 100;
var1 = String(CH1);
payload = var1 + "," + var2 + "," + var3 ;
nodeMCU.println(payload);
buttonpressed = 8;
firstrun=1;
}

//Conn on and off
if (request.indexOf("/ConnOn=1") != -1) {
CH2=0;
var2 = String(CH2);
//digitalWrite(LedPin,HIGH); 
payload = var1 + "," + var2 + "," + var3 ;
nodeMCU.println(payload);
buttonpressed = 9;
firstrun=1;

}

if (request.indexOf("/ConnOff=1") != -1) {
CH2=1;
var2 = String(CH2);
//digitalWrite(LedPin,LOW); 
payload = var1 + "," + var2 + "," + var3 ;
nodeMCU.println(payload);
buttonpressed = 10;
firstrun=1;

} 
delay(10); 
}

