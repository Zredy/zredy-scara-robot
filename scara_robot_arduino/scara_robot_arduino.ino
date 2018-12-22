//Deklaracija PIN-ova za stepper drivere
int PIN_5 = 4;
int PIN_6 = 5;
int PIN_7 = 6;
int PIN_8 = 7;
int PIN_1 = 8;
int PIN_2 = 9;
int PIN_3 = 10;
int PIN_4 = 11;

//Deklaracija ostalih varijabli
int Steps = 0;
int Steps1 = 0;
int dir1 = 0;
int dir2 = 0;
int c,v;
int delayTime = 1;
int recStepA;
int recStepB;


void setup(){
//Otvaranje Serial Porta
Serial.begin(115200);

//Setanje PIN-ova na OUTPUT mod da se omoguci kontrola
pinMode(PIN_1, OUTPUT);
pinMode(PIN_2, OUTPUT);
pinMode(PIN_3, OUTPUT);
pinMode(PIN_4, OUTPUT);
pinMode(PIN_5, OUTPUT);
pinMode(PIN_6, OUTPUT);
pinMode(PIN_7, OUTPUT);
pinMode(PIN_8, OUTPUT);
}

void loop(){
  //Provjera za podatke na Serijskom portu
  while (Serial.available()) {
    c = Serial.read();
    if(c == 'a'){
      dir1 = 1;
    } else if(c == 'b'){
      dir1 = 2;
    } else if(c == 'c'){
      dir2 = 1;
    } else if(c == 'd'){
      dir2 = 2;
    } else if ((c >= '0') && (c <= '9')) {
      //Pretvaranje stringa broja u integer
      v = 10 * v + c - '0';
      if(dir1 != 0){
        recStepA = v;
      } else if(dir2 != 0){
        recStepB = v;
      }
    } else if (c == 'e') {
      Serial.println(v);
      recStepA = v;
      v = 0;
    } else if (c == 'f') {
      Serial.println(v);
      recStepB = v;
      v = 0;
      dir1 = 0;
      dir2 = 0;
    }
    //Naredba za pokretanje steppera
    if(dir1 != 0 and dir2 != 0){
      stepBoth(recStepA, recStepB, dir1, dir2);
    }
  }
}

//Funkcija za kretanje steppera
void stepBoth(int stepsA, int stepsB, int dirA, int dirB){
  int stepA = stepsA;
  int stepB = stepsB;
  
  //Pokretanje oba steppera istovremeno
  while(stepA > 0 and stepB > 0){
    delay(delayTime);
    switch(Steps1){
       case 0:
         digitalWrite(PIN_1, LOW); 
         digitalWrite(PIN_2, HIGH);
         digitalWrite(PIN_3, HIGH);
         digitalWrite(PIN_4, HIGH);
       break; 
       case 1:
         digitalWrite(PIN_1, LOW); 
         digitalWrite(PIN_2, LOW);
         digitalWrite(PIN_3, HIGH);
         digitalWrite(PIN_4, HIGH);
       break; 
       case 2:
         digitalWrite(PIN_1, HIGH); 
         digitalWrite(PIN_2, LOW);
         digitalWrite(PIN_3, HIGH);
         digitalWrite(PIN_4, HIGH);
       break; 
       case 3:
         digitalWrite(PIN_1, HIGH); 
         digitalWrite(PIN_2, LOW);
         digitalWrite(PIN_3, LOW);
         digitalWrite(PIN_4, HIGH);
       break; 
       case 4:
         digitalWrite(PIN_1, HIGH); 
         digitalWrite(PIN_2, HIGH);
         digitalWrite(PIN_3, LOW);
         digitalWrite(PIN_4, HIGH);
       break; 
       case 5:
         digitalWrite(PIN_1, HIGH); 
         digitalWrite(PIN_2, HIGH);
         digitalWrite(PIN_3, LOW);
         digitalWrite(PIN_4, LOW);
       break; 
         case 6:
         digitalWrite(PIN_1, HIGH); 
         digitalWrite(PIN_2, HIGH);
         digitalWrite(PIN_3, HIGH);
         digitalWrite(PIN_4, LOW);
       break; 
       case 7:
         digitalWrite(PIN_1, LOW); 
         digitalWrite(PIN_2, HIGH);
         digitalWrite(PIN_3, HIGH);
         digitalWrite(PIN_4, LOW);
       break; 
       default:
         digitalWrite(PIN_1, LOW); 
         digitalWrite(PIN_2, LOW);
         digitalWrite(PIN_3, LOW);
         digitalWrite(PIN_4, LOW);
       break; 
    }
    switch(Steps){
       case 0:
         digitalWrite(PIN_5, LOW); 
         digitalWrite(PIN_6, HIGH);
         digitalWrite(PIN_7, HIGH);
         digitalWrite(PIN_8, HIGH);
       break; 
       case 1:
         digitalWrite(PIN_5, LOW); 
         digitalWrite(PIN_6, LOW);
         digitalWrite(PIN_7, HIGH);
         digitalWrite(PIN_8, HIGH);
       break; 
       case 2:
         digitalWrite(PIN_5, HIGH); 
         digitalWrite(PIN_6, LOW);
         digitalWrite(PIN_7, HIGH);
         digitalWrite(PIN_8, HIGH);
       break; 
       case 3:
         digitalWrite(PIN_5, HIGH); 
         digitalWrite(PIN_6, LOW);
         digitalWrite(PIN_7, LOW);
         digitalWrite(PIN_8, HIGH);
       break; 
       case 4:
         digitalWrite(PIN_5, HIGH); 
         digitalWrite(PIN_6, HIGH);
         digitalWrite(PIN_7, LOW);
         digitalWrite(PIN_8, HIGH);
       break; 
       case 5:
         digitalWrite(PIN_5, HIGH); 
         digitalWrite(PIN_6, HIGH);
         digitalWrite(PIN_7, LOW);
         digitalWrite(PIN_8, LOW);
       break; 
         case 6:
         digitalWrite(PIN_5, HIGH); 
         digitalWrite(PIN_6, HIGH);
         digitalWrite(PIN_7, HIGH);
         digitalWrite(PIN_8, LOW);
       break; 
       case 7:
         digitalWrite(PIN_5, LOW); 
         digitalWrite(PIN_6, HIGH);
         digitalWrite(PIN_7, HIGH);
         digitalWrite(PIN_8, LOW);
       break; 
       default:
         digitalWrite(PIN_5, LOW); 
         digitalWrite(PIN_6, LOW);
         digitalWrite(PIN_7, LOW);
         digitalWrite(PIN_8, LOW);
       break; 
    }
    dirSet(dirA, dirB);
    stepA--;
    stepB--;
  }
  //Pokretanje A steppera
  while(stepA > 0){
    delay(delayTime);
    switch(Steps1){
       case 0:
         digitalWrite(PIN_1, LOW); 
         digitalWrite(PIN_2, HIGH);
         digitalWrite(PIN_3, HIGH);
         digitalWrite(PIN_4, HIGH);
       break; 
       case 1:
         digitalWrite(PIN_1, LOW); 
         digitalWrite(PIN_2, LOW);
         digitalWrite(PIN_3, HIGH);
         digitalWrite(PIN_4, HIGH);
       break; 
       case 2:
         digitalWrite(PIN_1, HIGH); 
         digitalWrite(PIN_2, LOW);
         digitalWrite(PIN_3, HIGH);
         digitalWrite(PIN_4, HIGH);
       break; 
       case 3:
         digitalWrite(PIN_1, HIGH); 
         digitalWrite(PIN_2, LOW);
         digitalWrite(PIN_3, LOW);
         digitalWrite(PIN_4, HIGH);
       break; 
       case 4:
         digitalWrite(PIN_1, HIGH); 
         digitalWrite(PIN_2, HIGH);
         digitalWrite(PIN_3, LOW);
         digitalWrite(PIN_4, HIGH);
       break; 
       case 5:
         digitalWrite(PIN_1, HIGH); 
         digitalWrite(PIN_2, HIGH);
         digitalWrite(PIN_3, LOW);
         digitalWrite(PIN_4, LOW);
       break; 
         case 6:
         digitalWrite(PIN_1, HIGH); 
         digitalWrite(PIN_2, HIGH);
         digitalWrite(PIN_3, HIGH);
         digitalWrite(PIN_4, LOW);
       break; 
       case 7:
         digitalWrite(PIN_1, LOW); 
         digitalWrite(PIN_2, HIGH);
         digitalWrite(PIN_3, HIGH);
         digitalWrite(PIN_4, LOW);
       break; 
       default:
         digitalWrite(PIN_1, LOW); 
         digitalWrite(PIN_2, LOW);
         digitalWrite(PIN_3, LOW);
         digitalWrite(PIN_4, LOW);
       break; 
    }
    dirSet(dirA, dirB);
    stepA--;
  }
  //Pokretanje B steppera
  while(stepB > 0){
    delay(delayTime);
    switch(Steps){
       case 0:
         digitalWrite(PIN_5, LOW); 
         digitalWrite(PIN_6, HIGH);
         digitalWrite(PIN_7, HIGH);
         digitalWrite(PIN_8, HIGH);
       break; 
       case 1:
         digitalWrite(PIN_5, LOW); 
         digitalWrite(PIN_6, LOW);
         digitalWrite(PIN_7, HIGH);
         digitalWrite(PIN_8, HIGH);
       break; 
       case 2:
         digitalWrite(PIN_5, HIGH); 
         digitalWrite(PIN_6, LOW);
         digitalWrite(PIN_7, HIGH);
         digitalWrite(PIN_8, HIGH);
       break; 
       case 3:
         digitalWrite(PIN_5, HIGH); 
         digitalWrite(PIN_6, LOW);
         digitalWrite(PIN_7, LOW);
         digitalWrite(PIN_8, HIGH);
       break; 
       case 4:
         digitalWrite(PIN_5, HIGH); 
         digitalWrite(PIN_6, HIGH);
         digitalWrite(PIN_7, LOW);
         digitalWrite(PIN_8, HIGH);
       break; 
       case 5:
         digitalWrite(PIN_5, HIGH); 
         digitalWrite(PIN_6, HIGH);
         digitalWrite(PIN_7, LOW);
         digitalWrite(PIN_8, LOW);
       break; 
         case 6:
         digitalWrite(PIN_5, HIGH); 
         digitalWrite(PIN_6, HIGH);
         digitalWrite(PIN_7, HIGH);
         digitalWrite(PIN_8, LOW);
       break; 
       case 7:
         digitalWrite(PIN_5, LOW); 
         digitalWrite(PIN_6, HIGH);
         digitalWrite(PIN_7, HIGH);
         digitalWrite(PIN_8, LOW);
       break; 
       default:
         digitalWrite(PIN_5, LOW); 
         digitalWrite(PIN_6, LOW);
         digitalWrite(PIN_7, LOW);
         digitalWrite(PIN_8, LOW);
       break; 
    }
    dirSet(dirA,dirB);
    stepB--;
  }
}

//Promjena trenutnog koraka, i smjera okretanja
void dirSet(int dirA, int dirB){
  if(dirA == 2){ Steps1++;}
  if(dirA == 1){ Steps1--; }
  if(Steps1>7){Steps1=0;}
  if(Steps1<0){Steps1=7; }
  if(dirB == 2){ Steps++;}
  if(dirB == 1){ Steps--; }
  if(Steps>7){Steps=0;}
  if(Steps<0){Steps=7; }
}
