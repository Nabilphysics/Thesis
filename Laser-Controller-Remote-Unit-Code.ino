
//Laser Controller , Remote Unit
//LASER OFF BLINKING, ARROW SIGN, LOCK SIGN
// Syed Razwanul Haque & Robi Kormokar
// https://www.nabilbd.com
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <VirtualWire.h>
#undef int
#undef abs
#undef double
#undef float
#undef round
LiquidCrystal lcd(6, 5, 4, 3, 1, 0);
int up = 0;
int down = 0;
int right = 0;
int left = 0;
int ok = 0;

const char *menu_string = "";
const char *space_string = "                ";

int password[4];
int blnk = 0;  //blink off

int button = 0; int i = 0;
int s1 = 0; int p1 = 0;
int s2 = 0; int p2 = 0;
int s3 = 0; int p3 = 0;
int l1 = 0; //for laser on
int l2 = 0;
int l3 = 0;

int string_no = 0;
int x = 0;
int permanent_lock = 0;

int pass_state = EEPROM.read(5);
int default_state = EEPROM.read(6);

const int transmit_pin = 9;
byte space[8] = {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111};

void setup() {
  lcd.createChar(2, space);
  lcd.begin(16, 2);
  lcd.print("Remote ON");
  delay(1000);
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);
  while(x < 1) {
    if(pass_state == 0) x = 1;
    if(pass_state == 1) {
      permanent_lock = permanent_lock + 1;
      if(permanent_lock < 4)
      ACCESS_CODE(1);
      if(permanent_lock == 4) {
        permanent_lock = 3;
        lcd.clear();
        lcd.print(" ACCESS DENIED");
        delay(1000);
      }
    }
  }
}

void loop() {
  blnk = 0;  //blink off
  button = 0;
  lcd.clear();
  delay(500);
  lcd.setCursor(4, 0); lcd.print("PRESS OK");
  lcd.setCursor(4, 1); lcd.print("FOR MENU");
  delay(1000);
  Button();
  if(button == 5) {
    SYSTEM();
  }
}


void SYSTEM() {

  int j = 0;
  int k = 0;
  lcd.clear();
  while(j < 1) {
    blnk = 1;  //blink on
    if(k == 0) {
      menu_string = "LASER CONTROL";
      lcd.setCursor(0, 1); lcd.print("SETTINGS");
    }
    if(k == 1) {
      menu_string = "SETTINGS";
      lcd.setCursor(0, 1); lcd.print("BACK");
    }
    if(k == 2) {
      menu_string = "BACK";
    }
    Button();
    if(button == 1) {  //down button
      lcd.clear();
      k = k + 1;
      if(k > 2) {
        k = 2;
      }
    }
    if(button == 2) { // up button
      lcd.clear();
      k = k - 1;
      if(k < 0) {
        k = 0;
      }
    }
    if(button == 5) {
      if(k == 0) 
        LASER_CONTROL();
      if(k == 1)
        SETTINGS();
      if(k == 2)
        j = 1;
    }
  }  //while end
}  //SYSTEM() end

int Button() {
  i = 0;
  //delay(100);           //Could Change
  while(i < 1) {
    if(blnk == 1) {
      lcd.setCursor(0, 0); lcd.print(menu_string);
      delay(150);
      lcd.setCursor(0, 0); lcd.print(space_string);
      delay(150);
    }
    else if(blnk == 2) {
      lcd.setCursor(3, 1); lcd.print(menu_string);
      delay(150);
      lcd.setCursor(3, 1); lcd.print("   ");
      delay(150);
    }
    else if(blnk == 3) {
      lcd.setCursor(11, 1); lcd.print(menu_string);
      delay(150);
      lcd.setCursor(11, 1); lcd.print("  ");
      delay(150);
    }
    else if(blnk == 4) {
      lcd.setCursor(0, 1); lcd.print(menu_string);
      delay(150);
      lcd.setCursor(0, 1); lcd.print("         ");
      delay(150);
    }
    else if(blnk == 5) {
      lcd.setCursor(12, 1); lcd.print(menu_string);
      delay(150);
      lcd.setCursor(12, 1); lcd.print("    ");
      delay(150);
    }
    else delay(50);
    left = analogRead(A1);
    ok = analogRead(A5);
    up = analogRead(A4);
    down = analogRead(A2);
    right = analogRead(A3);
    
    if(up > 500) {
      button = 1;
      up = 0;
      i = 1;
    }
    if(down > 500) {
      button = 2;
      down = 0;
      i = 1;
    }
    if(left > 500) {
      button = 3;
      left = 0;
      i = 1;
    }
    if(right > 500) {
      button = 4;
      right = 0;
      i = 1;
    }
    if(ok > 500) {
      button = 5;
      ok = 0;
      i = 1;
    }
  }
  return (button);
}

void LASER_CONTROL() {
  lcd.clear();
  int m;
  if(default_state == 1) 
    m = EEPROM.read(0);
  if(default_state == 0)
    m = 0;
  int l = 0;
  while(l < 1) {
    blnk = 1; //blink on
    if(m == 0 && default_state == 0) {
      menu_string = "LASER ONE";
      lcd.setCursor(0, 1); lcd.print("LASER TWO");
    }
    if(m == 1 && default_state == 0) {
      menu_string = "LASER TWO";
      lcd.setCursor(0, 1); lcd.print("LASER THREE");
    }
    if(m == 2 && default_state == 0) {
      menu_string = "LASER THREE";
      lcd.setCursor(0, 1); lcd.print("BACK");
    }
    if(m == 3 && default_state == 0) {
      menu_string = "BACK";
    }
    if(default_state == 0)
      Button();
    if(button == 1) {  //down button
      lcd.clear();
      m = m + 1;
      if(m > 3) {
        m = 3;
      }
    }
    if(button == 2) { // up button
      lcd.clear();
      m = m - 1;
      if(m < 0) {
        m = 0;
      }
    }
    if(button == 5 || default_state == 1) {
      if(m == 0)
        LASER_ONE();
      if(m == 1)
        LASER_TWO();
      if(m == 2)
        LASER_THREE();
      if(m == 3 || default_state == 1)
        l = 1;
    }
  }
}

void LASER_ONE() {
  if(l1 == 0) {
    string_no = 12;
    RF_Send(string_no);
    l1 = 1;
  }
  int a = 0; int b = 0;
  lcd.clear();
  while(a < 1) {
    //blnk = 0;
    if(b == 0) {
      blnk = 0;
      lcd.setCursor(0, 0); lcd.print("[SH-");
      if(s1 == 0) {
        lcd.setCursor(4, 0); lcd.print("OFF]");
      }
      if(s1 == 1) {
        lcd.setCursor(5, 0); lcd.print("ON]");
      }
      lcd.setCursor(9, 0); lcd.print("POW-");
      lcd.setCursor(13, 0); lcd.print(p1);
      lcd.setCursor(0, 1); lcd.print("LAS_1_OFF |");
      lcd.setCursor(12, 1); lcd.print("LOCK");
      delay(400);
    }
    if(b == 1) {
      blnk = 4;
      lcd.setCursor(0, 0); lcd.print("SH-");
      if(s1 == 0) {
        lcd.setCursor(3, 0); lcd.print("OFF |");
      }
      if(s1 == 1) {
        lcd.setCursor(4, 0); lcd.print("ON |");
      }
      lcd.setCursor(9, 0); lcd.print("POW-");
      lcd.setCursor(13, 0); lcd.print(p1);
      menu_string = "LAS_1_OFF";
      lcd.setCursor(10, 1); lcd.print("| LOCK");
    }
    if(b == 2) {
      blnk = 5;
      lcd.setCursor(0, 0); lcd.print("SH-");
      if(s1 == 0) {
        lcd.setCursor(3, 0); lcd.print("OFF |");
      }
      if(s1 == 1) {
        lcd.setCursor(4, 0); lcd.print("ON |");
      }
      lcd.setCursor(9, 0); lcd.print("POW-");
      lcd.setCursor(13, 0); lcd.print(p1);
      lcd.setCursor(0, 1); lcd.print("LAS_1_OFF |");
      menu_string = "LOCK";
    }
    if(b == 3) {
      blnk = 4;
      lcd.setCursor(0, 0); lcd.print("LAS_1 OFF |");
      lcd.setCursor(12, 0); lcd.print("LOCK");
      menu_string = "BACK";
    }
    delay(100);
    Button();
    if(button == 1) {
      lcd.clear();
      b = b + 1;
      if(b > 3) b = 3;
    }
    if(button == 2) {
      lcd.clear();
      b = b - 1;
      if(b < 0) b = 0;
    }
    if(button == 4) {
      lcd.clear();
      //send RF data for power change
      p1 = p1 + 10;
      if(p1 > 100) p1 = 100;
      string_no = 40 + (p1/10);
      RF_Send(string_no);
    }
    if(button == 3) {
      lcd.clear();
      //send RF data for power change
      p1 = p1 - 10;
      if(p1 < 0) p1 = 0;
      string_no = 40 + (p1/10);
      RF_Send(string_no);
    }
    if(button == 5) {
      lcd.clear();
      if(b == 0) {
        //send RF code for sutter toggle
        s1 = ! s1;
        if(s1 == 0) 
          string_no = 10;
        if(s1 == 1)
          string_no = 11;
        RF_Send(string_no);
      }
      if(b == 1) {
        int k1 = sure();
        //send RF code for LASER OFF
        if(k1 == 0) {
          if(p1 == 0) { 
            string_no = 13;
            RF_Send(string_no);
            l1 = 0;
            a = 1;
            lcd.print("   LASER  OFF");
            delay(800);
          }
          else {
            lcd.print(" POWER MUST BE"); 
            lcd.setCursor(4, 1); lcd.print("!!ZERO!!");
            delay(1000);
            lcd.clear();
          }
        }
      }
      if(b == 2) {
        //for lock
        blnk = 0;
        delay(500);
        lcd.clear(); lcd.setCursor(0, 0); lcd.print("LASER 1  RUNNING");
        lcd.setCursor(3, 1); lcd.print("!!LOCKED!!");
        x = 0;
        while(x < 1) {
          Button();
          if(button == 5) { 
            ACCESS_CODE(1);
            if(x == 0) {
              lcd.clear(); lcd.setCursor(0, 0); lcd.print("LASER 1 RUNNING");
              lcd.setCursor(3, 1); lcd.print("!!LOCKED!!");
            }
          } 
        }
        string_no = 14;
        RF_Send(string_no);
        lcd.clear(); 
      }
      if(b == 3) {
        a = 1; //break while loop
      }
    }
  }//while end
}  //function end

void LASER_TWO() {
  if(l2 == 0){
    string_no = 22;
    RF_Send(string_no);
    l2 = 1;
  }
  int c = 0; int d = 0;
  lcd.clear();
  while(c < 1) {
    //blnk = 0;
    if(d == 0) {
      blnk = 0;
      lcd.setCursor(0, 0); lcd.print("[SH-");
      if(s2 == 0) {
        lcd.setCursor(4, 0); lcd.print("OFF]");
      }
      if(s2 == 1) {
        lcd.setCursor(5, 0); lcd.print("ON]");
      }
      lcd.setCursor(9, 0); lcd.print("POW-");
      lcd.setCursor(13, 0); lcd.print(p2);
      lcd.setCursor(0, 1); lcd.print("LAS_2_OFF |");
      lcd.setCursor(12, 1); lcd.print("LOCK");
      delay(400);
    }
    if(d == 1) {
      blnk = 4; 
      lcd.setCursor(0, 0); lcd.print("SH-");
      if(s2 == 0) {
        lcd.setCursor(3, 0); lcd.print("OFF |");
      }
      if(s2 == 1) {
        lcd.setCursor(4, 0); lcd.print("ON |");
      }
      lcd.setCursor(9, 0); lcd.print("POW-");
      lcd.setCursor(13, 0); lcd.print(p2);
      menu_string = "LAS_2_OFF";
      lcd.setCursor(10, 1); lcd.print("| LOCK");
    }
    if(d == 2) {
      blnk = 5;
      lcd.setCursor(0, 0); lcd.print("SH-");
      if(s2 == 0) {
        lcd.setCursor(3, 0); lcd.print("OFF |");
      }
      if(s2 == 1) {
        lcd.setCursor(4, 0); lcd.print("ON |");
      }
      lcd.setCursor(9, 0); lcd.print("POW-");
      lcd.setCursor(13, 0); lcd.print(p2);
      lcd.setCursor(0, 1); lcd.print("LAS_2 OFF |");
      menu_string = "LOCK";
    }
    if(d == 3) {
      blnk = 4;
      lcd.setCursor(0, 0); lcd.print("LAS_2 OFF |");
      lcd.setCursor(12, 0); lcd.print("LOCK");
      menu_string = "BACK";
    }
    delay(100);
    Button();
    if(button == 1) {
      lcd.clear();
      d = d + 1;
      if(d > 3) d = 3;
    }
    if(button == 2) {
      lcd.clear();
      d = d - 1;
      if(d < 0) d = 0;
    }
    if(button == 4) {
      lcd.clear();
      //send RF data for power change
      p2 = p2 + 10;
      if(p2 > 100) p2 = 100;
      string_no = 60 + (p2/10);
      RF_Send(string_no);
    }
    if(button == 3) {
      lcd.clear();
      //send RF data for power change
      p2 = p2 - 10;
      if(p2 < 0) p2 = 0;
      string_no = 60 + (p2/10);
      RF_Send(string_no);
    }
    if(button == 5) {
      lcd.clear();
      if(d == 0) {
        //send RF code for sutter toggle
        s2 = ! s2;
        if(s2 == 0)
          string_no = 20;
        if(s2 == 1)
          string_no = 21;
        RF_Send(string_no);
      }
      if(d == 1) {
        //send RF code for LASER OFF
        int k2 = sure();
        if(k2 == 0) {
          if(p2 == 0) { 
            string_no = 23;
            RF_Send(string_no);
            l2 = 0;
            c = 1;
            lcd.print("   LASER  OFF");
            delay(800);
          }
          else {
            lcd.print(" POWER MUST BE"); 
            lcd.setCursor(4, 1); lcd.print("!!ZERO!!");
            delay(1000);
            lcd.clear();
          }
        }
      }
      if(d == 2) {
        //for lock
        blnk = 0;
        delay(500);
        lcd.clear(); lcd.setCursor(0, 0); lcd.print("LASER 2  RUNNING");
        lcd.setCursor(3, 1); lcd.print("!!LOCKED!!");
        x = 0;
        while(x < 1) {
          Button();
          if(button == 5) { 
            ACCESS_CODE(1);
            if(x == 0) {
              lcd.clear(); lcd.setCursor(1, 0); lcd.print("LASER 2  RUNNING");
              lcd.setCursor(3, 1); lcd.print("!!LOCKED!!");
            }
          } 
        }
        string_no = 24;
        RF_Send(string_no);
        lcd.clear();
      }
      if(d == 3) {
        c = 1; //break while loop
      }
    }
  }//while end
}
void LASER_THREE() {
  if(l3 == 0) {
    string_no = 32;
    RF_Send(string_no);
    l3 = 1;
  }
  int e = 0; int f = 0;
  lcd.clear();
  while(e < 1) {
    //blnk = 0;
    if(f == 0) {
      blnk = 0;
      lcd.setCursor(0, 0); lcd.print("[SH-");
      if(s3 == 0) {
        lcd.setCursor(4, 0); lcd.print("OFF]");
      }
      if(s3 == 1) {
        lcd.setCursor(5, 0); lcd.print("ON]");
      }
      lcd.setCursor(9, 0); lcd.print("POW-");
      lcd.setCursor(13, 0); lcd.print(p3);
      lcd.setCursor(0, 1); lcd.print("LAS_3_OFF |");
      lcd.setCursor(12, 1); lcd.print("LOCK");
      delay(400);
    }
    if(f == 1) {
      blnk = 4;
      lcd.setCursor(0, 0); lcd.print("SH-");
      if(s3 == 0) {
        lcd.setCursor(3, 0); lcd.print("OFF |");
      }
      if(s3 == 1) {
        lcd.setCursor(4, 0); lcd.print("ON |");
      }
      lcd.setCursor(9, 0); lcd.print("POW-");
      lcd.setCursor(13, 0); lcd.print(p3);
      menu_string = "LAS_3_OFF";
      lcd.setCursor(10, 1); lcd.print("| LOCK");
    }
    if(f == 2) {
      blnk = 5;
      lcd.setCursor(0, 0); lcd.print("SH-");
      if(s3 == 0) {
        lcd.setCursor(3, 0); lcd.print("OFF |");
      }
      if(s3 == 1) {
        lcd.setCursor(4, 0); lcd.print("ON |");
      }
      lcd.setCursor(9, 0); lcd.print("POW-");
      lcd.setCursor(13, 0); lcd.print(p3);
      lcd.setCursor(0, 1); lcd.print("LAS_3_OFF |");
      menu_string = "LOCK";
    }
    if(f == 3) {
      blnk = 4;
      lcd.setCursor(0, 0); lcd.print("LAS_3_OFF |");
      lcd.setCursor(12, 0); lcd.print("LOCK");
      menu_string = "BACK";
    }
    delay(100);
    Button();
    if(button == 1) {
      lcd.clear();
      f = f + 1;
      if(f > 3) f = 3;
    }
    if(button == 2) {
      lcd.clear();
      f = f - 1;
      if(f < 0) f = 0;
    }
    if(button == 4) {
      lcd.clear();
      //send RF data for power change
      p3 = p3 + 10;
      if(p3 > 100) p3 = 100;
      string_no = 80 + (p3/10);
      RF_Send(string_no);
    }
    if(button == 3) {
      lcd.clear();
      //send RF data for power change
      p3 = p3 - 10;
      if(p3 < 0) p3 = 0;
      string_no = 80 + (p3/10);
      RF_Send(string_no);
    }
    if(button == 5) {
      lcd.clear();
      if(f == 0) {
        //send RF code for sutter toggle
        s3 = ! s3;
        if(s3 == 0)
          string_no = 30;
        if(s3 == 1)
          string_no = 31;
        RF_Send(string_no);
      }
      if(f == 1) {
        //send RF code for LASER OFF
        int k3 = sure();
        if(k3 == 0) {
          if(p3 == 0) { 
            string_no = 33;
            RF_Send(string_no);
            l3 = 0;
            e = 1;
            lcd.print("   LASER  OFF");
            delay(800);
          }
          else {
            lcd.print(" POWER MUST BE"); 
            lcd.setCursor(4, 1); lcd.print("!!ZERO!!");
            delay(1000);
            lcd.clear();
          }
        }
      }
      if(f == 2) {
        //for lock
        blnk = 0;
        delay(500);
        lcd.clear(); lcd.setCursor(0, 0); lcd.print("LASER 3  RUNNING");
        lcd.setCursor(3, 1); lcd.print("!!LOCKED!!");
        x = 0;
        while(x < 1) {
          Button();
          if(button == 5) { 
            ACCESS_CODE(1);
            if(x == 0) {
              lcd.clear(); lcd.setCursor(0, 0); lcd.print("LASER 3  RUNNING");
              lcd.setCursor(3, 1); lcd.print("!!LOCKED!!");
            }
          } 
        }
        string_no = 34;
        RF_Send(string_no);
        lcd.clear();
      }
      if(f == 3) {
        e = 1; //break while loop
      }
    }
  }//while end
}

void RF_Send(int s) {
  const char *msg = " ";
  if(s == 10) msg = "S10";
  if(s == 11) msg = "S11";
  if(s == 12) msg = "L11";
  if(s == 13) msg = "L10";
  if(s == 14) msg = "K10";  //for remote 2, msg = K11 and for remote 3, msg = K12 
  if(s == 40) msg = "P10";
  if(s == 41) msg = "P11";
  if(s == 42) msg = "P12";
  if(s == 43) msg = "P13";
  if(s == 44) msg = "P14";
  if(s == 45) msg = "P15";
  if(s == 46) msg = "P16";
  if(s == 47) msg = "P17";
  if(s == 48) msg = "P18";
  if(s == 49) msg = "P19";
  if(s == 50) msg = "P1:";
    
  if(s == 20) msg = "S20";
  if(s == 21) msg = "S21";
  if(s == 22) msg = "L21";
  if(s == 23) msg = "L20";
  if(s == 24) msg = "K20";
  if(s == 60) msg = "P20";
  if(s == 61) msg = "P21";
  if(s == 62) msg = "P22";
  if(s == 63) msg = "P23";
  if(s == 64) msg = "P24";
  if(s == 65) msg = "P25";
  if(s == 66) msg = "P26";
  if(s == 67) msg = "P27";
  if(s == 68) msg = "P28";
  if(s == 69) msg = "P29";
  if(s == 70) msg = "P2:";
    
  if(s == 30) msg = "S30";
  if(s == 31) msg = "S31";
  if(s == 32) msg = "L31";
  if(s == 33) msg = "L30";
  if(s == 34) msg = "K34";
  if(s == 80) msg = "P30";
  if(s == 81) msg = "P31";
  if(s == 82) msg = "P32";
  if(s == 83) msg = "P33";
  if(s == 84) msg = "P34";
  if(s == 85) msg = "P35";
  if(s == 86) msg = "P36";
  if(s == 87) msg = "P37";
  if(s == 88) msg = "P38";
  if(s == 89) msg = "P39";
  if(s == 90) msg = "P3:";
  
  //more if conditions will be added
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
}

void SETTINGS(){
  int g = 0; int h = 0;
  lcd.clear();
  while(g < 1) {
    blnk = 1; //blink on
    if(h == 0) {
      menu_string = "PASSWORD OPTION";
      lcd.setCursor(0, 1); lcd.print("DEFAULT LASER");
    }
    if(h == 1) {
      menu_string = "DEFAULT LASER";
      lcd.setCursor(0, 1); lcd.print("BACK");
    }
    if(h == 2) {
      menu_string = "BACK";
    }
    Button();
    if(button == 1) {
      lcd.clear();
      h = h + 1;
      if(h > 2) h = 2;
    }
    if(button == 2) {
      lcd.clear();
      h = h - 1;
      if(h < 0) h = 0;
    }
    if(button == 5) {
      if(h == 0)
        PASSWORD_OPTION();
      if(h == 1)
        DEFAULT_COMMUNICATION();
      if(h == 2)
        g = 1; //break while loop
    }
  } //end while loop
}  //end SETTINGS

void PASSWORD_OPTION() {
  int p = 0; int q = 0;
  lcd.clear();
  while(p < 1) {
    blnk = 1;
    if(q == 0) {
      menu_string = "CHANGE PASSWORD";
      if(pass_state == 0) {
        lcd.setCursor(0, 1); lcd.print("ENABLE PASSWORD");
      }
      if(pass_state == 1) {
        lcd.setCursor(0, 1); lcd.print("DISABLE PASSWORD");
      }
    }
    if(q == 1) {
      if(pass_state == 0)
        menu_string = "ENABLE PASSWORD";
      if(pass_state == 1)
        menu_string = "DISABLE PASSWORD";
      lcd.setCursor(0, 1); lcd.print("BACK");
    }
    if(q == 2) {
      menu_string = "BACK";
    }
    Button();
    if(button == 1) {
      lcd.clear();
      q = q + 1;
      if(q > 2) q = 2;
    }
    if(button == 2) {
      lcd.clear();
      q = q - 1;
      if(q < 0) q = 0;
    }
    if(button == 5) {
      if(q == 0) {
        CHANGE_PASSWORD();
      }
      if(q == 1) {
        pass_state = ! pass_state;
        EEPROM.write(5, pass_state);
      }
      if(q == 2) {
        p = 1;  //break while
      }
    }
  }  // end while
}  //end PASSWORD OPTION

void CHANGE_PASSWORD() {
  ACCESS_CODE(2);
   if(x == 1) {
     char new_password[4]; char verify_password[4];
     int e1 = 0; int f1 = 0; int g1 = 0;
     lcd.clear(); 
     while(e1 < 1) {
       blnk = 0;
       if(g1 == 0) {
         lcd.setCursor(0, 0); lcd.print("NEW PASSWORD");
         lcd.setCursor(0, 1);
         lcd.print(f1); lcd.write(2); lcd.write(2); lcd.write(2);
       }
       if(g1 == 1) {
         lcd.setCursor(0, 0); lcd.print("NEW PASSWORD");
         lcd.setCursor(0, 1);
         lcd.print("*"); lcd.print(f1); lcd.write(2); lcd.write(2);
       }
       if(g1 == 2) {
         lcd.setCursor(0, 0); lcd.print("NEW PASSWORD");
         lcd.setCursor(0, 1);
         lcd.print("*"); lcd.print("*"); lcd.print(f1); lcd.write(2);
       }
       if(g1 == 3) {
         lcd.setCursor(0, 0); lcd.print("NEW PASSWORD");
         lcd.setCursor(0, 1);
         lcd.print("*"); lcd.print("*"); lcd.print("*"); lcd.print(f1);
       }
       delay(400);
       Button();
       if(button == 2) {
         lcd.clear();
         f1 = f1 + 1;
         if(f1 > 9) f1 = 9;
       }
       if(button == 1) {
         lcd.clear();
         f1 = f1 - 1;
         if(f1 < 0) f1 = 0;
       }
       if(button == 3) {
         f1 = 0;
         lcd.clear();
         g1 = g1 - 1;
         if(g1 < 0) g1 = 0;
         new_password[g1] = f1; 
       }
       if(button == 4 && g1 != 3) {
         new_password[g1] = f1;
         lcd.clear();
         g1 = g1 + 1;
         f1 = 0;
       }
       if(button == 5 && g1 == 3) {
         new_password[g1] = f1;
         e1 = 1;
         lcd.clear();
       }
     }
     e1 = 0; 
     f1 = 0; 
     g1 = 0;
     while(e1 < 1) {
       blnk = 0;
       if(g1 == 0) {
         lcd.setCursor(0, 0); lcd.print("VERIFY PASSWORD");
         lcd.setCursor(0, 1);
         lcd.print(f1); lcd.write(2); lcd.write(2); lcd.write(2);
       }
       if(g1 == 1) {
         lcd.setCursor(0, 0); lcd.print("VERIFY PASSWORD");
         lcd.setCursor(0, 1);
         lcd.print("*"); lcd.print(f1); lcd.write(2); lcd.write(2);
       }
       if(g1 == 2) {
         lcd.setCursor(0, 0); lcd.print("VERIFY PASSWORD");
         lcd.setCursor(0, 1);
         lcd.print("*"); lcd.print("*"); lcd.print(f1); lcd.write(2);
       }
       if(g1 == 3) {
         lcd.setCursor(0, 0); lcd.print("VERIFY PASSWORD");
         lcd.setCursor(0, 1);
         lcd.print("*"); lcd.print("*"); lcd.print("*"); lcd.print(f1);
       }
       delay(400);
       Button();
       if(button == 2) {
         lcd.clear();
         f1 = f1 + 1;
         if(f1 > 9) f1 = 9;
       }
       if(button == 1) {
         lcd.clear();
         f1 = f1 - 1;
         if(f1 < 0) f1 = 0;
       }
       if(button == 3) {
         f1 = 0;
         lcd.clear();
         g1 = g1 - 1;
         if(g1 < 0) g1 = 0;
         verify_password[g1] = f1; 
       }
       if(button == 4 && g1 != 3) {
         verify_password[g1] = f1;
         lcd.clear();
         g1 = g1 + 1;
         f1 = 0;
       }
       if(button == 5 && g1 == 3) {
         verify_password[g1] = f1;
         e1 = 1;
         lcd.clear();
       }
     }
      for(int h1 = 0; h1 < 4; h1++) {
        if(new_password[h1] == verify_password[h1]) {
           if(h1 == 3) {
             delay(100);
             for(h1 = 0; h1 < 4; h1++) {
               EEPROM.write((h1 + 1), new_password[h1]);
               lcd.clear(); lcd.print("PASSWORD CHANGED");
               delay(1000);
             }
             h1 = 3;
           }
        }
        if(new_password[h1] != verify_password[h1]) {
          lcd.clear(); lcd.setCursor(5, 0); lcd.print("FAILED");
          h1 = 4; //end for loop
          delay(1000);
        }
      }
   }
}

void DEFAULT_COMMUNICATION() {
  int r = 0; int t = 0;
  lcd.clear();
  while(r < 1) {
    blnk = 1;
    if(t == 0) {
      if(default_state == 0) menu_string = "ACTIVATE";
      if(default_state == 1) menu_string = "DEACTIVATE";
      lcd.setCursor(0, 1); lcd.print("BACK");
    }
    if(t == 1) {
      menu_string = "BACK";
    }
    Button();
    if(button == 1) {
      lcd.clear();
      t = t + 1;
      if(t > 1) t = 1;
    }
    if(button == 2) {
      lcd.clear();
      t = t - 1;
      if(t < 0) t = 0;
    }
    if(button == 5) {
      if(t == 0) {
        default_state = ! default_state;
        EEPROM.write(6, default_state);
        if(default_state == 1) 
          ACTIVATE();
      }
      if(t == 1) 
        r = 1;
    }
  } //end while        
}  //end DEFAULT_COMMUNICATION

void ACTIVATE() {  //no back option
  int u = 0; int v = 0;
  lcd.clear();
  while(u < 1) {
    blnk = 1;
    if(v == 0) {
      menu_string = "LASER ONE";
      lcd.setCursor(0, 1); lcd.print("LASER TWO");
    }
    if(v == 1) {
      menu_string = "LASER TWO";
      lcd.setCursor(0, 1); lcd.print("LASER THREE");
    }
    if(v == 2) {
      menu_string = "LASER THREE";
    }
    Button();
    if(button == 1) {
      lcd.clear();
      v = v + 1;
      if(v > 2) v = 2;
    }
    if(button == 2) {
      lcd.clear();
      v = v - 1;
      if(v < 0) v = 0;
    }
    if(button == 5) {
      lcd.clear();
      EEPROM.write(0, v);
      u = 1;
    }
  } // end while
}  //end ACTIATE()

void ACCESS_CODE(int d1) {
  int a1 = 0; int b1 = 0; int c1 = 0;
  lcd.clear(); blnk = 0;
  while(a1 < 1) {
    if(c1 == 0) {
      lcd.setCursor(0, 0); if(d1 == 1) lcd.print("ENTER PASSWORD"); if(d1 == 2) lcd.print("CURRENT PASSWORD");
      lcd.setCursor(0, 1);
      lcd.print(b1); lcd.write(2); lcd.write(2); lcd.write(2);
    }
    if(c1 == 1) {
      lcd.setCursor(0, 0); if(d1 == 1) lcd.print("ENTER PASSWORD"); if(d1 == 2) lcd.print("CURRENT PASSWORD");
      lcd.setCursor(0, 1);
      lcd.print("*"); lcd.print(b1); lcd.write(2); lcd.write(2);
    }
    if(c1 == 2) {
      lcd.setCursor(0, 0); if(d1 == 1) lcd.print("ENTER PASSWORD"); if(d1 == 2) lcd.print("CURRENT PASSWORD");
      lcd.setCursor(0, 1);
      lcd.print("*"); lcd.print("*"); lcd.print(b1); lcd.write(2);
    }
    if(c1 == 3) {
      lcd.setCursor(0, 0); if(d1 == 1) lcd.print("ENTER PASSWORD"); if(d1 == 2) lcd.print("CURRENT PASSWORD");
      lcd.setCursor(0, 1);
      lcd.print("*"); lcd.print("*"); lcd.print("*"); lcd.print(b1);
    }
    delay(400);
    Button();
    if(button == 2) {
      lcd.clear();
      b1 = b1 + 1;
      if(b1 > 9) b1 = 9;
    }
    if(button == 1) {
      lcd.clear();
      b1 = b1 - 1;
      if(b1 < 0) b1 = 0;
    }
    if(button == 3) {
      b1 = 0;
      lcd.clear();
      c1 = c1 - 1;
      if(c1 < 0) c1 = 0;
      password[c1] = b1; 
    }
    if(button == 4 && c1 != 3) {
      password[c1] = b1;
      lcd.clear();
      c1 = c1 + 1;
      b1 = 0;
    }
    if(button == 5 && c1 == 3) {
      password[c1] = b1;
      for(int z1 = 0; z1 < 4; z1++) {
        if(password[z1] == EEPROM.read(z1+1)) {
           if(z1 == 3) {
             x = 1;
             if(d1 == 1) {
               lcd.clear(); lcd.setCursor(4, 0); lcd.print("UNLOCKED");
               delay(1000);
             }
             a1 = 1;
           }
        }
        if(password[z1] != EEPROM.read(z1+1)) {
          x = 0;
          lcd.clear(); lcd.setCursor(1, 0); lcd.print("WRONG PASSWORD");
          a1 = 1;
          z1 = 4; //end for loop
          delay(1000);
        }
      }
    }
  }  //end while
} //end function

int sure() {
  int i2 = 0; int j2 = 0;
  lcd.clear();
  while(i2 < 1) {
    if(j2 == 0) {
      blnk = 2;
      lcd.setCursor(2, 0); lcd.print("ARE YOU SURE!");
      menu_string = "YES";
      lcd.setCursor(11, 1); lcd.print("NO");
    }
    if(j2 == 1) {
      blnk = 3;
      lcd.setCursor(2, 0); lcd.print("ARE YOU SURE!");
      lcd.setCursor(3, 1); lcd.print("YES");
      menu_string = "NO";
    }
    Button();
    if(button == 3) {
      lcd.clear();
      j2 = j2 - 1;
      if(j2 < 0) j2 = 0;
    }
    if(button == 4) {
      lcd.clear();
      j2 = j2 + 1;
      if(j2 > 1) j2 = 1;
    }
    if(button == 5) {
      i2 = 1;
    }
  }
  lcd.clear();
  return(j2);  
}
