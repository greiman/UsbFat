#include <SPI.h>
#include <UsbFat.h>
#include <masstorage.h>

// USB host objects.
USB usb;
BulkOnly bulk(&usb);

// File system.
UsbFat key(&bulk);

// Test file.
File file;

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.print(F("FreeRam "));
  Serial.println(FreeRam());
  Serial.println(F("Type any character to begin"));
  while (Serial.read() < 0) {}
  
  // Initialize the USB bus.
  if (!initUSB(&usb)) {
    Serial.println(F("initUSB failed"));
    return;    
  }
  // Init the USB key or USB hard drive.
  if (!key.begin()) {
    Serial.println(F("key.begin failed"));
    return;
  }
  Serial.print(F("\r\nVolume Size: "));
  // Avoid 32-bit overflow for large volumes.
  Serial.print((key.volumeBlockCount()/1000)*512/1000);
  Serial.println(F(" MB"));
  
  // Print a line to a test file.
  file.open("test file.txt", O_CREAT | O_RDWR);
  file.println("Hello USB");
  file.close();
  
  // List the files in the root directory.
  Serial.println();
  key.ls(LS_A | LS_DATE | LS_SIZE);
  Serial.println();
  
  Serial.println(F("Done")); 
}
//------------------------------------------------------
void loop() {}