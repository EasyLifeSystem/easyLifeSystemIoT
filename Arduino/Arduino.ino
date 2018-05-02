#include <TimerOne.h>
#include <SoftwareSerial.h>

SoftwareSerial ArduinoUno(2,13); //rx,tx at pin 2 in arduino (reciver)

unsigned char channel_1 = 7; // Output to Opto Triac pin, channel 1 comes from acdemar 
unsigned char channel_2 = 6; // Output to Opto Triac pin, channel 1
unsigned char channel_3 = 8; // Output to Opto Triac pin, channel 1
unsigned char GPIO_Pin = 3; // at 3 in arduino SYN
int CH1 = 100;
int CH2 = 0;
int CH3 = 0;
unsigned char i=0;
unsigned char clock_tick=0; 
String payload = ""; // store the payload comes from  nodeMCU 


void zero_cross_int() 
{

clock_tick=0;
}

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void setup() {
 pinMode(channel_1, OUTPUT);// Set AC Load pin as output >>>>> pinMode(pin, mode)


  pinMode(channel_2, OUTPUT);// Set AC Load pin as output

 pinMode(channel_3, OUTPUT);// Set AC Load pin as output
 

attachInterrupt(digitalPinToInterrupt(GPIO_Pin), zero_cross_int, RISING); // when the interput accurs will call zero_cross_int function  >> RISING : when the ping goes from low to high 
Timer1.initialize(83); // waite 83 ms to do attachInterrupt
Timer1.attachInterrupt( timerIsr ); // after coplite 83 ms call timerIsr function 

ArduinoUno.begin(9600);
Serial.begin(9600);

}

void timerIsr()
{
clock_tick++;// counter

if (CH1==clock_tick)
{
digitalWrite(channel_1, HIGH); // triac firing   
delayMicroseconds(8.33); // wait 83 untill go back to cross zero half wave  
digitalWrite(channel_1, LOW); // triac Off
}

if (CH3==clock_tick)
{
digitalWrite(channel_3, HIGH); // triac firing
delayMicroseconds(8.33); 
digitalWrite(channel_3, LOW); // triac Off
}

}






void loop() {
 
while (ArduinoUno.available()){// software comuncation >> available : means at nodeMCU there is a code says nodeMCU.println(payload);
payload = ArduinoUno.readStringUntil('\r\n');// read until enter اللي هي من println 
Serial.println(payload);// optional to konw what will recive for ex 100,100,50 
CH1 = getValue(payload, ',', 0).toInt();// السترينق كامل و ايش اللي يفصل بينهم بالاندكس و يحولها بالاخير الى رقم 
CH2 = getValue(payload, ',', 1).toInt();
CH3 = getValue(payload, ',', 2).toInt();

}
digitalWrite(channel_2,CH2);
}

