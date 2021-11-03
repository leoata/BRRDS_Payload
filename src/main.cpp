#include <Adafruit_ICM20649.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPRLS.h>
#include <Wire.h>
#include "SD.h"
#include "PWFusion_TCA9548A.h"

Adafruit_ICM20649 icm;
Adafruit_Sensor *icm_temp, *icm_accel, *icm_gyro;
TCA9548A i2cMux;
Adafruit_MPRLS mpr = Adafruit_MPRLS();
File sd;
String fileName;

void setup(void)
{
    Serial.begin(9600);
    Wire.begin();

    i2cMux.begin();
    icm.begin_I2C();
    mpr.begin();

    SD.begin(8);
    unsigned long time = millis();
    String time_string = String(time, 10);
    fileName = "test_";
    fileName.concat(time_string);
    fileName.concat(".csv");
    sd = SD.open(fileName.c_str(), FILE_WRITE);
    sd.write("time,temperature,accelx,accely,accelz,gyrox,gyroy,gyroz,pressurehPa0,pressurehPa1,pressurehPa3,pressurehPa7\n");
}

String imu_loop();

String mprls_loop(uint8_t chan);

void loop()
{
    String s;
    s.concat(millis());
    s.concat(",");
    String mprls0 = mprls_loop(CHAN0);
    String mprls1 = mprls_loop(CHAN1);
    String mprls3 = mprls_loop(CHAN3);
    String mprls7 = mprls_loop(CHAN7);

    s.concat(imu_loop());
    s.concat(",");
    s.concat(mprls0);
    s.concat(",");
    s.concat(mprls1);
    s.concat(",");
    s.concat(mprls3);
    s.concat(",");
    s.concat(mprls7);
    s.concat("\n");
    Serial.print(s);
    sd.write(s.c_str());
    sd.close();
    sd = SD.open(fileName.c_str(), FILE_WRITE);
}

String imu_loop()
{
    i2cMux.setChannel(CHAN5);

    //  /* Get a new normalized sensor event */
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
    icm.getEvent(&accel, &gyro, &temp);
    String res;
    res.concat(temp.temperature);
    res.concat(",");
    res.concat(accel.acceleration.x);
    res.concat(",");
    res.concat(accel.acceleration.y);
    res.concat(",");
    res.concat(accel.acceleration.z);
    res.concat(",");
    res.concat(gyro.gyro.x);
    res.concat(",");
    res.concat(gyro.gyro.y);
    res.concat(",");
    res.concat(gyro.gyro.z);
    return res;
}

String mprls_loop(uint8_t chan)
{
    i2cMux.setChannel(chan);
    float pressure_hPa = mpr.readPressure();
    return String(pressure_hPa);
}
