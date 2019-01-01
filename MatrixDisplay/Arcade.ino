#define GREEN_BTN 0
#define BLUE_BTN 1
#define WHITE_BTN 2

typedef struct {  
  byte digitalPin, analogPin;
  char pressed, released, state;
  int  analogValue;
} ArcadeButton;

#define POSITION_UP 0
#define POSITION_DOWN 1
#define POSITION_LEFT 2
#define POSITION_RIGHT 3

typedef struct {
  byte digitalPin;
  char pressed, released, state;
} Joystick;

ArcadeButton buttons[3] = {0};
Joystick positions[4] = {0};
char lastReportedState[8] = {0};

void setup() 
{
  Serial.begin(9600);
    
  buttons[GREEN_BTN].digitalPin = 9;
  buttons[GREEN_BTN].analogPin = 6;
  buttons[GREEN_BTN].pressed = 'G';
  buttons[GREEN_BTN].released = 'g';
  
  buttons[WHITE_BTN].digitalPin = 8;
  buttons[WHITE_BTN].analogPin = 3;
  buttons[WHITE_BTN].pressed = 'W';
  buttons[WHITE_BTN].released = 'w';
  
  buttons[BLUE_BTN].digitalPin = 2;
  buttons[BLUE_BTN].analogPin = 5;
  buttons[BLUE_BTN].pressed = 'B';
  buttons[BLUE_BTN].released = 'b';

  positions[POSITION_UP].digitalPin = 13;
  positions[POSITION_UP].pressed = 'U';
  positions[POSITION_UP].released = 'u';
  positions[POSITION_DOWN].digitalPin = 12;
  positions[POSITION_DOWN].pressed = 'D';
  positions[POSITION_DOWN].released = 'd';
  positions[POSITION_LEFT].digitalPin = 10;
  positions[POSITION_LEFT].pressed = 'L';
  positions[POSITION_LEFT].released = 'l';
  positions[POSITION_RIGHT].digitalPin = 11;
  positions[POSITION_RIGHT].pressed = 'R';
  positions[POSITION_RIGHT].released = 'r';

  for(byte i = 0; i < 3; i++)
  {
    pinMode(buttons[i].digitalPin, INPUT_PULLUP);
    pinMode(buttons[i].analogPin, OUTPUT);
  }

  for(byte i = 0; i < 4; i++)
    pinMode(positions[i].digitalPin, INPUT_PULLUP);
}

void loop() 
{
  char currentState[8] = { 0 };
  
  //Buttons
  for(byte i = 0; i < 3; i++)
  {
    char state = digitalRead(buttons[i].digitalPin) == HIGH ? buttons[i].released : buttons[i].pressed;
    if(state != buttons[i].state)
    {
      if(state == buttons[i].pressed)
        buttons[i].analogValue = 255;
      
      buttons[i].state = state;
    } else if(state == buttons[i].released && buttons[i].analogValue)
      buttons[i].analogValue = max(buttons[i].analogValue - 33, 0);

    currentState[i] = state;

    analogWrite(buttons[i].analogPin, buttons[i].analogValue);
  }

  //Joystick
  for(byte i = 0; i < 4; i++)
  {
     positions[i].state = digitalRead(positions[i].digitalPin) == HIGH ? positions[i].released : positions[i].pressed;
     currentState[i + 3] = positions[i].state;
  }

  if(memcmp(currentState, lastReportedState, sizeof(currentState)))
  {
    Serial.println(currentState);
    memcpy(lastReportedState, currentState, sizeof(currentState));
  }
  delay(30);
}
