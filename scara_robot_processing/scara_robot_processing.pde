import processing.serial.*;
import g4p_controls.*;

float cursorX, cursorY;
float cursorSize = 2;
PVector a, b, aE, bE;
float len1 = 80;
float len2 = 90;
float x, y;
float A1, A2;
float degStep = 0.00000000;
int cnt = 0;
int stepsAng1, stepsAng2, lastStepsAng1, lastStepsAng2, stepsAng1a, stepsAng2a;
public boolean sendData = false;
public boolean connected = false;
String portName;

Serial port;

void setup(){
  A1 = HALF_PI;
  A2 = PI;
  cursorX = width/2;
  cursorY = height/2 - len1-len2+10;
  degStep = 360/4096;
  size(720, 480, JAVA2D);
  createGUI();
  customGUI();
  background(255);
  //IF THE APP DOESNT WORK, SET THE "0" TO ANOTHER NUMBER AND TEST AGAIN! IT DETERMINES THE SERIAL PORT ON YOUR COMPUTER
  dropList1.setItems(Serial.list(), 1);
  /*
  for(int i = 0;i < Serial.list().length;i++){
    dropList1.insertItem(i, Serial.list()[i]);
  }
  */
  println(Serial.list().length);
  
  
  a = new PVector(width/2, height/2);
  b = new PVector();
  aE = new PVector();
  bE = new PVector();
  delay(1000);
  
}

public void customGUI(){

}

public void connect(){
  portName = Serial.list()[dropList1.getSelectedIndex()];
  port = new Serial(this, portName, 115200);
  connected = true;
  println("SERIAL PORT CONNECTED");
}

void draw(){
  x = mouseX - (width/2);
  y = (height/2) - mouseY;
  angles(cursorX - (width/2),(height/2) - cursorY);
  stroke(200);
  fill(200);
  ellipse(width/2, height/2, 2*(len1+len2+5), 2*(len1+len2+5));
  stroke(255);
  strokeWeight(6);
  line(a.x, a.y, aE.x, aE.y);
  line(b.x, b.y, bE.x, bE.y);
  calculateEndpoints();
  stroke(0);   
  strokeWeight(4);
  line(a.x, a.y, aE.x, aE.y);
  line(b.x, b.y, bE.x, bE.y);
  stroke(0);
  strokeWeight(2);
  ellipse(cursorX, cursorY, cursorSize, cursorSize);
  if(sendData == true){
    calcSteps();
    sendSteps(stepsAng1, stepsAng2);
    sendData = false;
  }
}

public void moveCursor(float xC, float yC){
  cursorX = cursorX + xC;
  cursorY = cursorY + yC;
}

// this part is executed, when serial-data is received
void serialEvent(Serial p) {
  try {
    // get message till line break (ASCII > 13)
    String message = p.readStringUntil(13);
    // just if there is data
    if (message != null) {
      println("message received: "+trim(message));
    }
  }
  catch (Exception e) {
  }
}

float cosineLaw(float aT, float bT, float cT){
  float what = acos(((sq(aT) + sq(bT) - sq(cT)) / (2*aT*bT) ));
  return what;
}

float distance(float xT, float yT){
  return sqrt(sq(xT) + sq(yT));
}

void angles(float xT, float yT){
    float dist = distance(xT, yT);
    float D1 = atan2(yT, xT);
    float D2 = cosineLaw(dist, len1, len2);
    A1 = D1+D2;
    A2 = cosineLaw(len1, len2, dist);
}

void update(int x, int y){

}

void mousePressed() {
}

void calculateEndpoints(){
  float dxa = len1 * cos(-A1);
  float dya = len1 * sin(-A1);
  float dxb = len2 * cos((-A1 + PI) - A2);
  float dyb = len2 * sin((-A1 + PI) - A2);
  aE.set(a.x+dxa, a.y+dya);
  b.set(aE.x, aE.y);
  bE.set(b.x+dxb, b.y+dyb);
}

void calcSteps(){
  lastStepsAng1 = stepsAng1a;
  lastStepsAng2 = stepsAng2a;
  float dA1 = degrees(A1);
  float dA2 = degrees(A2);
  stepsAng1a = round(dA1 * (2048/360));
  stepsAng2a = round(dA2 * (2048/360));
  stepsAng1 = round(dA1 * (2048/360)) - lastStepsAng1;
  stepsAng2 = round(dA2 * (2048/360)) - lastStepsAng2;
  println(stepsAng1, stepsAng2);
  println(dA1, dA2); 
}

public void sendSteps(int stepA, int stepB){
  if(connected){
    if(stepA < 0){
      port.write('a');
      port.write(Integer.toString(abs(stepA)));
    } else if(stepA > 0){
      port.write('b');
      port.write(Integer.toString(abs(stepA)));
    } else{
      port.write('b');
      port.write(Integer.toString(abs(stepA)));
    }
    port.write('e');
    if(stepB < 0){
      port.write('c');
      port.write(Integer.toString(abs(stepB)));
    } else if(stepB > 0){
      port.write('d');
      port.write(Integer.toString(abs(stepB)));
    } else{
      port.write('c');
      port.write(Integer.toString(abs(stepB)));
    }
    port.write('f');
  } else {
    println("SERIAL PORT NOT CONNECTED!");
  }
  
}
