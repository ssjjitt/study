int LEDrot = 12;
int LEDgelb = 11;
int LEDgruen = 10;
int cnt = 0;
int state = 0;
int var = 0;

void setup()
{
  pinMode(LEDrot, OUTPUT);
  pinMode(LEDgelb, OUTPUT);
  pinMode(LEDgruen, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available()) {
    char command = Serial.read();
    switch (command) {
      case 'N':
        state = 1;
      	var = 1;
        Serial.println("Включен режим normal");
        break;
      case 'S':
        state = 1;
      	var = 2;
        Serial.println("Включен режим sleep");
        break;
      case 'R':
        state = 1;
      	var = 3;
        Serial.println("Включен режим red");
        break;
      case 'G':
        state = 1;
      	var = 4;
        Serial.println("Включен режим green");
        break;
    }
  }
  if(var == 1){
  	cnt++;
   	if (cnt == 100)
  	{
    cnt = 0;
    Statemaschine();
  	}
  	delay(10);
  }
  else if(var == 2){
  	cnt++;
   	if (cnt == 100)
  	{
    cnt = 0;
    Statemaschine2();
  	}
  	delay(10);
  }
  else if(var == 3){
  	cnt++;
   	if (cnt == 100)
  	{
    cnt = 0;
    Statemaschine3();
  	}
  	delay(10);
  }
  else if(var == 4){
  	cnt++;
   	if (cnt == 100)
  	{
    cnt = 0;
    Statemaschine4();
  	}
  	delay(10);
  }
}

void Statemaschine() // СВЕТОФОР
{
  switch (state)
  {
    case 1:
      digitalWrite(LEDrot, HIGH);
      digitalWrite(LEDgelb, LOW);
      digitalWrite(LEDgruen, LOW);
      state++;
      break;
    case 2:
      digitalWrite(LEDrot, HIGH);
      digitalWrite(LEDgelb, HIGH);
      digitalWrite(LEDgruen, LOW);
      state++;
      break;
    case 3:
      digitalWrite(LEDrot, LOW);
      digitalWrite(LEDgelb, LOW);
      digitalWrite(LEDgruen, HIGH);
      state++;
      break;
    case 4:
      digitalWrite(LEDrot, LOW);
      digitalWrite(LEDgelb, HIGH);
      digitalWrite(LEDgruen, LOW);
      state++;
      break;
  }

  if (state > 4) {
    state = 1;
  }
}

void Statemaschine2() // ТОЛЬКО ЖЕЛТЫЙ
{
  switch (state)
  {
    case 1:
      digitalWrite(LEDrot, LOW);
      digitalWrite(LEDgelb, HIGH);
      digitalWrite(LEDgruen, LOW);
      state++;
      break;
    case 2:
      digitalWrite(LEDrot, LOW);
      digitalWrite(LEDgelb, LOW);
      digitalWrite(LEDgruen, LOW);
      state++;
      break;
  }
  if(state > 2){
    state = 1;
  }
}

void Statemaschine3() // ТОЛЬКО ЖЕЛТЫЙ
{
  switch (state)
  {
    case 1:
    while(state){  
    	digitalWrite(LEDrot, HIGH);
      digitalWrite(LEDgelb, LOW);
      digitalWrite(LEDgruen, LOW);
      break;
  	}
  }
}
void Statemaschine4() // ТОЛЬКО ЖЕЛТЫЙ
{
  switch (state)
  {
    case 1:
    while(state){  
    	digitalWrite(LEDrot, LOW);
      digitalWrite(LEDgelb, LOW);
      digitalWrite(LEDgruen, HIGH);
      break;
  	}
  }
}