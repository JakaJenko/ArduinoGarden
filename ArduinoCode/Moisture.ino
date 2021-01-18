// Set pins
int analogPin_Soil = 0;
int digitalPin_Rele = 12;
int digitalPin_LED = 11;
int digitalPin_Button = 2;

// Set max and min values of moisture sensor
int moistureMin = 612;
int moistureMax = 300;

// Timers for reading moisture value and turning on irrigation system
unsigned long timers[2];

void setup() {
  // Set serial
  Serial.begin(9600);

  // Set rele ouput
  pinMode(digitalPin_Rele, OUTPUT);
  digitalWrite(digitalPin_Rele, HIGH);

  // Set LED ouput
  pinMode(digitalPin_LED, OUTPUT);
  digitalWrite(digitalPin_LED, LOW);

  // Set Button input
  pinMode(digitalPin_Button, INPUT);

  //Start timers
  startTimer(0);
  startTimer(1);
}

void loop() {
  // If button pressed check the system
  if(digitalRead(digitalPin_Button) == HIGH)
  {
    testSystem();
  }

  if(hasPassed(0, 60000)) //1 min
  {
    int moisturePercent = getAverageMoisture(5);
    bool needsIrigation = isNeedsIrigation(moisturePercent);
    showNumberWithLed(moisturePercent);

    // Send moisture data
    Serial.print("<");
    Serial.print(moisturePercent);
    Serial.println(">");

    // Reset timer
    startTimer(0);
  }

  
  if(hasPassed(1, 3600000)) //1h, 86400000 day
  {
    // Reset timer
    startTimer(1);

    int moisturePercent = getAverageMoisture(5);
    bool needsIrigation = isNeedsIrigation(moisturePercent);
    
    if(needsIrigation)
    {
      digitalWrite(digitalPin_Rele, LOW);
      delay(5000);
      digitalWrite(digitalPin_Rele, HIGH);
    }
  }
  
}

// Map raw values to 0-100
int moistureLevel(int analogValue)
{
  return (analogValue - moistureMin) * (100 - 0) / (moistureMax - moistureMin) + 0;
}

bool isNeedsIrigation(int moisturePercent)
{
  return moisturePercent < 50;
}

// Check moisture multiple times and get average value
int getAverageMoisture(int checks)
{
  int averageMoisture = 0;
  
  for(int i = 0; i<checks; i++)
  {
    int val = analogRead(analogPin_Soil);
    int moisturePercent =  moistureLevel(val);
    averageMoisture += moisturePercent;
    delay(10);
  }

  return int(averageMoisture/checks);
}

// Function to show and int by blinking an LED (long blink = 10, short blink = 1)
int showNumberWithLed(int number)
{
  while(number >= 10)
  {
    digitalWrite(digitalPin_LED, HIGH);
    delay(500);
    digitalWrite(digitalPin_LED, LOW);
    delay(500);
    number -= 10;
  }
  
  delay(1000);
  
  while(number > 0)
  {
    digitalWrite(digitalPin_LED, HIGH);
    delay(250);
    digitalWrite(digitalPin_LED, LOW);
    delay(250);
    number -= 1;
  }
}

// Set time when timer started
void startTimer(int timerNumber)
{
  timers[timerNumber] = millis();
}

// Check if x miliseconds have pasted on the timer
bool hasPassed(int timerNumber, unsigned long milliseconds)
{
  return (millis() - timers[timerNumber]) > milliseconds;
}

void testSystem()
{
  int moisturePercent = getAverageMoisture(5);
  bool needsIrigation = isNeedsIrigation(moisturePercent);
  showNumberWithLed(moisturePercent);
  
  delay(500);
  digitalWrite(digitalPin_Rele, LOW);
  delay(500);
  digitalWrite(digitalPin_Rele, HIGH);
}
