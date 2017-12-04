#include <GroveColorSensor.h>
#include <Wire.h>
#include <Registers.h>
#include <Utilities.h>

//Simple test program to read the color sensor
//Convert (R,G,B) to international system CIE

void setup()
{
  // put your setup code here, to run once:

  SerialUSB.begin(9600);
  Wire.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:

  int red, green, blue;
  GroveColorSensor colorSensor;
  float x, y;

  colorSensor.ledStatus = 1;
  while (true)
  {
    colorSensor.readRGB(&red, &green, &blue);
    rgb2xy(red, green, blue, &x, &y);
    delay(800);
    SerialUSB.print("RGB: ");
    SerialUSB.print(red, DEC);
    SerialUSB.print(' ');
    SerialUSB.print(green, DEC);
    SerialUSB.print(' ');
    SerialUSB.print(blue, DEC);
    SerialUSB.print(" -> (X,Y): ");
    SerialUSB.print(x, DEC);
    SerialUSB.print(' ');
    SerialUSB.println(y, DEC);
    colorSensor.clearInterrupt();
  }
}

void rgb2xy(int r, int g, int b, float *x, float *y)
{
  //This function transform RGB to XY (CIE)
  float k, i, j;

  k = -0.14282 * r + 1.54924 * g - 0.95641 * b;
  i = -0.32466 * r + 1.57837 * g - 0.73191 * b;
  j = -0.68202 * r + 0.77073 * g + 0.56332 * b;
  *x = k / (k + i + j);
  *y = i / (k + i + j);
}
