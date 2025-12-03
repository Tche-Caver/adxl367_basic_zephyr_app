#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/dt-bindings/sensor/adxl367.h>

#include <app_version.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);


int main(void)
{

	const struct device *accelerometer;

	struct sensor_value  valx,  valy,  valz;
	double output [3];

	printk("ADXL367 sample application\n");

	//Get device structure pointer from Devicetree using the alias specified in Devicetree
	accelerometer = DEVICE_DT_GET(DT_ALIAS(accel));

	while (1) {

	//Obtain a sample from the accelerometer.  This sample will be stored internally in the driver
	//Provide device struct pointer as a parameter
	sensor_sample_fetch(accelerometer);

	//After a sample is obtained, return a value to the application, in the form of a sensor_value struct
	sensor_channel_get(accelerometer,  SENSOR_CHAN_ACCEL_X, &valx);
	sensor_channel_get(accelerometer,  SENSOR_CHAN_ACCEL_Y, &valy);
	sensor_channel_get(accelerometer,  SENSOR_CHAN_ACCEL_Z, &valz);

	//Convert the two int32 values in the struct to a double
	output[0] = (double) valx.val1 + (double) valx.val2 / 1000000;
	output[1] = (double) valy.val1 + (double) valy.val2 / 1000000;
	output[2] = (double) valz.val1 + (double) valz.val2 / 1000000;

	//Output values
	printk("X: %f, Y: %f, Z: %f\n", output[0], output[1], output[2]);

	}

	return 0;
}

