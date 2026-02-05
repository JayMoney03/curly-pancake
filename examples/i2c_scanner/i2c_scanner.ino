#include <Wire.h>

void identifyDevice(byte addr) {
  Serial.print(" → Likely: ");
  switch(addr) {
    case 0x3C: case 0x3D: 
      Serial.println("OLED Display (SSD1306/SH1106)"); 
      break;
    case 0x68: 
      Serial.println("MPU6050 Gyro/Accel or DS3231 RTC"); 
      break;
    case 0x76: case 0x77: 
      Serial.println("BMP280/BME280 Temp/Pressure Sensor"); 
      break;
    case 0x40: 
      Serial.println("PCA9685 Servo Driver"); 
      break;
    case 0x48: case 0x49: case 0x4A: case 0x4B:
      Serial.println("ADS1115 ADC");
      break;
    default: 
      Serial.println("Unknown device");
  }
}

void setup() {
  Wire.begin(21, 22); // SDA on 21, SCL on 22
  Serial.begin(115200);
  while (!Serial);
  Serial.println("\n╔════════════════════════════════════════╗");
  Serial.println("║  I2C Scanner - AEGIS Core Detection   ║");
  Serial.println("╚════════════════════════════════════════╝\n");
}

void loop() {
  byte error, address;
  int nDevices = 0;
  
  Serial.println("Scanning I2C bus...");
  
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("✅ Device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();
      identifyDevice(address);
      nDevices++;
    } else if (error == 4) {
      Serial.print("⚠️  Unknown error at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  
  if (nDevices == 0) {
    Serial.println("❌ No I2C devices found");
  } else {
    Serial.println("\n✓ Scan complete - " + String(nDevices) + " device(s) found");
  }
  Serial.println("─────────────────────────────────────────\n");
  
  delay(5000);
}
