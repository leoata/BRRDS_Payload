#include <Adafruit_ICM20649.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPRLS.h>
#include <Wire.h>
#include "SD.h"

Adafruit_ICM20649 icm;
Adafruit_Sensor *icm_temp, *icm_accel, *icm_gyro;
Adafruit_MPRLS mpr = Adafruit_MPRLS();

File sd;
String fileName;

void setup(void)
{
    Serial.begin(9600);
    Wire.begin();

    mpr.begin();
    icm.begin_I2C();

    // create name of file
    unsigned long time = millis();
    String time_string = String(time, 10);
    fileName = "test_";
    fileName.concat(time_string);
    fileName.concat(".csv");

    // open and write headers
    SD.begin(8);
    sd = SD.open(fileName.c_str(), FILE_WRITE);
    sd.write("time,temperature,accelx,accely,accelz,gyrox,gyroy,gyroz,pressurehPa\n");
    Serial.println("time,temperature,accelx,accely,accelz,gyrox,gyroy,gyroz,pressurehPa\n");
    // save and re-open
    sd.close();
    sd = SD.open(fileName.c_str(), FILE_WRITE);
}

String imu_loop();

String mprls_loop(Adafruit_MPRLS *mpr);

void loop()
{
    String s;
    s.concat(millis());
    s.concat(",");
    String mprls1 = mprls_loop(&mpr);

    s.concat(imu_loop());

    s.concat(",");
    s.concat(mprls1);
    s.concat("\n");
    Serial.print(s);
    sd.write(s.c_str());
    sd.close();
    sd = SD.open(fileName.c_str(), FILE_WRITE);
}

String imu_loop()
{
    //   Get a new normalized sensor event
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

String mprls_loop(Adafruit_MPRLS *mpr)
{
    float pressure_hPa = mpr->readPressure();
    return String(pressure_hPa);
}
