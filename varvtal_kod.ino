
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into port 5 on the Arduino
#define ONE_WIRE_BUS 5
 
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
 
int NumSensors=0;
/*
 * The setup function. We only start the sensors here
 */
 
#define control 10 // pin that controls the MOSFET

void setup() {
  // ************************Pumpen**********************************
  pinMode(control,OUTPUT);// define control pin as output
  Serial.begin(9600);
   // start serial port
  Serial.println("Dallas Temperature IC Control Library Demo");
 
  // ************************Temperatursensor***************************
  sensors.begin();
  NumSensors=sensors.getDeviceCount();
  Serial.print(NumSensors);Serial.print(" sensor");
  if((NumSensors>1)&(NumSensors!=0))
    Serial.print("s");
  Serial.println(" available");
  sensors.setResolution(9);
}
bool motor_on = false;

void loop() {
  // ********************Tempsensorer************************************  
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  for(int i=0;i<NumSensors;i++)
  {
    Serial.print("Probe ");Serial.print(i);Serial.print(" : ");
    Serial.print(sensors.getTempCByIndex(i));
    if(i<NumSensors-1)
      Serial.print(",");}
      
// ************************Pump*********************************'
    float temp_diff = sensors.getTempCByIndex(1)-sensors.getTempCByIndex(0);
    float power = temp_diff/15;
    
    if (power>1){
      power=1;
    }
    else if(power<0){
      power=0;
    }

    if(sensors.getTempCByIndex(0)>58){
      digitalWrite(control,LOW); // Turn the MOSFET Switch OFF
    }
    else if(motor_on and temp_diff<2){
      digitalWrite(control,LOW); // Turn the MOSFET Switch OFF
      motor_on = false;
    }
    else if(temp_diff>1 or motor_on){
      //analogWrite(control,0);
      for(int i=0;i<50;i++){  
        digitalWrite(control,LOW); // Turn the MOSFET Switch OFF
        delay((1-power)*100);// 
        digitalWrite(control,HIGH); // turn the MOSFET Switch ON
        delay(power*100);// 
       }
      motor_on = true;       
    }
 Serial.println();
}
