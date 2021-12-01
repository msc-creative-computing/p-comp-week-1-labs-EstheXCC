import processing.serial.*;
PImage bg;
int val = 0;
int cols, rows;
int scl = 50;
int h = 2400;
int w = 2400;
float rotate = 0;
boolean rite = true;
Serial port = new Serial(this, "COM3", 9600);
float flying,flying2;

float[][] terrain,terrain2;

void setup() {
  size(1000, 659, P3D);
  cols = w / scl;
  rows = h / scl;
  terrain = new float[cols][rows];
  terrain2 = new float[cols][rows];
 
  port.bufferUntil('\n'); 
}

void draw() {
 
  push();
  flying -= 0.1;
  float yoff = flying;
   for (int y = 0; y < rows; y++) {
    float xoff = 0;
     for (int x = 0; x < cols; x++) {
       terrain[x][y] = map(noise(xoff, yoff), 0, 1, -val, val); 
       xoff += 0.07;
     }
     yoff += 0.1;
  }

 stroke(255);
 noFill();
 background(0);
 
 translate(width/2, height/2);
 rotateX(PI/3);
 //rotateZ(rotate);
 translate(-w/2, -h/2);
 rotate+= 0.01;
 
 for (int y = 0; y < rows-1; y++) {
   if(rite) {
   beginShape(TRIANGLE_STRIP);
   }
   for (int x = 0; x < cols; x++) {
     vertex(x*scl,y*scl, terrain[x][y]);
     vertex(x*scl,(y+1)*scl, terrain[x][y+1]);
   }
   endShape();
 }
 
 pop();
  
}

 
  void serialEvent(Serial p) {
   
 
    
  String inString = p.readString();
  if(!inString.equals("")){
 
      
  
  String temp = inString.replace("\n","").trim();
 
  if(temp.length()>1&&temp.length()<9){
   println(temp);
   val = Integer.parseInt(temp);
  }

 
}
  
  }
 
 
