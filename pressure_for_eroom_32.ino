const int FSR_PIN = 33; // Pin connected to FSR/resistor divider
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0; // Measured resistance of 3.3k resistor

void setup() 
{
  Serial.begin(9600);
  
}

void loop() 
{
  int fsrADC = analogRead(FSR_PIN);
  
  if (fsrADC != 0) // If the analog reading is non-zero
  {
    
    float fsrV = fsrADC * VCC / 4095.0;

    float fsrR = R_DIV * (VCC / fsrV - 1.0);
    Serial.println("Resistance: " + String(fsrR) + " ohms");
    float force;
    float fsrG = 1.0 / fsrR; // Calculate conductance
    
    // Break parabolic curve down into two linear slopes:
    if (fsrR <= 600) 
      force = ((fsrG - 0.00075) / 0.00000032639)*98.0665;
     
    else
      force =  (fsrG / 0.000000642857)*98.0665;
     
    Serial.println("Force: " + String(force) + " pa");
    Serial.println(); 
    delay(500);
    
  }
  else
  {
    // No pressure detected
  }
}
