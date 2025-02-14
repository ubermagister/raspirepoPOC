#include <cstdio.h>

int main(void)

// I2C pins need to be configured, for example for pin 22 & 21 for 
// the M5StickC Plus. These pins might be different for other boards.
Configuration.SetPinFunction(10, DeviceFunction.I2C1_CLOCK);
Configuration.SetPinFunction(8, DeviceFunction.I2C1_DATA);

I2cConnectionSettings settings = new(1, Mpu6886AccelerometerGyroscope.DefaultI2cAddress);

using (Mpu6886AccelerometerGyroscope ag = new(I2cDevice.Create(settings)))
{
    Debug.WriteLine("Start calibration ...");
    var offset = ag.Calibrate(1000);
    Debug.WriteLine("Calibration done, calculated offsets {offset.X} {offset.Y} {offset.Y}");

    Debug.WriteLine("Internal temperature: {ag.GetInternalTemperature().DegreesCelsius} C");

    while (true)
    {
        var acc = ag.GetAccelerometer();
        var gyr = ag.GetGyroscope();
        Debug.WriteLine("Accelerometer data x:{acc.X} y:{acc.Y} z:{acc.Z}");
        Debug.WriteLine("Gyroscope data x:{gyr.X} y:{gyr.Y} z:{gyr.Z}\n");
        Thread.Sleep(100);
    return 0;
    }
}
/** kaikki k�ytetyt pikakommennot l�ytyy t�st�!

registers 0x05 to 0x0b: low noise to low power offset
registers 0x0d to 0x0F: self test
register 0x1a: FIFO mode, DLPF (digital low pass filter)
register 0x1d bit 0 to 3: DLPF
register 0x1e bit 4 to 6: averaging filter for low power mode
registers 0x20 to 0x22: threshold for wake-on motion
register 0x36: fsync interrupt status
register 0x37: INT/DRDY pin config
register 0x39 and 0x3a: FIFO watermark interrupt
register 0x60 and 0x61: FIFO watermark interrupt
register 0x68: signal path reset
register 0x69: acc. intelligence control
**/