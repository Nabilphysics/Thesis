//Test Code for Rotational Stage
#include <EEPROM.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int button = 0;
int Blink = 0;

int left = 0;
int right = 0;
int up = 0;
int down = 0;
int ok = 0;

int s = 0;

const char *menu_string = "";
const char *space_string = "                ";

int a = 1;
int b = 2;
int c = 3;
int d = 4;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("LOADING");
  for(int z = 1; z <= 10; z++) {
    if(z < 10) lcd.setCursor(7, 1);
    if(z == 10) lcd.setCursor(6, 1);
    lcd.print(z*10);
    lcd.setCursor(9, 1);
    lcd.print("%");
    delay(250);
    lcd.setCursor(6, 1);
    lcd.print("   ");
    delay(250);
  }
  lcd.clear(); 
  lcd.setCursor(2, 0);
  lcd.print("MADE BY Dept. of");
  lcd.setCursor(0, 1);
  lcd.print("  PHYSICS SUST");
  delay(2000);
}

void loop() {
  int b = 0;
  int t = 0;
  lcd.clear();
  while(t < 1) {
    Blink = 1;
    if(b == 0) {
      menu_string = "START CONTROL";
      lcd.setCursor(0, 1); lcd.print("SETTINGS");
    }
    if(b == 1) {
      lcd.setCursor(0, 0); lcd.print("START CONTROL");
      menu_string = "SETTINGS";
    }
    BUTTON(b);
  
    if(button == 4) {
      lcd.clear();
      b = b + 1;
      if(b > 1) b = 1;
    }
  
    if(button == 3) {
      lcd.clear();
      b = b - 1;
      if(b < 0) b = 0;
    }
  
    if(button == 5) {
      if(b == 0) MAIN();
      if(b == 1) SETTINGS();
    }
  }
}

void MAIN() {
  lcd.clear();
  int k = EEPROM.read(2);
  int l = 0; int m = 0;
  while(l < 1) {
    if(m == 0) {
      lcd.clear();
      Blink = 0;
      lcd.setCursor(0, 0); lcd.print("DEGREE = "); lcd.setCursor(9, 0); lcd.print(k);
      lcd.setCursor(0, 1); lcd.print("BACK");
    }
    if(m == 1) {
      lcd.clear();
      Blink = 1;
      lcd.setCursor(0, 0); lcd.print("DEGREE = "); lcd.setCursor(9, 0); lcd.print(k);
      menu_string = "BACK";
    }
    delay(100);
    BUTTON(m);
    if(button == 4) {
      lcd.clear();
      m = m + 1;
      if(m > 1) m = 1;
    }
    if(button == 3) {
      lcd.clear();
      m = m - 1;
      if(m < 0) m = 0;
    }
    if(button == 2) {
      k = k + (2*EEPROM.read(0));
      if(k == 360) k = 0;
      EEPROM.write(2, k);
      for(s = 0; s < EEPROM.read(0); s++) {
        PULSE(EEPROM.read(3));
      }
    }
    if(button == 5 && m == 1) {
      lcd.clear();
      l = 1;
    }
  } 
}

void SETTINGS() {
  lcd.clear();
  int d = 0; int e = 0;
  while(d < 1) {
    Blink = 1;
    if(e == 0) {
      menu_string = "SELECT STEP";
      lcd.setCursor(0, 1); lcd.print("RESET TO ZERO");
    }
    if(e == 1) {
      lcd.setCursor(0, 0); lcd.print("SELECT STEP");
      menu_string = "RESET TO ZERO";
    }
    if(e == 2) {
      lcd.setCursor(0, 0); lcd.print("RESET TO ZERO");
      menu_string = "BACK";
    }
    BUTTON(e);
    if(button == 4) {
      lcd.clear();
      e = e + 1;
      if(e > 2) e = 2;
    }
    
    if(button == 3) {
      lcd.clear();
      e = e - 1;
      if(e < 0) e = 0;
    }
    
    if(button == 5) {
      if(e == 0) DEGREE();
      if(e == 1) RESET();
      if(e == 2) d = 1;
    }
  }   //while d end
}

void DEGREE() {
  lcd.clear();
  int f = 0; int g = 0; int h = 0;
  while(f < 1) {
    if(g == 0) {
      Blink = 0;
      lcd.setCursor(0, 0); lcd.print("STEP = "); lcd.setCursor(7, 0); lcd.print(2*h);
      lcd.setCursor(0, 1); lcd.print("OK");
    }
    if(g == 1) {
      Blink = 1;
      lcd.setCursor(0, 0); lcd.print("STEP = "); lcd.setCursor(7, 0); lcd.print(2*h);
      menu_string = "OK";
    }
    delay(100);
    BUTTON(g);
    if(button == 4) {
      lcd.clear();
      g = g + 1;
      if(g > 1) g = 1;
    }
    if(button == 3) {
      lcd.clear();
      g = g - 1;
      if(g < 0) g = 0;
    }
    if(button == 2) {
      lcd.clear();
      h = h + 1;    //eaach step change by 2
      if(h > 180) h = 180;
    }
    if(button == 1) { 
      lcd.clear();
      h = h - 1;
      if(h < 1) h = 1;
    }
    if(g == 1 && button == 5) {
      lcd.clear();
      EEPROM.write(0, h);
      f = 1;
    }
  }  //while f end
}   //BUTTON END

void RESET() {
  lcd.clear();
  int i = 0; int j = 0;
  while(i < 1) {
    if(j == 0) {
      Blink = 2;
      lcd.setCursor(2, 0); lcd.print("ARE YOU SURE");
      menu_string = "YES";
      lcd.setCursor(11, 1); lcd.print("NO");
    }
    if(j == 1) {
      Blink = 3;
      lcd.setCursor(2, 0); lcd.print("ARE YOU SURE");
      lcd.setCursor(3, 1); lcd.print("YES");
      menu_string = "NO";
    }
    BUTTON(1);
    if(button == 2) {
      lcd.clear(); 
      j = j + 1;
      if(j > 1) j = 1;
    }
    if(button == 1) {
      lcd.clear();
      j = j- 1;
      if(j < 0) j = 0;
    }
    if(button == 5) {
      lcd.clear();
      if(j == 0) {
        i = 1;
        EEPROM.write(2, 0);
      }
      if(j == 1) {
        i = 1;
      }
    }
  }     //while end
}      //reset end

void BUTTON(int c) {                                    //BUTTON FUNCTION
  if(c > 1) c = 1;
  int a = 0;
  while(a < 1) {
    if(Blink == 1) {
      lcd.setCursor(0, c); lcd.print(menu_string);
      delay(150);
      lcd.setCursor(0, c); lcd.print(space_string);
      delay(150);
    }
    if(Blink == 2) {
      lcd.setCursor(3, 1); lcd.print(menu_string);
      delay(150);
      lcd.setCursor(3, 1); lcd.print("   ");
      delay(150);
    }
    if(Blink == 3) {
      lcd.setCursor(11, 1); lcd.print(menu_string);
      delay(150);
      lcd.setCursor(11, 1); lcd.print("  ");
      delay(150);
    }
    
    else delay(50);
    
    left = analogRead(A0);
    right = analogRead(A1);
    up = analogRead(A2);
    down = analogRead(A3);
    ok = analogRead(A4);
    
    if(left > 500) {
      button = 1;
      a = 1;
    }
    
    if(right > 500) {
      button = 2;
      a = 1;
    }
    
    if(up > 500) {
      button = 3;
      a = 1;
    }
    
    if(down > 500) {
      button = 4;
      a = 1;
    }
    
    if(ok > 500) {
      button = 5;
      a = 1;
    }
  }  // while end
}

void PULSE(int n) {
  if(n == 0) {
    for(int o = 1; o <= 3; o++) {
      digitalWrite(a, HIGH); 
      digitalWrite(b, LOW); 
      digitalWrite(c, LOW); 
      digitalWrite(d, LOW); 
      delay(150);
    
      digitalWrite(a, LOW); 
      digitalWrite(b, HIGH); 
      digitalWrite(c, LOW); 
      digitalWrite(d, LOW); 
      delay(150);
    
      digitalWrite(a, LOW); 
      digitalWrite(b, LOW); 
      digitalWrite(c, HIGH); 
      digitalWrite(d, LOW); 
      delay(150);
    
      digitalWrite(a, LOW); 
      digitalWrite(b, LOW); 
      digitalWrite(c, LOW); 
      digitalWrite(d, HIGH); 
      delay(150);
    }
    digitalWrite(a, HIGH); 
    digitalWrite(b, LOW); 
    digitalWrite(c, LOW); 
    digitalWrite(d, LOW); 
    delay(150);
    digitalWrite(a, LOW); 
    digitalWrite(b, LOW); 
    digitalWrite(c, LOW); 
    digitalWrite(d, LOW); 
  }
  if(n == 1) {
    for(int p = 1; p <= 3; p++) {
      digitalWrite(a, LOW); 
      digitalWrite(b, HIGH); 
      digitalWrite(c, LOW); 
      digitalWrite(d, LOW); 
      delay(150);
    
      digitalWrite(a, LOW); 
      digitalWrite(b, LOW); 
      digitalWrite(c, HIGH); 
      digitalWrite(d, LOW); 
      delay(150);
    
      digitalWrite(a, LOW); 
      digitalWrite(b, LOW); 
      digitalWrite(c, LOW); 
      digitalWrite(d, HIGH); 
      delay(150);
      
      digitalWrite(a, HIGH); 
      digitalWrite(b, LOW); 
      digitalWrite(c, LOW); 
      digitalWrite(d, LOW); 
      delay(150);
    }
    digitalWrite(a, LOW); 
    digitalWrite(b, HIGH); 
    digitalWrite(c, LOW); 
    digitalWrite(d, LOW); 
    delay(150);
    digitalWrite(a, LOW); 
    digitalWrite(b, LOW); 
    digitalWrite(c, LOW); 
    digitalWrite(d, LOW);
  }
  if(n == 2) {
    for(int q = 1; q <= 3; q++) {
      digitalWrite(a, LOW); 
      digitalWrite(b, LOW); 
      digitalWrite(c, HIGH); 
      digitalWrite(d, LOW); 
      delay(150);
    
      digitalWrite(a, LOW); 
      digitalWrite(b, LOW); 
      digitalWrite(c, LOW); 
      digitalWrite(d, HIGH); 
      delay(150);
      
      digitalWrite(a, HIGH); 
      digitalWrite(b, LOW); 
      digitalWrite(c, LOW); 
      digitalWrite(d, LOW); 
      delay(150);
      
      digitalWrite(a, LOW); 
      digitalWrite(b, HIGH); 
      digitalWrite(c, LOW); 
      digitalWrite(d, LOW); 
      delay(150);
    }
    digitalWrite(a, LOW); 
    digitalWrite(b, LOW); 
    digitalWrite(c, HIGH); 
    digitalWrite(d, LOW); 
    delay(150);
    digitalWrite(a, LOW); 
    digitalWrite(b, LOW); 
    digitalWrite(c, LOW); 
    digitalWrite(d, LOW);
  }
  if(n == 3) {
    for(int r = 0; r <= 3; r ++) {
      digitalWrite(a, LOW); 
      digitalWrite(b, LOW); 
      digitalWrite(c, LOW); 
      digitalWrite(d, HIGH); 
      delay(150);
      
      digitalWrite(a, HIGH); 
      digitalWrite(b, LOW); 
      digitalWrite(c, LOW); 
      digitalWrite(d, LOW); 
      delay(150);
      
      digitalWrite(a, LOW); 
      digitalWrite(b, HIGH); 
      digitalWrite(c, LOW); 
      digitalWrite(d, LOW); 
      delay(150);
      
      digitalWrite(a, LOW); 
      digitalWrite(b, LOW); 
      digitalWrite(c, HIGH); 
      digitalWrite(d, LOW); 
      delay(150);
    }
    digitalWrite(a, LOW); 
    digitalWrite(b, LOW); 
    digitalWrite(c, LOW); 
    digitalWrite(d, HIGH); 
    delay(150);
    digitalWrite(a, LOW); 
    digitalWrite(b, LOW); 
    digitalWrite(c, LOW); 
    digitalWrite(d, LOW);
  }
  n = n + 1;
  if(n > 3) n = 0;
  EEPROM.write(3, n);
}
    


