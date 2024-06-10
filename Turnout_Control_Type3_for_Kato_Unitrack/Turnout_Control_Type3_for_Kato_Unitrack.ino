/*
  Turnout Control Type 2 for Kato Unitrack
  May. 26, 2024.
  Kazuhiko Tomomatsu

  Designed to control 9 turnouts with Arduino Nano.

  Pin 0, 1 are used for Rx and Tx. 
  Pin 2 is used to input 5V regulated DCC signal.
  Pin 3 are reserved for the interrupt feature for future use.
  Pin 4 and 5 are for the control out TA8219P.
  Pin 13 is connected to a built in LED. Not use for output in this sketch.
  Pin 18 and 19 are for LCD display via I2C. (Not used in this version.)
  
  DCC address is configured in accessory[i].address.
  Turnout ID associated to the DCC address is configured in accessory[i].turnout_n.
  DCC state given by DCC signal is stored in accessory[i].dccstate.

  Outpin1 and Outpin2 are connected to Pin 5 and 6 of TA8219P respectively and control 12V outputs from TA8219P.
  
  The state of the turnout (Closed or Thrown) is set in turnout[i].cur_state.

 */

#define NUMACCESSORIES 11 // Enter the number of accessories here
#define NUMTURNOUT 11 // Enter the number of turnput here
#define THROWN 1
#define CLOSED 0

// GO TO setup() TO CONFIGURE DCC ADDRESSES AND PIN NUMBERS

#include <DCC_Decoder.h>

typedef struct DCCAccessoryData {
  int  address;   // User Configurable DCC address
  int  accessory_n; // Refer the accessory nummber that associates to turnout.
  boolean  dccstate;  // Internal use DCC state of accessory, 1=on, 0=off
  boolean  accessorystate; // Current Accesory State
};
DCCAccessoryData accessory[] = {
                      {101, 0, 0, 0},
                      {102, 1, 0, 0},
                      {103, 2, 0, 0},
                      {104, 3, 0, 0},
                      {105, 4, 0, 0},
                      {106, 5, 0, 0},
                      {107, 6, 0, 0},
                      {108, 7, 0, 0},
                      {109, 8, 0, 0},
                      {110, 9, 0, 0},
                      {111, 10, 0, 0}
                      };
// Pin 13 is directly connected to the build in LED

typedef struct {
  int out_pin;
  int cur_state;
} TurnoutData;

int outpin_12v1 = 4;
int outpin_12v2 = 5;

TurnoutData turnout[] = {
  {6,0},
  {7,0},
  {8,0},
  {9,0},
  {10,0},
  {11,0},
  {12,0},
  {14,0},
  {15,0},
  {16,0},
  {17,0}
};
// Pin 0, 1 are used for Rx and Tx. Pin 2 and 3 are reserved for the interrupt feature for future use.

String state[2] = {"Closed", "Thrown"};

void setup() { 
  Serial.begin(19200);
  Serial.println("");
  Serial.println("Turnout Control Type 3 for Kato Unitrack");
  Serial.println("Turnout_Control_Type3_for_Kato_Unitrack.ino");
  Serial.println("2024/06/10 Kazuhiko Tomomatsu");
  Serial.println("");

  for(int i=0; i<NUMACCESSORIES; i++) {
    Serial.print("Address: ");
    Serial.print(accessory[i].address);
    Serial.print(" DCC State: ");
    Serial.print(accessory[i].dccstate);
    Serial.print(" Accesary State: ");
    Serial.print(accessory[i].accessorystate);
    Serial.print(" Turnout Number: ");
    Serial.println(accessory[i].accessory_n);
  }

  // Outpin 4 and 5 are TA8219P output 12V control
  pinMode(outpin_12v1, OUTPUT);
  pinMode(outpin_12v2, OUTPUT);
  digitalWrite(outpin_12v1, LOW);
  digitalWrite(outpin_12v2, LOW);

  for(int i=0; i<NUMTURNOUT; i++) {
    pinMode(turnout[i].out_pin, OUTPUT);
  }

for(int i=0; i<NUMTURNOUT; i++) {
  turnout_closed(i);
//  Serial.print("Turnout State: ");
//  Serial.println(state[turnout[i].cur_state]);
  delay(1000);
  turnout[i].cur_state=turnout_thrown(i);
//  Serial.print("Turnout State: ");
//  Serial.println(state[turnout[i].cur_state]);
  delay(1000);
  turnout[i].cur_state=turnout_closed(i);
//  Serial.print("Turnout State: ");
//  Serial.println(state[turnout[i].cur_state]);
  }

  Serial.println("Turnput Initialization Completed");
  Serial.println("");

  DCC.SetBasicAccessoryDecoderPacketHandler(BasicAccDecoderPacket_Handler, true);
  DCC.SetupDecoder( 0x00, 0x00, 0 );

}

void loop() {
  static int n = 0;
  
  DCC.loop(); // Call the DCC library to read incoming DCC data
  if( ++n >= NUMACCESSORIES ) n = 0; // Next address to test
  if (accessory[n].dccstate!=accessory[n].accessorystate) {
    Serial.print("Current Accessory State ");
    Serial.println(accessory[n].accessorystate); 
    if (accessory[n].dccstate){
      Serial.print("Entering turnout_thrown Turnout ");
      Serial.println(accessory[n].accessory_n);

      turnout[accessory[n].accessory_n].cur_state=turnout_thrown(accessory[n].accessory_n);
      accessory[n].accessorystate = 1;
    }
  else {
      Serial.print("Entering turnout_closed Turnout ");
      Serial.println(accessory[n].accessory_n);

      turnout[accessory[n].accessory_n].cur_state=turnout_closed(accessory[n].accessory_n);
      accessory[n].accessorystate = 0;
    }
    Serial.print("New Accessory State ");
    Serial.println(accessory[n].accessorystate);
    Serial.print("Turnout State ");
    Serial.println(state[turnout[accessory[n].accessory_n].cur_state]);
    Serial.println("");
    delay (1000);
  }
}

// The DCC library calls this function to set / reset accessories
void BasicAccDecoderPacket_Handler(int address, boolean activate, byte data) {
  address -= 1;
  address *= 4;
  address += 1;
  address += (data & 0x06) >> 1;
  // Added in DCC_Decoder
  // End of Added in DCC_Decoder
  // address = address - 4; // uncomment this line for Roco Maus or z21
  boolean enable = (data & 0x01) ? 1 : 0;
  for (int i=0; i<NUMACCESSORIES; i++) {
    if (address == accessory[i].address) {
        Serial.print("Address ");
        Serial.print(address);
        Serial.print(" DCC Data Byte ");
        Serial.println(data);
        Serial.print("Current DCC State ");
        Serial.print(accessory[i].dccstate);
      if (enable) {
        accessory[i].dccstate = 1;
      }
      else {
        accessory[i].dccstate = 0;
      }
    Serial.print(" New DCC State ");
    Serial.println(accessory[i].dccstate);
    }
  }
}

int turnout_thrown(int t){
  digitalWrite(turnout[t].out_pin, LOW); // close Relay t
  delay(500);                        // wait for 500 ms
  digitalWrite(outpin_12v1, HIGH);   // Output 12V from TA8219P pin 1
  delay(100);  // Generate 12V output from TA8219P for 100 ms
  digitalWrite(outpin_12v1, LOW); // Bring output 1 of TA8219P back to 0V.
  delay(500);                   // wait for 500 ms
  digitalWrite(turnout[t].out_pin, HIGH); // close Relay t
  Serial.print("Turnout ");
  Serial.print(t);
  Serial.println(" Thrown");
  return THROWN;
}

int turnout_closed(int t){
  digitalWrite(turnout[t].out_pin, LOW); // close Relay t
  delay(500);                        // wait for 500 ms
  digitalWrite(outpin_12v2, HIGH);   // Output 12V from TA8219P pin 10
  delay(100);  // Generate 12V output from TA8219P for 100 ms
  digitalWrite(outpin_12v2, LOW); // Bring output 1 of TA8219P back to 0V.
  delay(500);                   // wait for 500 ms
  digitalWrite(turnout[t].out_pin, HIGH); // close Relay t
  Serial.print("Turnout ");
  Serial.print(t);
  Serial.println(" Closed");
  return CLOSED;
}



