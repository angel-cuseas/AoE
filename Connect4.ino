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
  Serial.begin(9600);
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
}

void loop() {
  matrix.drawRect(4,2,2,16, matrix.Color333(0,0,7));
  matrix.drawRect(26,2,2,16, matrix.Color333(0,0,7));
  int win = 0;
  while(win==0){    
    matrix.setCursor(0,0);
    matrix.setTextColor(matrix.Color333(255,255,0));
    matrix.print("1");
    matrix.drawRect(4,2,2,16, matrix.Color333(0,0,7));
    matrix.fillRect(4,0,2,2, matrix.Color333(0,0,0));
    int xPos = 6;
    int p1selection = 0;
    matrix.drawRect(6,0,2,2, matrix.Color333(255,255,0));
    while(p1selection==0){
      if(digitalRead(11)==HIGH){
        p1selection++;
        break;
      }
      delay(500);
      if(analogRead(A3)>530){
        if(xPos<24){
          matrix.fillRect(xPos-2,0,2,2, matrix.Color333(0,0,0));
          xPos = xPos+2;
          matrix.drawRect(xPos,0,2,2, matrix.Color333(255,255,0));
          matrix.fillRect(xPos-2,0,2,2, matrix.Color333(0,0,0));
        }
      }
      else if(analogRead(A3)<500){
       if(xPos>6){
          matrix.fillRect(xPos+2,0,2,2, matrix.Color333(0,0,0));
          xPos = xPos-2;
          matrix.drawRect(xPos,0,2,2, matrix.Color333(255,255,0));
          matrix.fillRect(xPos+2,0,2,2, matrix.Color333(0,0,0));
        }
      }
    }
    matrix.fillRect(xPos,0,2,2, matrix.Color333(0,0,0));
    selections[(xPos-6)/2][((columns[(xPos-6)/2])-2)/2]=1;//[0][6]
    matrix.drawRect(xPos,columns[(xPos-6)/2],2,2, matrix.Color333(255,255,0));
    columns[(xPos-6)/2] = columns[(xPos-6)/2] - 2;
    if(connectFourPlayer1(selections)){
      win++;
    }
    delay(1000);
    matrix.fillRect(0,0,4,7,matrix.Color333(0,0,0));
    
    //player 2
    if(win==0){
    matrix.setCursor(0,0);
    matrix.setTextColor(matrix.Color333(255,0,0));
    matrix.print("2");
    xPos = 6;
    int p2selection = 0;
    matrix.drawRect(6,0,2,2, matrix.Color333(255,0,0));
    while(p2selection==0){
      if(digitalRead(11)==HIGH){
        p2selection++;
        break;
      }
      delay(500);
      if(analogRead(A3)>530){
        if(xPos<24){
          matrix.fillRect(xPos-2,0,2,2, matrix.Color333(0,0,0));
          xPos = xPos+2;
          matrix.drawRect(xPos,0,2,2, matrix.Color333(255,0,0));
          matrix.fillRect(xPos-2,0,2,2, matrix.Color333(0,0,0));
        }
      }
      else if(analogRead(A3)<500){
       if(xPos>6){
          matrix.fillRect(xPos+2,0,2,2, matrix.Color333(0,0,0));
          xPos = xPos-2;
          matrix.drawRect(xPos,0,2,2, matrix.Color333(255,0,0));
          matrix.fillRect(xPos+2,0,2,2, matrix.Color333(0,0,0));
        }
      }
    }
    matrix.fillRect(xPos,0,2,2, matrix.Color333(0,0,0));
    selections[(xPos-6)/2][((columns[(xPos-6)/2])-2)/2]=2;
    matrix.drawRect(xPos,columns[(xPos-6)/2],2,2, matrix.Color333(255,0,0));
    columns[(xPos-6)/2] = columns[(xPos-6)/2] - 2;
    delay(1000);
    matrix.fillRect(0,0,4,7,matrix.Color333(0,0,0));
    if(connectFourPlayer2(selections) == true){
      win++;
    }
  }
  }
  if(connectFourPlayer1(selections) == true){
      matrix.fillRect(0,0,31,15,matrix.Color333(0,0,0));
      matrix.setCursor(0,0);
      matrix.print("P1");
      matrix.setCursor(0,8);
      matrix.print("WINS");
      matrix.fillRect(0, 15, 31, 1,matrix.Color333(0,0,0));
      delay(5000);
      matrix.fillRect(0,0,31,15,matrix.Color333(0,0,0));
    }
   if(connectFourPlayer2(selections) == true){
      matrix.fillRect(0,0,31,15,matrix.Color333(0,0,0));
      matrix.setCursor(0,0);
      matrix.print("P2");
      matrix.setCursor(0,8);
      matrix.print("WINS");
      matrix.fillRect(0, 15, 31, 1,matrix.Color333(0,0,0));
      delay(5000);
      matrix.fillRect(0,0,31,15,matrix.Color333(0,0,0));
    }
    for(int i=0; i<sizeof(columns); i++){
      columns[i]=14;
    }
    for(int i=0; i<7; i++){
      for(int j=0; j<10; j++){
        selections[i][j]=0;
      }
    }
}

boolean connectFourPlayer1(int [][10]){
  int fourInARow = 0;
  for(int i=0; i<7; i++){//horizontal
    for(int j=0; j<10; j++){
      if(selections[i][j]==1 && selections[i][j+1]==1 && selections[i][j+2]==1 && selections[i][j+3]==1){
        fourInARow+=1;
      }
    }
  }
 for(int i=0; i<7; i++){//vertical
    for(int j=0; j<10; j++){
      if(selections[i][j]==1 && selections[i+1][j]==1 && selections[i+2][j]==1 && selections[i+3][j]==1){
        fourInARow+=1;
      }
    }
  }
  for(int i=0; i<7; i++){//diagonal right
    for(int j=0; j<10; j++){
      if(selections[i][j]==1 && selections[i+1][j+1]==1 && selections[i+2][j+2]==1 && selections[i+3][j+3]==1){
        fourInARow+=1;
      }
    }
  }
 for(int i=6; i>=0; i--){//diagonal left
    for(int j=0; j<10; j++){
      if(selections[i][j]==1 && selections[i-1][j+1]==1 && selections[i-2][j+2]==1 && selections[i-3][j+3]==1){
        fourInARow+=1;
      }
    }
  }
    
  if(fourInARow!=0){
    return true;
  }
  return false;
}

boolean connectFourPlayer2(int [][10]){
  int fourInARow = 0;
  for(int i=0; i<7; i++){//horizontal
    for(int j=0; j<10; j++){
        if(selections[i][j]==2 && selections[i][j+1]==2 && selections[i][j+2]==2 && selections[i][j+3]==2){
          fourInARow+=1;
      }
    }
  }
 for(int i=0; i<7; i++){//vertical
    for(int j=0; j<10; j++){
      if(selections[i][j]==2 && selections[i+1][j]==2 && selections[i+2][j]==2 && selections[i+3][j]==2){
        fourInARow+=1;
      }
    }
  }
  for(int i=0; i<7; i++){//diagonal right
    for(int j=0; j<10; j++){
      if(selections[i][j]==2 && selections[i+1][j+1]==2 && selections[i+2][j+2]==2 && selections[i+3][j+3]==2){
        fourInARow+=1;
      }
    }
  }
 for(int i=6; i>=0; i--){//diagonal left
    for(int j=0; j<10; j++){
      if(selections[i][j]==2 && selections[i-1][j+1]==2 && selections[i-2][j+2]==2 && selections[i-3][j+3]==2){
        fourInARow+=1;
      }
    }
  }
 
  if(fourInARow!=0){
    return true;
  }
  return false;
}
  
