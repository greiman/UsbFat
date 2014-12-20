/*
 * This program is a simple binary write/read benchmark.
 */
#include <SPI.h>
#include <UsbFat.h>
#include <masstorage.h>

// Size of read/write.
const size_t BUF_SIZE = 100;

// File size in MB where MB = 1,000,000 bytes.
const uint32_t FILE_SIZE_MB = 5;

// Write pass count.
const uint8_t WRITE_COUNT = 1;

// Read pass count.
const uint8_t READ_COUNT = 1;
//==============================================================================
// End of configuration constants.
//------------------------------------------------------------------------------
// File size in bytes.
const uint32_t FILE_SIZE = 1000000UL*FILE_SIZE_MB;

uint8_t buf[BUF_SIZE];

// USB host objects.
USB usb;
BulkOnly bulk(&usb);

// File system.
UsbFat key(&bulk);

// Test file.
FatFile file;

// Serial output stream
ArduinoOutStream cout(Serial);
//------------------------------------------------------------------------------
// store error strings in flash to save RAM
#define error(s) Serial.println(s);
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  while (!Serial) {} // wait for Leonardo
  delay(1000);
  cout << F("\nUse a freshly formatted volume for best performance.\n");

  // use uppercase in hex and use 0X base prefix
  cout << uppercase << showbase << endl;
}
//------------------------------------------------------------------------------
void loop() {
  float s;
  uint32_t t;
  uint32_t maxLatency;
  uint32_t minLatency;
  uint32_t totalLatency;

  // discard any input
  while (Serial.read() >= 0) {}

  // F( stores strings in flash to save RAM
  cout << F("Type any character to start\n");
  while (Serial.read() <= 0) {}
  delay(400);  // catch Due reset problem

  cout << F("Free RAM: ") << FreeRam() << endl;

  if (!initUSB(&usb)) {
    cout << F("initUSB failed") << endl;
  }
  // initialize the USB key or hard drive.
  if (!key.begin()) {
    cout << F("key.begin failed") << endl;
    while(1);
  }

  cout << F("Type is FAT") << int(key.vol()->fatType()) << endl;
  cout << F("Volume size: ") << key.volumeBlockCount()*512E-9;
  cout << F(" GB (GB = 1E9 bytes)") << endl;

  // open or create file - truncate existing file.
  if (!file.open("bench.dat", O_CREAT | O_TRUNC | O_RDWR)) {
    error("open failed");
  }

  // fill buf with known data
  for (uint16_t i = 0; i < (BUF_SIZE-2); i++) {
    buf[i] = 'A' + (i % 26);
  }
  buf[BUF_SIZE-2] = '\r';
  buf[BUF_SIZE-1] = '\n';

  cout << F("File size ") << FILE_SIZE_MB << F(" MB\n");
  cout << F("Buffer size ") << BUF_SIZE << F(" bytes\n");
  cout << F("Starting write test, please wait.") << endl << endl;

  // do write test
  uint32_t n = FILE_SIZE/sizeof(buf);
  cout <<F("write speed and latency") << endl;
  cout << F("speed,max,min,avg") << endl;
  cout << F("KB/Sec,usec,usec,usec") << endl;
  for (uint8_t nTest = 0; nTest < WRITE_COUNT; nTest++) {
    file.truncate(0);
    maxLatency = 0;
    minLatency = 9999999;
    totalLatency = 0;
    t = millis();
    for (uint32_t i = 0; i < n; i++) {
      uint32_t m = micros();
      if (file.write(buf, sizeof(buf)) != sizeof(buf)) {
        error("write failed");
      }
      m = micros() - m;
      if (maxLatency < m) {
        maxLatency = m;
      }
      if (minLatency > m) {
        minLatency = m;
      }
      totalLatency += m;
    }
    file.sync();
    t = millis() - t;
    s = file.fileSize();
    cout << s/t <<',' << maxLatency << ',' << minLatency;
    cout << ',' << totalLatency/n << endl;
  }

  cout << endl << F("Starting read test, please wait.") << endl;
  cout << endl <<F("read speed and latency") << endl;
  cout << F("speed,max,min,avg") << endl;
  cout << F("KB/Sec,usec,usec,usec") << endl;
  // do read test
  for (uint8_t nTest = 0; nTest < READ_COUNT; nTest++) {
    file.rewind();
    maxLatency = 0;
    minLatency = 9999999;
    totalLatency = 0;
    t = millis();
    for (uint32_t i = 0; i < n; i++) {
      buf[BUF_SIZE-1] = 0;
      uint32_t m = micros();
      if (file.read(buf, sizeof(buf)) != sizeof(buf)) {
        error("read failed");
      }
      m = micros() - m;
      if (maxLatency < m) {
        maxLatency = m;
      }
      if (minLatency > m) {
        minLatency = m;
      }
      totalLatency += m;
      if (buf[BUF_SIZE-1] != '\n') {
        error("data check");
      }
    }
    t = millis() - t;
    cout << s/t <<',' << maxLatency << ',' << minLatency;
    cout << ',' << totalLatency/n << endl;
  }
  cout << endl << F("Done") << endl;
  file.close();
}