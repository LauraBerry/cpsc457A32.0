/******************************************************************************
    Copyright © 2012-2015 Martin Karsten

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
#include "runtime/Thread.h"
#include "kernel/AddressSpace.h"
#include "kernel/Clock.h"
#include "kernel/Output.h"
#include "world/Access.h"
#include "machine/Machine.h"
#include "devices/Keyboard.h"

#include "main/UserMain.h"

AddressSpace kernelSpace(true); // AddressSpace.h
volatile mword Clock::tick;     // Clock.h

extern Keyboard keyboard;


#if TESTING_KEYCODE_LOOP
static void keybLoop() {
  for (;;) {
    Keyboard::KeyCode c = keyboard.read();
    StdErr.print(' ', FmtHex(c));
  }
}
#endif

void kosMain() {
  KOUT::outl("Welcome to KOS!", kendl);
  auto iter = kernelFS.find("motb");
  if (iter == kernelFS.end()) {
    KOUT::outl("motb information not found");
  } else {
    FileAccess f(iter->second);
    for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
    KOUT::outl();
  }
/*A3*/
	string outputmessage="My filesystem works !";
	char outputMessage [20];
	for (int i=0; i<21;i++)
	{
		outputMessage[i]=outputmessage[i];
	}

  /*KOUT::out1("myKernelFS"); 		//fill myKernelFS the same way kernelFS was filled.
  KOUT::outl();
  auto iter3 = myKernelFS.find("motb");
  if (iter3 == myKernelFS.end()) {
    KOUT::outl("motb information not found");
  } else {
    FileAccess f(iter3->second);
    for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
	KOUT::outl();
	for(int i=0; i<21; i++)
	{
		if(f.write(&outputMessage[i], 1)==0) break;
			KOUT:out1("wrote to file");
	}
	KOUT::outl();
 	for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
    KOUT::outl();
   }

  KOUT::out1("myKernelFS"); 		//fill myKernelFS the same way kernelFS was filled.
  KOUT::outl();
  auto iter4 = myKernelFS.find("kbloop");
  if (iter4 == myKernelFS.end()) {
    KOUT::outl("kbloop information not found");
  } else {
    FileAccess f(iter4->second);
    for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
	KOUT::outl();
	for(int i=0; i<21; i++)
	{
		if(f.write(&outputMessage[i], 1)==0) break;
			KOUT:out1("wrote to file");
	}
	KOUT::outl();
 	for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
    KOUT::outl();
   }

  KOUT::out1("myKernelFS"); 		
  KOUT::outl();
  auto iter5 = myKernelFS.find("manytthread");
  if (iter5 == myKernelFS.end()) {
    KOUT::outl("manythread information not found");
  } else {
    FileAccess f(iter5->second);
    for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
	KOUT::outl();
	for(int i=0; i<21; i++)
	{
		if(f.write(&outputMessage[i], 1)==0) break;
			KOUT:out1("wrote to file");
	}
	KOUT::outl();
 	for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
    KOUT::outl();
   }

  KOUT::out1("myKernelFS"); 		//fill myKernelFS the same way kernelFS was filled.
  KOUT::outl();
  auto iter6 = myKernelFS.find("systest");
  if (iter6 == myKernelFS.end()) {
    KOUT::outl("systest information not found");
  } else {
    FileAccess f(iter6->second);
    for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
	KOUT::outl();
	for(int i=0; i<21; i++)
	{
		if(f.write(&outputMessage[i], 1)==0) break;
			KOUT:out1("wrote to file");
	}
	KOUT::outl();
 	for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
    KOUT::outl();
   }

  KOUT::out1("myKernelFS"); 		//fill myKernelFS the same way kernelFS was filled.
  KOUT::outl();
  auto iter7 = myKernelFS.find("threadtest");
  if (iter7 == myKernelFS.end()) {
    KOUT::outl("threadtest information not found");
  } else {
    FileAccess f(iter7->second);
    for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
	KOUT::outl();
	for(int i=0; i<21; i++)
	{
		if(f.write(&outputMessage[i], 1)==0) break;
		KOUT:out1("wrote to file");
	}
	KOUT::outl();
 	for (;;) {
      char c;
      if (f.read(&c, 1) == 0) break;
      KOUT::out1(c);
    }
    KOUT::outl();
   }*/

	auto iter2 = kernelFS.find("filesystem_test");
    if (iter2 == kernelFS.end()) 
    {
        KOUT::outl("filesystem_test information not found");
    } 
    else 
    {
        FileAccess f(iter2->second);
        for (;;) 
        {
            char c;
            if (f.read(&c, 1) == 0) break;
			KOUT::out1(c);
        }
        KOUT::outl();
    } 



/*A3*/

#if TESTING_TIMER_TEST
  StdErr.print(" timer test, 3 secs...");
  for (int i = 0; i < 3; i++) {
    Timeout::sleep(Clock::now() + 1000);
    StdErr.print(' ', i+1);
  }
  StdErr.print(" done.", kendl);
#endif
#if TESTING_KEYCODE_LOOP
  Thread* t = Thread::create()->setPriority(topPriority);
  Machine::setAffinity(*t, 0);
  t->start((ptr_t)keybLoop);
#endif
  Thread::create()->start((ptr_t)UserMain);
#if TESTING_PING_LOOP
  for (;;) {
    Timeout::sleep(Clock::now() + 1000);
    KOUT::outl("...ping...");
  }
#endif
}

extern "C" void kmain(mword magic, mword addr, mword idx)         __section(".boot.text");
extern "C" void kmain(mword magic, mword addr, mword idx) {
  if (magic == 0 && addr == 0xE85250D6) {
    // low-level machine-dependent initialization on AP
    Machine::initAP(idx);
  } else {
    // low-level machine-dependent initialization on BSP -> starts kosMain
    Machine::initBSP(magic, addr, idx);
  }
}
