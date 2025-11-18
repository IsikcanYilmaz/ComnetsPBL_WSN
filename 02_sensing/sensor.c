#include "sensor.h"
#include "shell.h"

i2c_t i2cDevice;

bool Sensor_GetChipId(uint8_t *id)
{
  int ret = i2c_read_reg(i2cDevice, TEMP_SENSOR_I2C_ADDR, TEMP_SENSOR_REG_CHIP_ID, id, 0);
  return (ret == 0);
}

bool Sensor_Reset(void)
{
  // The “reset” register contains the soft reset word reset[7:0]. If the value 0xB6 is written to the register,
  // the device is reset using the complete power-on-reset procedure. Writing other values than 0xB6 has
  // no effect. The readout value is always 0x00
  //
  // Optional //
  return true;
}

bool Sensor_EnableSampling(void)
{
  // This is where you tell the chip to start sampling
}

bool Sensor_Init(void)
{
  if ((TEMP_SENSOR_I2C_NUM < 0) || (TEMP_SENSOR_I2C_NUM >= (int)I2C_NUMOF)) {
    printf("I2C device with number \"%d\" not found\n", TEMP_SENSOR_I2C_NUM);
    return false;
  }
  i2cDevice = I2C_DEV(TEMP_SENSOR_I2C_NUM);
  i2c_acquire(i2cDevice);
  return true;
}

void Sensor_Deinit(void)
{
  i2c_release(i2cDevice);
}

int Sensor_CmdHandler(int argc, char **argv)
{
  if (argc < 2)
  {
    goto usage;
  }
  if (strncmp(argv[1], "id", 16) == 0)
  {
    uint8_t id = 0xff;
    bool ret = Sensor_GetChipId(&id);
    printf("0x%x (%s) \n", id, (id == TEMP_SENSOR_CHIP_ID) ? "CORRECT" : "INCORRECT");
  }
  return 0;

  usage:
  printf("Usage: sensor <id>");
  return 1;
}
SHELL_COMMAND(sensor, "Sensor cmd handler", Sensor_CmdHandler);
