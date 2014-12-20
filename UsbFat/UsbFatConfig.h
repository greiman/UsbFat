/* Arduino UsbFat Library
 * Copyright (C) 2012 by William Greiman
 *
 * This file is part of the Arduino UsbFat Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino UsbFat Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * \file
 * \brief configuration definitions
 */
#ifndef SdFatConfig_h
#define SdFatConfig_h
#include <stdint.h>
#ifdef __AVR__
#include <avr/io.h>
#endif  // __AVR__
//------------------------------------------------------------------------------
/** Print debufg messages if USB_FAT_DBG_MODE is nonzero */
#define USB_FAT_DBG_MODE 0
//------------------------------------------------------------------------------
/** Maximum time to initialize the USB bus */
#define TIMEOUT_MILLIS 4000
//------------------------------------------------------------------------------
/**
 * Set USE_LONG_FILE_NAMES nonzero to use long file names (LFN).
 * Long File Name are limited to a maximum length of 255 characters.
 *
 * This implementation allows 7-bit characters in the range
 * 0X20 to 0X7E except the following characters are not allowed:
 *
 *  < (less than)
 *  > (greater than)
 *  : (colon)
 *  " (double quote)
 *  / (forward slash)
 *  \ (backslash)
 *  | (vertical bar or pipe)
 *  ? (question mark)
 *  * (asterisk)
 *
 */
#define USE_LONG_FILE_NAMES 1
//------------------------------------------------------------------------------
/** 
 * Set ARDUINO_FILE_USES_STREAM nonzero to use Stream as the base class
 * for the Arduino File class.  If ARDUINO_FILE_USES_STREAM is zero, Print
 * will be used as the base class for the Arduino File class.
 *
 * You can save some flash if you do not use Stream input functions such as
 * find(), findUntil(), readBytesUntil(), readString(), readStringUntil(), 
 * parseInt(), and parsefloat().
 */
#define ARDUINO_FILE_USES_STREAM 1
//------------------------------------------------------------------------------
/**
 * Set FAT12_SUPPORT nonzero to enable use if FAT12 volumes.
 * FAT12 has not been well tested and requires additional flash.
 */
#define FAT12_SUPPORT 0
//------------------------------------------------------------------------------
/**
 * Set DESTRUCTOR_CLOSES_FILE nonzero to close a file in its destructor.
 *
 * Causes use of lots of heap in ARM.
 */
#define DESTRUCTOR_CLOSES_FILE 0
//------------------------------------------------------------------------------
/**
 * Call flush for endl if ENDL_CALLS_FLUSH is nonzero
 *
 * The standard for iostreams is to call flush.  This is very costly for
 * UsbFat.  Each call to flush causes 2048 bytes of I/O.
 *
 * UsbFat has a single 512 byte buffer so UsbFat must write the current
 * data block to the drive, read the directory block from the drive, update the
 * directory entry, write the directory block to the drive and read the data
 * block back into the buffer.
 *
 * If ENDL_CALLS_FLUSH is zero, you must call flush and/or close to force
 * all data to be written to the drive.
 */
#define ENDL_CALLS_FLUSH 0
//------------------------------------------------------------------------------
/**
 * Set USE_SEPARATE_FAT_CACHE nonzero to use a second 512 byte cache
 * for FAT table entries.  This improves performance for large writes
 * that are not a multiple of 512 bytes.
 */
#ifdef __arm__
#define USE_SEPARATE_FAT_CACHE 1
#else  // __arm__
#define USE_SEPARATE_FAT_CACHE 0
#endif  // __arm__
//------------------------------------------------------------------------------
/**
 * Set USE_MULTI_BLOCK_IO nonzero to use multi-block read/write.
 *
 * Don't use mult-block read/write on small AVR boards.
 */
#if defined(RAMEND) && RAMEND < 3000
#define USE_MULTI_BLOCK_IO 0
#else  // RAMEND
#define USE_MULTI_BLOCK_IO 1
#endif  // RAMEND
#endif  // SdFatConfig_h
