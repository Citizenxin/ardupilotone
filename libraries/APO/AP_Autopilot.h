/*
 * AP_Autopilot.h
 *
 *  Created on: Apr 30, 2011
 *      Author: jgoppert
 */

#ifndef AP_AUTOPILOT_H_
#define AP_AUTOPILOT_H_

/*
 * AVR runtime
 */
#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <math.h>
/*
 * Libraries
 */
#include "../AP_Common/AP_Common.h"
#include "../FastSerial/FastSerial.h"
#include "../AP_GPS/GPS.h"
#include "../APM_RC/APM_RC.h"
#include "../AP_ADC/AP_ADC.h"
#include "../APM_BMP085/APM_BMP085.h"
#include "../AP_Compass/AP_Compass.h"
#include "../AP_Math/AP_Math.h"
#include "../AP_IMU/AP_IMU.h"
#include "../AP_DCM/AP_DCM.h"
#include "../AP_Common/AP_Loop.h"
#include "../GCS_MAVLink/GCS_MAVLink.h"
#include "../AP_RangeFinder/AP_RangeFinder.h"
/*
 * Local Modules
 */
#include "AP_HardwareAbstractionLayer.h"
#include "AP_RcChannel.h"
#include "AP_Controller.h"
#include "AP_Navigator.h"
#include "AP_Guide.h"
#include "AP_CommLink.h"
#include "controllers.h"

/**
 * ArduPilotOne namespace to protect varibles
 * from overlap with avr and libraries etc.
 * ArduPilotOne does not use any global
 * variables.
 */
namespace apo {

// forward declarations
class AP_CommLink;

/**
 * This class encapsulates the entire autopilot system
 * The constructor takes the serial streams available
 * and attaches them to the appropriate devices.
 * Also, since APM_RC is globally instantiated this
 * is also passed to the constructor so that we
 * can avoid and global instance calls for maximum
 * clarity.
 *
 * It inherits from loop to manage
 * the subloops and sets the overal
 * frequency for the autopilot.
 *

 */
class AP_Autopilot: public Loop {
public:
	/**
	 * Default constructor
	 */
	AP_Autopilot(AP_Navigator * navigator, AP_Guide * guide, AP_Controller * controller,
			AP_HardwareAbstractionLayer * hal);

	/**
	 * Accessors
	 */
	AP_Navigator * navigator() {
		return _navigator;
	}
	AP_Guide * guide() {
		return _guide;
	}
	AP_Controller * controller() {
		return _controller;
	}
	AP_HardwareAbstractionLayer * hal() {
		return _hal;
	}

private:

	/**
	 * Loop 0 Callbacks (fastest)
	 * - inertial navigation
	 * @param data A void pointer used to pass the apo class
	 *  so that the apo public interface may be accessed.
	 */
	static void callback0(void * data);

	/**
	 * Loop 1 Callbacks
	 * - control
	 * - compass reading
	 * @see callback0
	 */
	static void callback1(void * data);

	/**
	 * Loop 2 Callbacks
	 * - gps sensor fusion
	 * - compass sensor fusion
	 * @see callback0
	 */
	static void callback2(void * data);

	/**
	 * Loop 3 Callbacks
	 * - slow messages
	 * @see callback0
	 */
	static void callback3(void * data);

	/**
	 * Loop 4 Callbacks
	 * - super slow mesages
	 * - log writing
	 * @see callback0
	 */
	static void callback4(void * data);

	/**
	 * Components
	 */
	AP_Navigator * _navigator;
	AP_Guide * _guide;
	AP_Controller * _controller;
	AP_HardwareAbstractionLayer * _hal;

	/**
	 * Constants
	 */
	static const float deg2rad = M_PI / 180;
	static const float rad2deg = 180 / M_PI;
};

} // namespace apo

#endif /* AP_AUTOPILOT_H_ */