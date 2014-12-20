#ifndef UsbFat_h
#define UsbFat_h
/**
 * \file
 * \brief UsbFat class
 */
#include "utility/FatLib.h"
#include "masstorage.h"
//------------------------------------------------------------------------------
/** Version of UsbFat - yyyymmdd */
#define USB_FAT_VERSION 20141220
//------------------------------------------------------------------------------
/** Simple USB init function.
 * \param[in] usb USB host object to be initialized.
 * \return true for success or false for failure.
 */
bool initUSB(USB* usb);
//------------------------------------------------------------------------------
#ifdef __arm__
extern "C" char* sbrk(int incr);
inline int FreeRam() {
  char top;
  return &top - reinterpret_cast<char*>(sbrk(0));
}
#else  // __arm__
/** End of heap */
extern char *__brkval;
/** End of globals */
extern char __bss_end;
/** Amount of free RAM
 * \return The number of free bytes.
 */
inline int FreeRam() {
  char top;
  return __brkval ? &top - __brkval : &top - &__bss_end;
}
#endif  // __arm
//------------------------------------------------------------------------------
/**
 * \class UsbFat
 * \brief FAT file systems on USB flash drives and USB hard drives.
 */
class UsbFat : public FatFileSystem {
 public:
  /** 
   * Constructor
   * \param[in] bulk BulkOnly object for this volume.
   */
  UsbFat(BulkOnly* bulk) : m_lun(0), m_bulk(bulk) {}
  /** 
   * Initialize a volume on a USB flash drive or USB hard drive.
   * \param[in] lun Logical unit to be used.
   * \param[in] part Partition to be used. Zero first tries mbr
   *                 partition zero then tries Super Floppy format.
   * \return true for success or false for failure.
   */ 
  bool begin(uint8_t lun = 0, uint8_t part = 0) {
    m_lun = lun;
    if (m_bulk->GetSectorSize(m_lun) != 512) {
      return false;
    }
    return FatFileSystem::begin(part);
  }

 private:
  bool readBlock(uint32_t block, uint8_t* dst) {
    return 0 == m_bulk->Read(m_lun, block, 512, 1, dst);
  }
  bool writeBlock(uint32_t block, const uint8_t* src) {
    return  0 == m_bulk->Write(m_lun, block, 512, 1, src);
  }
  bool readBlocks(uint32_t block, uint8_t* dst, size_t n) {
        return 0 == m_bulk->Read(m_lun, block, 512, n, dst);
  }
  bool writeBlocks(uint32_t block, const uint8_t* src, size_t n) {
        return  0 == m_bulk->Write(m_lun, block, 512, n, src);
  }
  uint8_t m_lun;
  BulkOnly* m_bulk;
};
#endif   // UsbFat_h