#include <M5Stack.h>    // this is needed to add the original source code.

/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5;           //In seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {             // overide the funtion onResult()
    void onResult(BLEAdvertisedDevice advertisedDevice) {                             // 
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};
void lcd_dsp(String d_str){
  M5.begin();               //Init M5Core.  
  M5.Power.begin();         //Init Power module.  
  M5.Lcd.fillScreen(BLACK); //Set the screen background color to black. 
  M5.Lcd.setTextColor(GREEN , BLACK); //Sets the foreground color and background color of the displayed text.  
  M5.Lcd.setTextSize(2);    //Set the font size.  
  M5.Lcd.setCursor(0, 70);
  M5.Lcd.print(d_str);      // to check M5stack is on or off via LCD monitor
}

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();  //create new scan as a function pointer
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);    //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);          // less or equal setInterval value
  lcd_dsp("pow-on");
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(2000);
}