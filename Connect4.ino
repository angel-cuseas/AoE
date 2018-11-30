#include <RGBmatrixPanel.h>

#define CLK  8
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

int columns[] = {14,14,14,14,14,14,14,14,14,14};
int selections [][10] = { {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0} };

//A3 = xPos



RGBmatrixPanel matrix (A, B, C, CLK, LAT, OE, false);

void setup() {
  pinMode(11,INPUT);
  matrix.begin();
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.setTextSize(1);
  matrix.print("Welcome");
  delay(1000);
  matrix.fillScreen(0);
  matrix.setCursor(0,0);
  matrix.print("To");
  delay(1000);
  matrix.fillScreen(0);
  matrix.setCursor(0,0);
  matrix.print("Connect");
  delay(1000);
  matrix.fillScreen(0);
  matrix.setCursor(0,0);
  matrix.print("Four!!!");
  delay(1000);
  matrix.fillScreen(0);
  matrix.drawRect(4,0,2,16, matrix.Color333(0,0,7));
  matrix.drawRect(26,0,2,16, matrix.Color333(0,0,7));
}

void loop() {
  int win=0;
  while(win==0){
    matrix.setCursor(0,0);
    matrix.setTextColor(matrix.Color333(255,255,0));
    matrix.print("1");
    int xPos = 6;
    while(digitalRead(11)!=HIGH){
      if(analogRead(A3)>512){
        delay(800);
        if(xPos<24){
          delay(1000);
          matrix.fillRect(xPos-2,0,2,2, matrix.Color333(0,0,0));
          if(xPos==6){
            matrix.drawRect(xPos-2,0,2,2, matrix.Color333(0,0,7));
          }
          xPos = xPos+2;
          matrix.drawRect(xPos,0,2,2, matrix.Color333(255,255,0));
        }
      }
      else if(analogRead(A3)<512){
        delay(800);
        if(xPos>6){
        xPos = xPos-2;
        matrix.fillRect(xPos-2,0,2,2, matrix.Color333(0,0,0));
        xPos = xPos+2;
        matrix.drawRect(xPos,0,2,2, matrix.Color333(255,255,0));
      }
      }
    }
    if(digitalRead(11)==HIGH){
      matrix.fillRect(xPos-2,0,2,2, matrix.Color333(0,0,0));
      selections[xPos-6][columns[xPos-6]] = 1;
    }
    matrix.fillRect(0,0,4,7,matrix.Color333(0,0,0));
    matrix.setCursor(28,0);
    matrix.setTextColor(matrix.Color333(255,0,0));
    matrix.print("2");
    xPos = 6;
    while(digitalRead(11)!=HIGH){
      if(analogRead(A3)>512){
        delay(800);
        if(xPos<24){
          matrix.fillRect(xPos-2,0,2,2, matrix.Color333(0,0,0));
          xPos = xPos+2;
          matrix.drawRect(xPos,0,2,2, matrix.Color333(255,255,0));
        }
      }
      else if(analogRead(A3)<512){
        delay(800);
        if(xPos>6){
        xPos = xPos-2;
        matrix.fillRect(xPos-2,0,2,2, matrix.Color333(0,0,0));
        if(xPos==6){
            matrix.drawRect(xPos-2,0,2,2, matrix.Color333(0,0,7));
          }
        xPos = xPos+2;
        matrix.drawRect(xPos,0,2,2, matrix.Color333(255,255,0));
      }
      }
    }
    if(digitalRead(11)==HIGH){
      matrix.fillRect(xPos-2,0,2,2, matrix.Color333(0,0,0));
      selections[xPos-6][columns[xPos-6]] = 2;
    }
    matrix.fillRect(28,0,4,7, matrix.Color333(0,0,0));
  }
}
  
