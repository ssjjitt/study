#define LED_PIN 9
String command;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
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
      command.toLowerCase(); 
      if (command == "on")
      {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED включен");
      }
      else if (command == "вкл")
      {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED включен");
      }
      else if (command == "off")
      {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED выключен");
      }
      
      else if (command == "off")
      {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED выключен");
      }
      else if (command == "выкл")
      {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED выключен");
      }
      else
      {
        Serial.println("Неизвестная команда");
      }

      command = ""; 
    }
  }
}