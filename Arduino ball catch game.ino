#include "Wire.h" 
#include "LiquidCrystal_I2C.h"

//connections
const short button = 2;
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const short buzzer = 8;
//LED segment ports
const short a=4; 
const short b=5; 
const short c=1; 
const short d=10; 
const short e=9; 
const short f=6; 
const short g=7; 
const short dp=3; 


const short spawnPos = 16;
short ballsA[15];
short ballsB[15];
short ballsLengthA = 0;
short ballsLengthB = 0;
bool alreadyClicked = false;
bool playerPos = 0;

int score = 0;


void setup()
{
 pinMode(a, OUTPUT);
 pinMode(b, OUTPUT);
 pinMode(c, OUTPUT);
 pinMode(d, OUTPUT);
 pinMode(e, OUTPUT);
 pinMode(f, OUTPUT);
 pinMode(g, OUTPUT);
 pinMode(dp, OUTPUT);


 Serial.begin(9600);
 pinMode(button, INPUT);
 lcd.init();                   
 lcd.print('>');
 lcd.backlight();
 lcd.noCursor();
 lcd.noBlink();
 showNum(0);
}
void loop()
{
    //handle button
  if(digitalRead(button) && !alreadyClicked){
      movePlayer();
  } else if (!digitalRead(button) && alreadyClicked) {
    alreadyClicked = false;
  }
  delay(400);
 
  //move balls
  for(int i = 0; i < ballsLengthA; ++i){
    moveBall(i, 0);
  }
  for(int i = 0; i < ballsLengthB; ++i){
    moveBall(i, 1);
  }

  //spawn balls
  if(random(101) > 90){
  spawnBall(0);
  } else if (random(101) > 90){
    spawnBall(1);
  }


  //check collisions or exits
  for(int i = 0; i < ballsLengthA; ++i){
    if(ballsA[i] == 0){
      onExit(i, 0);
    }
  }
  for(int i = 0; i < ballsLengthB; ++i){
    if(ballsB[i] == 0){
      onExit(i, 1);
    }
  }

}

void onExit(short posInArray, bool row){
 if (row == playerPos){
  Serial.println(++score);
  showNum(score%9);
  //audio feedback
  tone(buzzer,262);
  delay(100);
  tone(buzzer,196,196);
  delay(50);
  tone(buzzer,247);
  delay(100);
  tone(buzzer,262);
  delay(300);
  noTone(buzzer);
 } 
  lcd.setCursor(0,row);
  if(playerPos == row){
      lcd.print(">");
  } else {
    lcd.print(" ");
  }

 //delete and shift remaining;
 if(!row){
  for (int i = posInArray; i < ballsLengthA; ++i){
    ballsA[i] = ballsA[i + 1]; // copy next element left
  }
  ballsLengthA--;
 } else {
    for (int i = posInArray; i < ballsLengthB; ++i){
    ballsB[i] = ballsB[i + 1]; // copy next element left
  }
  ballsLengthB--;
 }
}

void moveBall(short ball, bool row){
  if(row == 0){
    lcd.setCursor(ballsA[ball],row);
    lcd.print(" ");
    lcd.setCursor(--ballsA[ball],row);
  } else {
    lcd.setCursor(ballsB[ball],row);
    lcd.print(" ");
    lcd.setCursor(--ballsB[ball],row);
  }

  lcd.print("O");
}

void spawnBall(short row){
  lcd.setCursor(spawnPos,row);
  lcd.print('O');
  if(row == 0){
  ballsA[ballsLengthA++] = spawnPos;
  } else{
  ballsB[ballsLengthB++] = spawnPos;
  }
}


void movePlayer(){
  //clear old
  lcd.setCursor(0,playerPos);
  lcd.print(' ');
  
  //move player
  playerPos = !playerPos;
  lcd.setCursor(0,playerPos);
  lcd.print('>');
  alreadyClicked = true;
}

///LED  display
void showNum(const short num){
  //clear
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(g,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);  
  digitalWrite(e,LOW);  
  digitalWrite(f,LOW);  


  switch(num){
      case 0:
        digitalWrite(a,HIGH);
        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(d,HIGH);  
        digitalWrite(e,HIGH);  
        digitalWrite(f,HIGH);  
    break;
      case 1:
        digitalWrite(b,HIGH);
        digitalWrite(c,HIGH);
    break;
      case 2:
        digitalWrite(a,HIGH);
        digitalWrite(b,HIGH);
        digitalWrite(g,HIGH);
        digitalWrite(e,HIGH);
        digitalWrite(d,HIGH);
    break;
      case 3:
          digitalWrite(a,HIGH);
          digitalWrite(b,HIGH);
          digitalWrite(c,HIGH);
          digitalWrite(d,HIGH);
          digitalWrite(g,HIGH);
    break;
      case 4:
          digitalWrite(f,HIGH);
          digitalWrite(b,HIGH);
          digitalWrite(g,HIGH);
          digitalWrite(c,HIGH);
    break;
      case 5:
        digitalWrite(a,HIGH);
        digitalWrite(f,HIGH);
        digitalWrite(g,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(d,HIGH);
    break;
      case 6:
          digitalWrite(a,HIGH);
          digitalWrite(f,HIGH);
          digitalWrite(g,HIGH);
          digitalWrite(c,HIGH);
          digitalWrite(d,HIGH);  
          digitalWrite(e,HIGH);  
    break;
      case 7:
          digitalWrite(a,HIGH);
          digitalWrite(b,HIGH);
          digitalWrite(c,HIGH);
    break;
      case 8:
          digitalWrite(a,HIGH);
          digitalWrite(b,HIGH);
          digitalWrite(g,HIGH);
          digitalWrite(c,HIGH);
          digitalWrite(d,HIGH);  
          digitalWrite(e,HIGH);  
          digitalWrite(f,HIGH);  
    break;
      case 9:
        digitalWrite(a,HIGH);
        digitalWrite(b,HIGH);
        digitalWrite(g,HIGH);
        digitalWrite(c,HIGH);
        digitalWrite(d,HIGH);  
        digitalWrite(f,HIGH);  
    break;
  }
}

