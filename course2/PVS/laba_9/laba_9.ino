#include <math.h>
int minute = 1;
int row_excel = 0;
int test = 123;
int test_2 = 456;
#define TERMIST_B 4300
#define VIN 5.0
void setup() {
  Serial.begin(9600);
  Serial.println("Minute\tTemperature");
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,Test 1, Test 2, temp");
}

void loop() {
  float voltage = analogRead(A0) * VIN / 1024.0;
  float r1 = voltage / (VIN - voltage);
  float temperature = 1. / (1. / (TERMIST_B)*log(r1) + 1. / (25. + 273.)) - 273;
  Serial.print(minute);
  Serial.print("\t");
  Serial.println(temperature);
  delay(6000);
  ++minute;
  row_excel++;
  Serial.print("DATA,TIME,");
  Serial.print(test);
  Serial.print(",");
  Serial.print(test_2);
  Serial.print(",");
  Serial.println(temperature);
  Serial.print(",");
  Serial.println(row_excel);
  
  if (row_excel > 50) {
    row_excel = 0;
    Serial.println("ROW,SET,2");
  }
  delay(1000);
}
