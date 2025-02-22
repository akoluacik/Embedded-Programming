/*
 * sensors.h
 *
 *  Created on: 16 Nis 2023
 *      Author: anil
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include <stdint.h>

typedef enum
{
	SENSOR_OK,
	SENSOR_ERROR
} sensor_resp_t;

typedef enum {
	TEMPERATURE_SENSOR = 0,
	HUMIDITY_SENSOR,
	CO2_SENSOR
} sensor_t;

/* Initialization Functions */
sensor_resp_t initTempSensor(void);
sensor_resp_t initHumiditySensor(void);
sensor_resp_t initCO2Sensor(void);

/* Measure Functions (each calls float i2c_sensor_read(uint8_t device_address, enum sensor_t sensor_type)) */
void	measure_temperature(uint8_t device_address);
void	measure_humidity(uint8_t device_address);
void	measure_co2(uint8_t device_address);

#endif /* INC_SENSORS_H_ */
