import processing.core.*; 
import processing.xml.*; 

import java.applet.*; 
import java.awt.Dimension; 
import java.awt.Frame; 
import java.awt.event.MouseEvent; 
import java.awt.event.KeyEvent; 
import java.awt.event.FocusEvent; 
import java.awt.Image; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class GenerateTextPaths extends PApplet {

//program to add arraypoints to a file 15 times a second

int[][] x_array_points = new int[21][1000];
int[][] y_array_points = new int[21][1000];

int line_num = 0;
int counter = 0;

int numLines = 0;
int startLine = 0;
boolean CircleA = true;

String file_name = "";

boolean record = false; 
String position_string = ""; 

int x;
int y;
int prev_x = 0;
int prev_y = 0;
PFont print_font; 
PImage bgCircles;

String[][] lines = new String[20][1000];


public void setup() {
  size(512,768);
  //size for calibration in the dome
  //size(1400,1050);
  //size(800,800);
  background(0);
  frameRate(30);

  print_font = loadFont("ArialMS-48.vlw");
  textFont(print_font, 12); 
  
  bgCircles = loadImage("AudioCircles.png");
  image(bgCircles,0,0,512,768);
  
}


public void draw() {

   fill(100,100,100);
   rect(3,10,180,110);
   fill(255);
   text("Current Line = " + numLines,5,26);
   if(CircleA) {
     text("Output circle A",5,46);
   } else {
      text("Output circle B",5,46);
   }
   
   text("Press 'r' to start recording \n Press 's' to save recording \n Press + - to choose line number \n press 'c' to change circles", 5,66);
   
   
   text("CIRCLE A",width/2,height/3);
   text("CIRCLE B",width/2,height*.75f);
  
  
  
  if (record) {

    x = mouseX;
    y = mouseY;

    if(counter == 0) {
      
      text(file_name, x,y); 
      set_new_fill();
    }

    //if enough space has passed between the last record
    if(dist(x,y,prev_x,prev_y) > 10) {

      //record the points into the array
      x_array_points[line_num][counter] = x;
      y_array_points[line_num][counter] = convert_y(y);
      if(counter > 1) {
        line( x_array_points[line_num][counter-1], convert_y(y_array_points[line_num][counter-1]),
        x_array_points[line_num][counter], convert_y(y_array_points[line_num][counter]));
      }
      prev_x = x;
      prev_y = y;
      counter++;
    }
  }
  
  
  
}


public void set_new_fill() {
  int line_color_red = 255 * (line_num/20) + (int)random(100);
  int line_color_green = 255 * (line_num/20) + (int)random(100);
  int line_color_blue = 255 * (line_num/20) + (int)random(100);            
  stroke(line_color_red, line_color_green, line_color_blue);
  fill(line_color_red, line_color_green, line_color_blue);
}


//this function is here because OPEN GL uses a different coordinate system than processing
//lower left vs. upper left for 0,0  
//changed back for OpenFrameworks. 

public int convert_y(int y) {
 // int new_y = height - y;
 int new_y = y;
  return new_y; 
}

public void load_previous_paths() {
  
  lines[0] = loadStrings("list.txt"); 
  println("there are " + lines.length + " lines"); 
  for (int i=0; i < lines.length; i++) { 
    println(lines[i]); 
  } 
}


public void output_path_file(int line_num) {
  //reset the position string to empty. ug....
  position_string = "";
  for(int i=0; i<counter; i++) {
    position_string += Float.toString((float)x_array_points[line_num][i]/(float)width);
    position_string += ",";
    position_string += Float.toString((float)y_array_points[line_num][i]/(float)height);
    position_string += " ";
  } 
  String position_list[] = splitTokens(position_string);
  String add_char = "";
  if(line_num < 10) {
    add_char = "0";
  }
  String folderAB = "";
  if(CircleA) {
    folderAB = "circleA/";
  } else {
    folderAB = "circleB/";
  }
  
  saveStrings("data/" + folderAB + file_name, position_list);
  println("output file: " + line_num + " to processing folder");
}

public void keyPressed() {

  //record
  if(key == 'r') {
    line_num = numLines;
    file_name = numLines + ".txt";
    record = true;
  } 
  
  if(key == '=') {
    numLines++;
  }
  
  if(key == '-') {
    numLines--;
  }
  
  if(key == 'c') {
    CircleA = !CircleA;
  }

  //load into a file
  if(key == 's') {
    output_path_file(numLines);
    record = false;
    counter = 0; 
    numLines++;
  }
}

  static public void main(String args[]) {
    PApplet.main(new String[] { "--bgcolor=#C0C0C0", "GenerateTextPaths" });
  }
}
