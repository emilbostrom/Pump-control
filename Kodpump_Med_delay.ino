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
    Serial.println();
// ************************Pump*********************************'
  if (sensors.getTempCByIndex(1)-5 > sensors.getTempCByIndex(0))
  {  
    digitalWrite(control,HIGH); // turn the MOSFET Switch ON
    delay(10000);// Wait for 2000 ms or 2 second
  else if (sensors.getTempCByIndex(1)-2 < sensors.getTempCByIndex(0))
    digitalWrite(control,LOW); // Turn the MOSFET Switch OFF
    for(int j=0;j<10;j++){
      Serial.print("Requesting temperatures...");
      sensors.requestTemperatures(); // Send the command to get temperatures
      Serial.println("DONE");
      for(int i=0;i<NumSensors;i++) {
        Serial.print("Probe ");Serial.print(i);Serial.print(" : ");
        Serial.print(sensors.getTempCByIndex(i));
        if(i<NumSensors-1)
          Serial.print(",");} 
      delay(1000);
      Serial.println(); 
    }
  }
}
