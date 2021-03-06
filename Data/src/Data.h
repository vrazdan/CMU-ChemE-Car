/*
  Data.h - Library for general use in the DATA team for CMU ChemE-Car
  Created by Xavier Artache, February 8, 2016.
  Released into the public domain.
*/

#ifndef DATA_H
#define DATA_H

#include <Arduino.h>
#include <SD.h>
//#include <SPI.h>
#include "utility/Utility.h"
#include "utility/Timer.h"
#include "utility/Series.h"
#include "utility/Measurement.h"
#include "utility/Sensor.h"
#include "utility/VoltageSensor.h"
#include "utility/TemperatureSensor.h"
#include "utility/HallEffectSensor.h"
#include "utility/WheelSensor.h"
#include "utility/PhotoSensor.h"
#include "utility/SwitchSensor.h"
#include "utility/INA219CurrentSensor.h"
#include "utility/Actuator.h"
#include "utility/MotorActuator.h"

#define DEFAULTBAUD 9600
#define MAXFILENAME 8

class DataClass {

  public:
    /* General Functions */
	void print();
	void println();
	void print(String str);
	void println(String str);
	void print(int x);
	void println(int x);
	void print(float x, int dec = DEFAULTDEC);
	void println(float x, int dec = DEFAULTDEC);
	void freeze();
	void beginSerial(int baud = DEFAULTBAUD);
	void beginTimer();
	float currentTime();
	void timePrint(int dec = DEFAULTDEC);
	void timePrintln(int dec = DEFAULTDEC);
	void startBluetooth();
	void stopBluetooth();
	void debugBluetooth(String str);
	void debugBluetooth(int x);
	void debugBluetooth(float x, int dec = DEFAULTDEC);
	void beginSD(int pin);

	/* Data Transfer Functions */
	void display(Sensor* sensor, int timeDec = DEFAULTDEC,
	  int valueDec = DEFAULTDEC);
	void display(Actuator* actuator, int timeDec = DEFAULTDEC,
	  int valueDec = DEFAULTDEC);
	void display(Measurement* measurement, int timeDec = DEFAULTDEC,
	  int valueDec = DEFAULTDEC);
	void sendBluetooth(Sensor* sensor, int timeDec = DEFAULTDEC,
	  int valueDec = DEFAULTDEC);
	void sendBluetooth(Actuator* actuator, int timeDec = DEFAULTDEC,
	  int valueDec = DEFAULTDEC);
	void sendBluetooth(Measurement* measurement, int timeDec = DEFAULTDEC,
	  int valueDec = DEFAULTDEC);
	void sendSD(Sensor* sensor, int newTrial, int trialNum, 
          int timeDec = DEFAULTDEC, int valueDec = DEFAULTDEC);
	void sendSD(Actuator* actuator, int timeDec = DEFAULTDEC,
	  int valueDec = DEFAULTDEC);
	void sendSD(Measurement* measurement, int timeDec = DEFAULTDEC,
	  int valueDec = DEFAULTDEC);


	/* Utility Wrappers */
	String floatToString(float x, int dec = DEFAULTDEC);
	String dataLine(String name, String time, String value);
	float millisToSeconds(unsigned long ms);
    unsigned long secondsToMillis(float s);
    float scale(float value, float max = V5);


	/* Timer */
	Timer timer();

	/* Series */
	Series series(int size);

	/* Measurement */
	Measurement measurement(String name, float (*measureValue)());
	Measurement measurement(String name, float (*measureValue)(), Timer time);


	/* Sensors */

    /** Sensor **/
    Sensor sensor(String name, byte pin);
    Sensor sensor(String name, byte pin, Timer time);

	/** VoltageSensor **/
    VoltageSensor voltageSensor(String name, byte pin, float R1, float R2);
    VoltageSensor voltageSensor(String name, byte pin, Timer time,
    	float R1, float R2);

	/** TemperatureSensor **/
    TemperatureSensor temperatureSensor(String name, byte pin, int mode = MODE_C);
    TemperatureSensor temperatureSensor(String name, byte pin, Timer time,
    	int mode = MODE_C);

    /** HallEffectSensor **/
    HallEffectSensor hallEffectSensor(String name, byte pin);
    HallEffectSensor hallEffectSensor(String name, byte pin, Timer time);

    /** WheelSensor **/
    WheelSensor wheelSensor(String name, byte pin,
        float wheelRadius, int numMagnets);
    WheelSensor wheelSensor(String name, byte pin, Timer time,
        float wheelRadius, int numMagnets);
	
	/** PhotoSensor **/
	PhotoSensor photoSensor(String name, byte pin, float R);
	PhotoSensor photoSensor(String name, byte pin, Timer time, float R);

	/** SwitchSensor **/
	SwitchSensor switchSensor(String name, byte pin);
	SwitchSensor switchSensor(String name, byte pin, Timer time);

    /** INA219CurrentSensor **/
    INA219CurrentSensor ina219CurrentSensor(String name);
    INA219CurrentSensor ina219CurrentSensor(String name, Timer time);


	/* Actuators */

	/** Actuator **/
	Actuator actuator(String name, byte pin);
	Actuator actuator(String name, byte pin, Timer time);

	/** MotorActuator **/
	MotorActuator motorActuator(String name, byte pin);
	MotorActuator motorActuator(String name, byte pin, Timer time);

  private:
	void _signalBluetooth();
	String _filenameForSD(String name);

    Timer _timer;
};

extern DataClass Data;

#endif
