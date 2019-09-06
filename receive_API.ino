#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // 이건 걍 필수
  lcd.init();     // 제일 처음에 한번만 해주기
  lcd.clear();    // lcd 싹 다 지우기

  ///////////굳이 없어도 되지만 켜진걸 확인하는거/////////
  lcd.noBacklight(); // 백라이트 X
  delay(500);
  lcd.backlight();   // 백라이트 o
  delay(500);

  lcd.setCursor(0, 0);  // (가로 배열, 세로 배열)
  lcd.print("Test");
  delay(1000);
  lcd.setCursor(5, 0);
  lcd.print("LCD");
  delay(1000);
  ///////////굳이 없어도 되지만 켜진걸 확인하는거 끝/////////
}

void loop() {
  // put your main code here, to run repeatedly:
  static double temp = 0.00;
  static char location[5] = {"Jeju"};
  static String weather; // node.js에서 보낸 값 받아오는 변수
  lcd.setCursor(0, 0);  // 커서 제일 앞으로
  
  if(Serial.available() > 0){    // node.js랑 연결되면 
    weather = Serial.readStringUntil('\n'); // node.js에서 보내는 값 읽어오기
  }
  
//  if(weather == '1'){ // node.js에서 1을 보내면? (아스키코드로 1이 49)
//    lcd.clear(); // 처음부터 다시 띄워줘야하니 클리어 한번
//    lcd.setCursor(0, 0); // 커서도 젤 첨으로
//    lcd.print("sunny"); // 이건 알겠지..?
//  }
//
//  else if(weather == '0'){ // node.js에서 0을 보내면? (아스키코드로 0이 48)
//    lcd.clear();
//    lcd.setCursor(0, 0);
//    lcd.print("raning");
//  }

  lcd.clear();
  lcd.setCursor(0, 0);
  String copy = weather;
  copy = strstr(weather, "Loc:");
  lcd.print(weather);
  lcd.setCursor(0, 1);
  


  delay(1000);
}
