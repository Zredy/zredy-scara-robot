import processing.serial.*;
import g4p_controls.*;

int rectXA, rectYA, rectXB, rectYB;
int rectSize = 25;
boolean rectOverA = false;
boolean rectOverB = false;
color rectHighlight;
color rectColor;
PVector a, b, aE, bE;
float len1 = 80;
float len2 = 90;
float x, y;
float A1, A2;
float degStep = 0.00000000;
int cnt = 0;
int stepsAng1, stepsAng2;

Serial port;

void setup(){
  degStep = 360/4096;
  size(720, 480, JAVA2D);
  createGUI();
  customGUI();
  rectColor = color(0);
  rectHighlight = color(51);
  background(255);
  rectXA = width/5-(2*rectSize);
  rectYA = height-rectSize*2;
  rectXB = width/5+rectSize;
  rectYB = height-rectSize*2;
  //IF THE APP DOESNT WORK, SET THE "0" TO ANOTHER NUMBER AND TEST AGAIN! IT DETERMINES THE SERIAL PORT ON YOUR COMPUTER
  String portName = Serial.list()[0];
  port = new Serial(this, portName, 115200);
  a = new PVector(width/2, height/2);
  b = new PVector();
  aE = new PVector();
  bE = new PVector();
  delay(1000);
  
}

public void customGUI(){

}

void draw(){
  x = mouseX - (width/2);
  y = (height/2) - mouseY;
  update(mouseX, mouseY);
  
  /*
  if(rectOverA){
    fill(rectHighlight);
  } else {
    fill(rectColor);
  }
  stroke(255);
  rect(rectXA, rectYA, rectSize, rectSize);
  if(rectOverB){
    fill(rectHighlight);
  } else {
    fill(rectColor);
  }
  stroke(255);
  rect(rectXB, rectYB, rectSize, rectSize);
  if(!mousePressed){
    port.write('0');
  }
  */
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
    calcSteps();
    sendSteps(stepsAng1, stepsAng2);
}

void update(int x, int y){
   if( overRect(rectXA, rectYA, rectSize, rectSize) ){
     rectOverA = true;
     rectOverB = false;
   } else if(overRect(rectXB, rectYB, rectSize, rectSize)) {
     rectOverB = true;
     rectOverA = false;
   } else {
     rectOverA = rectOverB = false;
   }
}

void mousePressed() {
  /*
  if(rectOverA){
    sendSteps(-1024, 0);
  } else if(rectOverB){
    sendSteps(1024, 0);
  } else {
    sendSteps(0, 0);
  }
  */
  angles(x,y);
}

boolean overRect(int xT, int yT, int width, int height){
  if(mouseX>= xT && mouseX <= xT+width && mouseY >= yT && mouseY <=yT+height){
    return true;
  } else {
    return false;
  }
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
  float dA1 = degrees(A1);
  float dA2 = degrees(A2);
  stepsAng1 = round(dA1 * (2048/360));
  stepsAng2 = round(dA2 * (2048/360));
  println(stepsAng1, stepsAng2);
  println(dA1, dA2); 
}

public void sendSteps(int stepA, int stepB){
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
}
