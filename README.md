# Part I: Using sensors with Arduino 
## Arduino Digital/Analog pins 
All Arduinos are equipped with a combination of analog (A1-AX) and digital (1-Y) pins (see graphic below). Analog pins allow the Arduino to sense a voltage within a particular range. When using an analog sensor, this range can be 0-3.3V or 0-5V, depending on how the sensor is wired. Digital pins can be used to sense or output a binary signal - either high (5V on the Arduino Uno), or low (0V on the Arduino Uno). Because they can read and write high or low values, digital pins can be used to transfer data in various communication protocols. 

[pinout image] 

## Types of sensors 

Consequently, sensors communicate with an Arduino through digital or analog pins. Analog sensors allow the Arduino to sense a voltage that indicates the sensor's current reading; for example, a thermistor is a resistor that changes resistance depending on the current temperature. By building a circuit with a thermistor, the Arduino can determine the current temperature as a function of the sensor's resistance. 

Digital sensors can communicate with the Arduino using a variety of protocols, such as [I2C](https://learn.sparkfun.com/tutorials/i2c) or [SPI](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi). These protocols allow the sensor to transfer data to the Arduino. In contrast to the thermistor, which required an Arduino to read the sensor's resistance and determine the temperature, a digital temperature sensor may simply transmit the current temperature to the Arduino. 

## Reading from sensors 

### Hooking up the sensor 
Wiring a sensor to an Arduino depends on the communication protocol in use. This tutorial will cover wiring with an analog sensor and a digital I2C sensor. All sensors mentioned in the tutorial are available at Treehacks. Many of them come with circuit boards that simplify the wiring. 

#### Analog Sensors 
We'll go over how to use one of Treehacks' photoresistors with an Arduino Uno. Take the sensor breakout and plug in one of the three pin attachment cables. This cable allows easy connection to an Arduino or breadboard. Plug the black lead (labeled GND) into a GND (ground, or 0V) pin on the Arduino, the red (labeled VCC) into the Uno's 5V pin, and the yellow cable into A5. 

[wiring picture]

Now that the sensor is wired, we've got to upload and run code to test it. Open (or [download](https://www.arduino.cc/en/main/software) and open) the Arduino app, and open the file "photoresistor/photoresistor/ino" located in this repository. 

```
/* 
 *  Photoresistor sample code. Prints out value of photoresistor 
 *  reading on analog pin A5. 
 */

int pin = A5;  
int val = 0; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(pin);
  Serial.println(val);
}
```

This code is quite simple: it takes an integer analog reading and prints it to the Serial monitor, which can be opened from the Arduino app. You should see a stream of numbers: 
```
283
290
294
305
309
315
318
330
349
354
356
363
368
370
```
The Arduino Uno's analog precision is 10 bits, or it provides analog readings from 0 to 1023. As a result, we can take each of these readings and divide them by 1024 to scale the brightness readings from 0 to 1. We could also scale from 0 to 5 volts by multiplying by 5V. From these raw readings, we can intuitively see relative brightness, or the difference bewteen light and dark. With my finger over the sensor, readings rose to ~800; with my phone's light near it, they dropped to 30. 

By consulting the [datasheet](https://www.kth.se/social/files/54ef17dbf27654753f437c56/GL5537.pdf) for the photoresistor, we can then determine the ambient brightness in lux (a unit of illumination). 

#### Digital Sensors 


#### PWM with a laser transmitter


### Finding or writing code 

## Using data from sensors 
## Sensors available 

# Part II: Interfacing an Arduino with Desktop Applications 
## Building Python and Processing apps that talk to Arduinos (via USB)

This section of the hackpack covers the process of writing simple Arduino programs that interact with a computer. This permits fairly effortless interaction between sensors and desktop applications, such as visualizations of sensor data, peripheral control of computer systems, or controlling robotics devices. 

We begin with a brief outline of serial communication and proceed to create a simple app that communicates from an Arduino to a desktop computer. Note that a similar procedure can be used to connect an Arduino to a Raspberry Pi. 

Serial communication through a UART port enables an Arduino to send messages to other devices, such as a desktop computer or another Arduino. Serial communication is a frequently used protocol to send data among devices; prior to USB, many computer peripherals were serial devices. Today, UART ports are frequently used to send data from an embedded device, such as an Arduino or Raspberry Pi, to sensors, including a GPS or LCD display. For more information on the mechanics of serial communication, consult: https://learn.sparkfun.com/tutorials/serial-communication. 

Clone this repository by running `git clone https://github.com/TreeHacks/hackpack-arduino-app.git` from your command line. It includes this readme and sample code. 

## Arduino: Using the Serial Monitor 

The serial monitor is perhaps the most important debugging tool for Arduino programs. See the "Hello, World" program as an example: 

```
// The setup function is required and runs a single time when the program starts
void setup() {
  Serial.begin(9600);
}

// The loop function loops infinitely after the setup function returns 
void loop() {
	Serial.println("Hello, world!"); 
	delay(1); // Delay one second 
}

```

To see "Hello, World" on your computer, open the Arduino application, choose the proper board (under tools -> board), and open the serial monitor. The example initializes serial communication with a speed of 9600 bits per second, so select 9600 after opening the serial monitor. 

This guide does not cover using more complex sensors and devices with an Arduino, but a general outline of sending this data to a computer follows: 

1) Collect the data in some variable 
2) Print the variable to the Serial port 
3) Receive it with a desktop application 

## Desktop: Writing apps to work with Arduino 
### Python 
To start, install pySerial by running `pip install pyserial` in your terminal window. 

Now, we will look at a basic program to read data from an Arduino: 

```
import serial 
ser = serial.Serial('/dev/tty.usbserial', 9600)

while True:
	print ser.readline()

```

Save this in a file "serial_demo.py". This python program creates a serial port and prints any data received over serial. If you connect your Arduino and, from the directory containing "serial_demo.py" type "python serial_demo.py", you should see "Hello, World" printed on your computer. More complex applications and two way communication can be implemented using `ser.write(val)` to send messages back to the Arduino.

### Processing 
Processing can be downloaded at https://processing.org/. With similar syntax to Java, it is designed for building fairly simple graphical applications. Thus, making two or three dimensional visualizations of Arduino data is simple in Processing. 

This guide will discuss a simple example in Processing for serial communication. 

```
Serial myPort;  // Create Serial object
String val;  	// For serial data

void setup() {
	// Serial.list() provides a list (of strings) of all open serial ports. 
	// You may have to change the 0 below to 1 or 2 depending on the port your 
	// Arduino is using. 
	println(Serial.list()); 
	String portName = Serial.list()[0]; // May change 0 to 1 or 2
	myPort = new Serial(this, portName, 9600);
	size(100, 100); 
}

void draw() {
  	if ( myPort.available() > 0 ) {  		// If data is available in the serial port, 
  		val = myPort.readStringUntil('\n'); // store it in val
  	} 
  	if ( val == "Hello, world" ) {
  		background(random(255), random(255), random(255)); // change the background color
  	}
	println(val); // print data to console 
}
```

Similar to Arduino, Processing sketches include a `setup` function, that runs once, and a `draw` function that runs repeatedly until the application quits. This program creates and opens a Serial port and prints any data received from the port to the console. 

### Other Languages 

Though Processing and python provide some of the simplest methods for interfacing an Arduino with a computer, many other languages, including Matlab and Java, provide serial communication libraries for interacting with an Arduino. 

## Reading and Writing 

It is possible to perform two way communication with the Arduino as well. Generally, it is good practice to perform some sort of handshake between the microcontroller and the computer to ensure both devices are sending messages when expected. This can be as simple as: 

```
void testContact() {
	// While there are no bytes incoming on the Serial 
	while (Serial.available() <= 0) {
		Serial.println("ABC"); 
	}
}
```

Note that the line `while (Serial.available() <= 0)` will be true while there are no bytes waiting for the Arduino to process. 

## Credit

https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing for some Processing examples, http://playground.arduino.cc/Interfacing/Python for python examples. 

by Andrew 