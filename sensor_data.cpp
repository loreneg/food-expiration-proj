// AHT10 - module I2C, replace DHT11 SHT20
#include <Wire.h>
#define AHT10_ADDRESS 0x38 // AHT10 I2C address

// Function to read temperature and humidity from AHT10
void readAHT10Data(float& temperature, float& humidity) {
    Wire.beginTransmission(AHT10_ADDRESS);
    Wire.write(0xAC);  // Command for reading sensor data
    Wire.endTransmission();

    delay(75);  // Wait for data to be ready

    Wire.requestFrom(AHT10_ADDRESS, 6);

    if (Wire.available() == 6) {
        // Read temperature and humidity data
        int32_t rawTemperature = (Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
        int32_t rawHumidity = (Wire.read() << 16) | (Wire.read() << 8) | Wire.read();

        // Convert raw data to floating-point values
        temperature = (static_cast<float>(rawTemperature) * 200.0) / 0x100000 - 50.0;
        humidity = (static_cast<float>(rawHumidity) * 100.0) / 0x100000;
    }
}
