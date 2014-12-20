/* Arduino UsbFat Library
 * Copyright (C) 2014 by William Greiman
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
\mainpage Arduino %UsbFat Library
<CENTER>Copyright &copy; 2014 by William Greiman
</CENTER>

\section Intro Introduction
The Arduino %UsbFat Library is a minimal implementation of FAT16 and FAT32
file systems on USB flash drives and USB hard drives.

Experimental support for FAT12 can be enabled by setting FAT12_SUPPORT
nonzero in UsbFatConfig.h.

The %UsbFat library supports Long %File Names or short 8.3 names.
Edit the UsbFatConfig.h file to select short or long file names.

The main classes in %UsbFat are UsbFat, FatFile, PrintFile, File, StdioStream,
\ref fstream, \ref ifstream, and \ref ofstream.

The UsbFat class maintains a FAT volume,
a current working directory, and simplifies initialization of other classes.

The FatFile class provides basic file access functions such as open(),
binary read(), binary write(), close(), remove(), and sync(). FatFile
is the smallest file class.

The PrintFile class has all the FatFile class functions plus the Arduino
Print class functions.

The File class has all the FatFile functions plus the functions in
the Arduino SD.h File class. This provides compatibility with the
Arduino SD.h library.

The StdioStream class implements functions similar to Linux/Unix standard
buffered input/output.

The \ref fstream class implements C++ iostreams for both reading and writing
text files.

The \ref ifstream class implements C++ iostreams for reading text files.

The \ref ofstream class implements C++ iostreams for writing text files.

The classes \ref ifstream, \ref ofstream, \ref istream, and \ref ostream
follow the C++ \ref iostream standard when possible.

There are many tutorials and much documentation about using C++ iostreams
on the web.

http://www.cplusplus.com/  is a good C++ site for learning iostreams.

The classes \ref ibufstream and \ref obufstream format and parse character
 strings in memory buffers.

the classes ArduinoInStream and ArduinoOutStream provide iostream functions
for Serial, LiquidCrystal, and other devices.

Several of example are provided in the %UsbFat/examples folder.  These were
developed to test %UsbFat and illustrate its use.

\section Install Installation

You must manually install UsbFat by copying the UsbFat folder from the download
package to the Arduino libraries folder in you sketch folder.

See the Manual installation section of this guide.

http://arduino.cc/en/Guide/Libraries

The Circuits\@Home USB_Host_Shield_2.0 library must also be installed in
your libraries folder.  A modified version of this library is included 
with UsbFat.  The modifications reduce the time to initialize most USB drives.

Place the USB_Host_Shield_2.0 folder in your Arduino libraries folder.

The unmodified version is here:

https://github.com/felis/USB_Host_Shield_2.0


\section Fatconfig UsbFat Configuration

Several configuration options may be changed by editing the UsbFatConfig.h
file in the %UsbFat folder.

Set USE_LONG_FILE_NAMES nonzero to enable Long %File Names.  By default,
Long %File Names are enabled. For the leanest fastest library disable
Long %File Names.  Long %File names require extra flash but no extra RAM.
Opening Long %File Names can be slower than opening Short %File Names.
Data read and write performance is not changed by the type of %File Name.

Set FAT12_SUPPORT nonzero to enable use of FAT12 volumes.
FAT12 has not been well tested and requires additional flash.


\section FatPath Paths and Working Directories

Relative paths in UsbFat are resolved in a manner similar to Windows.

Each instance of UsbFat has a current directory.  In UsbFat this directory
is called the volume working directory, vwd.  Initially this directory is
the root directory for the volume.

The volume working directory is changed by calling UsbFat::chdir(path).

The call key.chdir("/2014") will change the volume working directory
for key to "/2014", assuming "/2014" exists.

Relative paths for UsbFat member functions are resolved by starting at
the volume working directory.

For example, the call key.mkdir("April") will create the directory
"/2014/April" assuming the volume working directory is "/2014".

UsbFat has a current working directory, cwd, that is used to resolve paths
for file.open() calls.

For a single volume the current working directory is always the volume
working directory.

For multiple volumes the current working directory is set to the volume
working directory of a card by calling the UsbFat::chvol() member function.
The chvol() call is like the Windows \<drive letter>: command.

The call key2.chvol() will set the current working directory to the volume
working directory for key2.

If the volume working directory for key2 is "/music" the call

file.open("BigBand.wav", O_READ);

will then open "/music/BigBand.wav" on key2.

The following functions are used to change or get current directories.
See the html documentation for more information.
@code
bool UsbFat::chdir(bool set_cwd = false);
bool UsbFat::chdir(const char* path, bool set_cwd = false);
void UsbFat::chvol();
FatFile* UsbFat::vwd();
static FatFile* FatFile::cwd();
@endcode

\section Hardware Hardware Configuration

%UsbFat was developed using an
<A HREF = "http://www.circuitsathome.com/products-page/arduino-shields"> 
Circuits\@Home</A> Host Shield.  Testing was also done using an 
<A HREF = http://arduino.cc/en/Main/ArduinoBoardMegaADK> Mega ADK</A>.

\section comment Bugs and Comments

If you wish to report bugs or have comments, send email to
fat16lib@sbcglobal.net.  If possible, include a simple program that illustrates
the bug or problem.

\section Trouble Troubleshooting

Try enabling extra debug messages by setting USB_FAT_DBG_MODE nonzero in
UsbFatConfig.h.

Also run the UsbFatInfo example.

Additional diagnostic tools will be provided in the future.

\section UsbFatClass UsbFat Usage

UsbFat supports Long File Names.  Long names in UsbFat are limited to 7-bit
ASCII characters in the range 0X20 - 0XFE The following are reserved characters:
    <ul>
    <li>< (less than)
    <li>> (greater than)
    <li>: (colon)
    <li>" (double quote)
    <li>/ (forward slash)
    <li>\ (backslash)
    <li>| (vertical bar or pipe)
    <li>? (question mark)
    <li>* (asterisk)
    </ul>
%UsbFat uses a slightly restricted form of short names.
Short names are limited to 8 characters followed by an optional period (.)
and extension of up to 3 characters.  The characters may be any combination
of letters and digits.  The following special characters are also allowed:

$ % ' - _ @ ~ ` ! ( ) { } ^ # &

Short names are always converted to upper case and their original case
value is lost.  Files that have a base-name where all characters have the
same case and an extension where all characters have the same case will
display properly.  Examples this type name are UPPER.low, lower.TXT,
UPPER.TXT, and lower.txt. 

An application which writes to a file using print(), println() or
\link PrintFile::write write() \endlink must close the file or call
\link PrintFile::sync() sync() \endlink at the appropriate time to
force data and directory information to be written to the drive.

Applications must use care calling \link PrintFile::sync() sync() \endlink
since 2048 bytes of I/O is required to update file and
directory information.  This includes writing the current data block, reading
the block that contains the directory entry for update, writing the directory
block back and reading back the current data block.

It is possible to open a file with two or more instances of a file object.
A file may be corrupted if data is written to the file by more than one
instance of a file object.

\section HowTo How to format USB drives as FAT Volumes

A special utility is required to format hard drives on Windows.  Windows does
not allow hard drives larger than 32 GB to be formatted FAT32.  I have used
this formatter.

http://www.ridgecrop.demon.co.uk/index.htm?guiformat.htm 

For USB flash drives, many people use the HP USB Disk Storage Format Tool.
I have used versions of this tool but have not done detailed tests.

Many manufactures have software for their USB flash drives.

http://www.flashdrive-repair.com/2014/02/best-usb-flash-drive-repair-software-recovery-format.html

For best performance, format drives with a large cluster size. Format
2 GB and smaller drives FAT16.  Drives larger than 2 GB should be formatted
FAT32 with a cluster size of at least 8 KB or larger.

You should use a freshly formatted drive for best performance.  FAT
file systems become slower if many files have been created and deleted.
This is because the directory entry for a deleted file is marked as deleted,
but is not deleted.  When a new file is created, these entries must be scanned
before creating the file.  Also files can become
fragmented which causes reads and writes to be slower.

\section ExampleFolder Examples

Several examples are provided in the UsbFat/examples folder.
See the html documentation for a list.

To access these examples from the Arduino development environment
go to:  %File -> Examples -> %UsbFat -> \<program Name\>

Compile, upload to your Arduino and click on Serial Monitor to run
the example.

Here is a list:

UsbDriveInfo - Determine properties of a USB drive.

UsbFatBench - A read/write benchmark.

UsbFatDemo - A simple Demo program.

UsbLogger - A simple modifiable data logger.
 */
