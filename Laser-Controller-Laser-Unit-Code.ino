//LASER Control Device (Control Unit- Attached with Laser)
// Project NLO  Thesis by Syed Razwanul Haque (Nabil)
// Code Robi Kormokar and Syed Razwanul Haque
#include <VirtualWire.h>
#include <LiquidCrystal.h>
#undef int
#undef abs
#undef double
#undef float
#undef round
LiquidCrystal lcd(7, 6, 9, 3, 1, 0);
int indicator_pin = 13;
int receiver_pin = 2;
int i = 0;
int j = 0;
int k = 0;
char msg[3];

void setup() {
  //pinMode(indicator_pin, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(5, OUTPUT);
  delay(1000);
  lcd.begin(16,2);
  lcd.print(" LASER  CONTROL ");
  lcd.setCursor(6, 1); lcd.print("UNIT");
  vw_set_rx_pin(receiver_pin);
  vw_setup(2000);
  vw_rx_start();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  digitalWrite(indicator_pin, HIGH);
  if(vw_get_message(buf, &buflen)) {
    for(j = 0; j < 3; j++) {
      msg[j] = buf[j];
    }
    if(msg[1] == '1') {
      if(msg[0] == 'L') {
        if(msg[2] == '1') {digitalWrite(A1, HIGH);
        lcd.clear(); lcd.setCursor(0,0);lcd.print("LSR ON");
        lcd.setCursor(0,1);lcd.print("Power=");
        lcd.setCursor(6,1);lcd.print(k*25);
        }
        if(msg[2] == '0') {digitalWrite(A1, LOW);
        lcd.clear(); lcd.setCursor(0,0);lcd.print("LSR OFF"); }
      }
      if(msg[0] == 'S') {
        if(msg[2] == '1') { 
          digitalWrite(A2, HIGH);
          lcd.setCursor(8,0); lcd.print("      ");
          lcd.setCursor(8,0);lcd.print("SH ON"); 
        }
        if(msg[2] == '0') {
          digitalWrite(A2, LOW);
          lcd.setCursor(8,0); lcd.print("      ");
          lcd.setCursor(8,0); lcd.print("SH OFF"); 
        }
      }
      if(msg[0] == 'P') {
        k = msg[2] - 48;
        analogWrite(5, k*25);
        lcd.setCursor(0,1); lcd.print("Power=");
        lcd.setCursor(6,1); lcd.print(k*10);
        if(k < 10) {
          lcd.setCursor(8, 1); lcd.print("% ");
        }
        if(k == 10) {
          lcd.setCursor(9, 1); lcd.print("%");
        }
      }
    }
    for(j = 0; j < 3; j++) {
      msg[j] = ' ';
    }
  }
}

