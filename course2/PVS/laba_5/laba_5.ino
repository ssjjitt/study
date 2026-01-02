#define LED_PIN_RED 9
#define LED_PIN_GREEN 10
#define LED_PIN_BLUE 11
String command;

void setup()
{
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_BLUE, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available())
  {
    char incomingChar = Serial.read();
    if (incomingChar != '\n')
    {
      command += incomingChar;
    }
    else
    {
      if (command == "on" || command == "вкл")
      {
        digitalWrite(LED_PIN_RED, HIGH);
        Serial.println("LED включен");
      }
      else if (command == "off" || command == "выкл")
      {
        digitalWrite(LED_PIN_RED, LOW);
        Serial.println("LED выключен");
      }
      else{
      command.trim(); 
      int commaIndex1 = command.indexOf(',');
      int commaIndex2 = command.indexOf(',', commaIndex1 + 1);
      if (commaIndex1 != -1 && commaIndex2 != -1 && command.length() > commaIndex2 + 1)
      {
        String redValueStr = command.substring(0, commaIndex1);
        String greenValueStr = command.substring(commaIndex1 + 1, commaIndex2);
        String blueValueStr = command.substring(commaIndex2 + 1);

        int redValue = redValueStr.toInt();
        int greenValue = greenValueStr.toInt();
        int blueValue = blueValueStr.toInt();

        analogWrite(LED_PIN_RED, redValue);
        analogWrite(LED_PIN_GREEN, greenValue);
        analogWrite(LED_PIN_BLUE, blueValue);

        Serial.print("значения яркости: R=");
        Serial.print(redValue);
        Serial.print(", G=");
        Serial.print(greenValue);
        Serial.print(", B=");
        Serial.println(blueValue);
      }
      else
      {
        Serial.println("введите еще раз");
      }

      command = ""; 
      }
    }
  }
}