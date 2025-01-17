# Snek — a tiny python-inspired language for embedded computing

![Snek picture](snek.svg)

Snek is a tiny embeddable language targeting processors with only a
few kB of flash and ram. Think of something that would have been
running BASIC years ago and you'll have the idea. These processors are
too small to run [MicroPython](https://micropython.org/).

## Documentation

 * The [Snek Home Page](https://keithp.com/snek) provides more information
   about the language and community.

 * [Snek Manual in HTML format](https://keithp.com/snek/snek.html)

 * [Snek Manual in PDF format](https://keithp.com/snek/snek.pdf)

## Downloads

 * Snek is packaged for Debian but not yet in the main archive. I have
   made packages available in my personal archive for
   now. Instructions for using that can be found
   [here](http://keithp.com/archive/README).  This archive also
   includes _lola_, the LL parser generator used in building Snek.

 * Packages for Linux, Mac OS X and Windows are available in the
   [Snek Dist directory](http://keithp.com/snek/dist)

## To Do list

I think the basic Snek language is pretty complete at this point, but
there are always improvements that can be made.

## Recent Changes

Here's some places that have seen recent work

 * [Adafruit ItsyBitsy 5V](https://www.adafruit.com/product/3677)
   port.  This device uses the Atmel ATmega 32u4 SoC which is similar
   to the 328P, but has integrate USB support so it doesn't need an
   external USB to serial converter. Getting a USB stack tucked into
   the ROM took some squeezing, and I had to remove some functionality
   (random numbers and pre-defined port names) to make it fit.

 * [NeoPixel](https://learn.adafruit.com/adafruit-neopixel-uberguide)
   driver.  NeoPixel is Adafruit's name for the WS2812 (and similar)
   scalable full-color light source. The current driver is
   samd21g-specific, but could be ported to other SoCs.
   
 * [Circuit Playground Express](https://www.adafruit.com/product/3333)
   port.  The 10 integrated NeoPixels encourated me to write a
   NeoPixel driver. This still needs drivers for the accelerometer,
   speaker and microphone.

 * [Crickit FeatherWing](https://www.adafruit.com/product/3343) port.
   This device has built-in drivers for motors and other devices,
   along with convenient plugs for other devices. If you want to get
   started building Snek robots, this is a great board to buy.

## Build and Run!

If you want to build Snek yourself, 

### Dependencies
To build Snek you need these dependencies:

  * [Lola](https://keithp.com/cgit/lola.git/)
  * [gcc-avr](https://ccrma.stanford.edu/~juanig/articles/wiriavrlib/AVR_GCC.html)
  * [avr-libc](https://www.nongnu.org/avr-libc/)
  * [gcc-arm-none-eabi](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
  * [newlib-nano](https://keithp.com/newlib-nano/)
  * [python3](https://www.python.org/)
  * [pyserial](https://github.com/pyserial/)
  * [python curses](https://docs.python.org/3/library/curses.html)

On Debian, you can get everything other than Lola from the main archive:

	# apt install gcc-avr avr-libc python3-serial gcc-arm-none-eabi libnewlib-nano-arm-none-eabi

To install Lola, download the source and install it;

	$ git clone git://keithp.com/git/lola.git
	$ cd lola && make install

### Building and install

In the source of the project run:

	$ make
	$ make install

## Running on Embedded Devices

Snek is designed to run on small embedded devices with 32kB or more of
flash and 2kB or more of RAM. Snek has been ported to a variety of
embedded devices, providing access to pins as GPIOs as well as some
built-in peripherals. Documentation about the supported boards can be
found in the [Snek Manual](https://keithp.com/snek/snek.html).

## Running on Linux, Mac OS X Windows

Snek is also built to run natively on Linux, Mac OS X and
Windows. When installed, you'll find it available in the regular
system menu.

## The Snek Development Environment

Snekde is provided on all three platforms; you'll find it in the
system menu on Linux and Windows and down in your personal
Applications directory on Mac OS X.

The snekde window is split into two parts. The upper 2/3 is a text
editor for source code. The bottom 1/3 lets you interact with the
Snek device over the USB port. The very top line lists functions that
you can invoke by pressing the associated function key:

 * F1 — Device. Connect to a serial port.
 * F2 — Get. Get source code saved to the Snek device eeprom into the editor pane.
 * F3 — Put. Put code from the editor pane into the Snek device eeprom.
 * F4 — Quit. Exit snekde.
 * F5 — Load. Read source code from the file system into the editor pane.
 * F6 — Save. Write source code from the editor pane to the file system.

There are a couple more keybindings which you'll want to know:

 * Page-up/Page-down — Switch between the editor pane and the interaction pane.
 * Ctrl-X/Ctrl-C/Ctrl-V — Usual cut/copy/paste commands.
 * Ctrl-C — In the interaction pane, this interrupts any snek program running on the device. Note that
   this means you don't get a Copy command in the interaction pane.
 * Ctrl-Z — Undo.

Tab auto-indents the current line. Backspace backs up over a tabstop
when appropriate.

## Examples

There are examples provided, some of which work with both Python and
Snek, and some of which show how to use SoC-specific APIs that aren't
available in Python.

## Contributions

I'd love to receive more contributions in the form of patches,
suggestions and bug reports. Please feel free to send mail or use the
github process. I've created a mailing list for collaboration; 
you'll need to subscribe to be able to post. Subscribe to the [snek
mailing list here](https://keithp.com/mailman/listinfo/snek)
