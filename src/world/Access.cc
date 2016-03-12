/******************************************************************************
    Copyright � 2012-2015 Martin Karsten

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/
#include "world/Access.h"
#include <cstring>
#include <string>

map<string,RamFile> kernelFS;
map<string,MyRamFile> myKernelFS;
char* savedMemory;

/* A3 */
ssize_t ReadAccess::pread(void *buf, size_t nbyte, off_t o)
{
    // myrf -> myKernelFS
    if (o + nbyte > myrf.size)
    {
        nbyte = myrf.size - o;
    }
    
    //copy into buf from (bufptr_t)(rf.vma + o) for nbyte bytes.
    memcpy( buf, (bufptr_t)(myrf.vma + o), nbyte );	
    
    return nbyte;
}

ssize_t ReadAccess::read(void *buf, size_t nbyte) 
{
    olock.acquire();
    
    //ask pread to read nbyte characters from location: offset and store it to location buf 
    ssize_t len = ReadAccess::pread(buf, nbyte, offset);
    
    if (len >= 0)
    {
        //increment the offset.
        offset += len;				            
    }
    
    olock.release();
    
    return len;
}

//Laura: i have the size, i check where it has to start and the number of bytes to see if it is to large
//if it is to large i normalize it as much as possible
ssize_t WriteAccess::pwrite(off_t o,  size_t nbyte,void *buf, int j)
{
    // myrf -> myKernelFS
    if (o + nbyte > myrf.size)
    {
        nbyte = myrf.size - o;
    }
    
    //copy into buf from (bufptr_t)(rf.vma + o) for nbyte bytes.	 
	memcpy( &savedMemory[j], buf, nbyte );

    return nbyte;
}

ssize_t WriteAccess::write(void *buf, size_t nbyte, int length) 
{
    olock.acquire();
		ssize_t len = WriteAccess::pwrite(offset, nbyte, buf, length); 	//ask pread to read nbyte characters from location: buf and store it to location offset 

    if (len >= 0)
    {
        //increment the offset.
        offset += len;				
    }

    olock.release();
    
    return len;
}

off_t WriteAccess::lseek(off_t o, int whence)
    {
    off_t new_o;
    switch (whence)
    {
        case SEEK_SET: new_o = o; break;
        case SEEK_CUR: new_o = offset + o; break;
        case SEEK_END: new_o = myrf.size + o; break;
        default: return -EINVAL;
    }
    
    if (new_o < 0)
    {
        return -EINVAL;
    }
    
    offset = new_o;
    return offset;
}

off_t ReadAccess::lseek(off_t o, int whence)
    {
    off_t new_o;
    switch (whence)
    {
        case SEEK_SET: new_o = o; break;
        case SEEK_CUR: new_o = offset + o; break;
        case SEEK_END: new_o = myrf.size + o; break;
        default: return -EINVAL;
    }
    
    if (new_o < 0)
    {
        return -EINVAL;
    }
    
    offset = new_o;
    return offset;
}
/* A3 */

ssize_t FileAccess::pread(void *buf, size_t nbyte, off_t o) {
  if (o + nbyte > rf.size) nbyte = rf.size - o;
  memcpy( buf, (bufptr_t)(rf.vma + o), nbyte );	//copy into buf from (bufptr_t)(rf.vma + o) for nbyte bytes.
  return nbyte;
}

ssize_t FileAccess::pwrite(off_t o,  size_t nbyte,void *buf) {
  if (o + nbyte > rf.size) nbyte = rf.size - o;
  memcpy( buf, (bufptr_t)(rf.vma + o), nbyte );	//copy into buf from (bufptr_t)(rf.vma + o) for nbyte bytes.
  return nbyte;
}

ssize_t FileAccess::read(void *buf, size_t nbyte) 
{
  olock.acquire();
  ssize_t len = pread(buf, nbyte, offset); 	//ask pread to read nbyte characters from location: offset and store it to location buf 
  if (len >= 0) offset += len;				//increment the offset.
  olock.release();
  return len;
}

ssize_t FileAccess::write(void *buf, size_t nbyte) 
{
  olock.acquire();
  ssize_t len = pwrite(offset, nbyte, buf); 	//ask pread to read nbyte characters from location: buf and store it to location offset 
  if (len >= 0) offset += len;				//increment the offset.
  olock.release();
  return len;
}
off_t FileAccess::lseek(off_t o, int whence) {
  off_t new_o;
  switch (whence) {
    case SEEK_SET: new_o = o; break;
    case SEEK_CUR: new_o = offset + o; break;
    case SEEK_END: new_o = rf.size + o; break;
    default: return -EINVAL;
  }
  if (new_o < 0) return -EINVAL;
  offset = new_o;
  return offset;
}
