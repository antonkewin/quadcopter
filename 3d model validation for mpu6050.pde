import processing.serial.*; //import the Serial library

int end = 10;    // the number 10 is ASCII for linefeed (end of serial.println), later we will look for this to break up individual messages
String serial;   // declare a new string called 'serial' . A string is a sequence of characters (data type know as "char")
Serial port;
float roll,pitch;// The serial port, this is a new instance of the Serial class (an Object)

void setup() {
  port = new Serial(this, Serial.list()[0], 115200); // initializing the object by assigning a port and baud rate (must match that of Arduino)
  port.clear();  // function from serial library that throws out the first reading, in case we started reading in the middle of a string from Arduino
  serial = port.readStringUntil(end); // function that reads the string from serial port until a println and then assigns string to our string variable (called 'serial')
  serial = null; // initially, the string will be null (empty)
  size(600,600,P3D);
}

void draw() {
  while (port.available() > 0) { //as long as there is data coming from serial port, read it and store it 
    serial = port.readStringUntil(end);
  }
    if (serial != null) {  //if the string is not empty, print the following
    
    /*  Note: the split function used below is not necessary if sending only a single variable. However, it is useful for parsing (separating) messages when
        reading from multiple inputs in Arduino. Below is example code for an Arduino sketch
    */
  
     String[] a = split(serial, ',');  //a new array (called 'a') that stores values into separate cells (separated by commas specified in your Arduino program)
      //println(a[0]); //print Value1 (in cell 1 of Array - remember that arrays are zero-indexed)
      //println(a[1]); //print Value2 value
      roll=float(a[0]);
      pitch=float(a[1]);
    
  }
  background(0);
  translate(width/2,height/2);
  fill(255,0,0);
  rotateX(radians(-roll));
  rotateZ(radians(pitch));
  box(300,50,300);//box(w, h, d)
}