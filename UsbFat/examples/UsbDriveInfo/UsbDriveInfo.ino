#include <SPI.h>
#include <UsbFat.h>
#include <masstorage.h>

// USB host objects.
USB usb;
BulkOnly bulk(&usb);

// File system.
UsbFat key(&bulk);

ArduinoOutStream cout(Serial);

#define error(msg) {cout << F("Error: ") << F(msg) << endl; while(1);}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  cout << F("UsbFat version: ") << USB_FAT_VERSION << endl;
  cout << F("FreeRam ") << FreeRam() << endl;
  cout << F("Type any character to begin") << endl;
  while (Serial.read() < 0) {}

  // Initialize the USB bus.
  if (!initUSB(&usb)) {
    error("initUSB failed");   
  }
  cout << F("USB initialized.") << endl;
  // Init the USB key or USB hard drive.
  if (!key.begin()) {
    error("key.begin failed");
  }
  cout << F("Volume initialized.") << endl;
  cout << endl;
  cout << F("Volume Size: ") << 0.000512*key.volumeBlockCount();
  cout << F(" MB (MB = 1,000,000 bytes)") << endl;
  cout << F("Volume is FAT") << int(key.vol()->fatType()) << endl;
  cout << F("blocksPerCluster: ") << int(key.vol()->blocksPerCluster()) << endl;
  cout << F("clusterCount: ") << key.vol()->clusterCount() << endl;
  cout << F("fatStartBlock: ") << key.vol()->fatStartBlock() << endl;
  cout << F("fatCount: ") << int(key.vol()->fatCount()) << endl;
  cout << F("blocksPerFat: ") << key.vol()->blocksPerFat() << endl;
  cout << F("rootDirStart: ") << key.vol()->rootDirStart() << endl;
  cout << F("dataStartBlock: ") << key.vol()->dataStartBlock() << endl;
  cout << F("Determining free cluster count -  please wait.") << endl;
  uint32_t volFree = key.vol()->freeClusterCount(); 
  cout << F("freeClusters: ") <<  volFree << endl;  
  float fs = 0.000512*volFree*key.vol()->blocksPerCluster();
  cout << F("freeSpace: ")<< fs << F(" MB (MB = 1,000,000 bytes)\n");
  cout << F("\nDone") << endl;
}
//------------------------------------------------------------------------------
void loop () {}