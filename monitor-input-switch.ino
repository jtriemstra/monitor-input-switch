const int PIN_SPLIT = 7;
const int PIN_HDMI = 4;
const int PIN_DISPLAY_PORT = 8;

/*
 *  split     {kn 1 0x020x20}{xb 1 0xc00x20}{xc 1 0x900x20}
 *  full hdmi {kn 1 0x000x20}{xb 1 0x900x20}
 *  full dp   {kn 1 0x000x20}{xb 1 0xc00x20}
 */

const int COMMAND_LENGTH = 9;
const byte COMMAND_SPLIT[] =     {0x6B,0x6E,0x20,0x30,0x31,0x20,0x30,0x31,0x0D};
const byte COMMAND_FULL[]  =     {0x6B,0x6E,0x20,0x30,0x31,0x20,0x30,0x30,0x0D};
const byte COMMAND_MAIN_DP[] =   {0x78,0x62,0x20,0x30,0x31,0x20,0x43,0x30,0x0D};
const byte COMMAND_MAIN_HDMI[] = {0x78,0x62,0x20,0x30,0x31,0x20,0x39,0x32,0x0D};
const byte COMMAND_SUB_HDMI[] =  {0x78,0x63,0x20,0x30,0x31,0x20,0x39,0x32,0x0D};

int m_intCurrentPin = -1;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(PIN_SPLIT, INPUT);
  pinMode(PIN_HDMI, INPUT);
  pinMode(PIN_DISPLAY_PORT, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(PIN_SPLIT) == HIGH && m_intCurrentPin != PIN_SPLIT) {
    doSplit();
    delay(500);
  }
  else if (digitalRead(PIN_HDMI) == HIGH && m_intCurrentPin != PIN_HDMI) {
    doFullHdmi();
    delay(500);
  }
  else if (digitalRead(PIN_DISPLAY_PORT) == HIGH && m_intCurrentPin != PIN_DISPLAY_PORT) {
    doFullDisplayPort();
    delay(500);
  }
}

void writeAndWait(byte command[])
{
  Serial.write(command,COMMAND_LENGTH);
  delay(250);
}

void doSplit()
{
  writeAndWait(COMMAND_SPLIT);
  writeAndWait(COMMAND_MAIN_DP);
  writeAndWait(COMMAND_SUB_HDMI);
}

void doFullHdmi()
{
  writeAndWait(COMMAND_FULL);
  writeAndWait(COMMAND_MAIN_HDMI);
}

void doFullDisplayPort()
{
  writeAndWait(COMMAND_FULL);
  writeAndWait(COMMAND_MAIN_DP);
}
