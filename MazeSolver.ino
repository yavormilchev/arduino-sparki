#include <Sparki.h> // include the sparki library

int edgeLeft;
int edgeRight;
int lineLeft;
int lineRight;
int lineCenter;
char* state;
int limit = 900;
boolean seeWall;
boolean seeRight;
boolean seeLeft;

void setup()
{
  sparki.clearLCD();
}

void loop()
{
  state = "OK";
  print_numbers();
  int count = 0;
  if(seeLeft && !seeWall) {
    sparki.moveForward();
    print_numbers();
  } else if(!seeLeft && !seeWall) {
    while(!seeLeft && !seeWall && count < 20) {
      count = count + 1;
      sparki.moveLeft(1);
      print_numbers();
    }
    print_numbers();
    if(!seeLeft) {
      sparki.moveRight(count);
      sparki.moveBackward(0.5);
      count = 0;
      print_numbers();
      while(!seeLeft && !seeWall && count < 20) {
        count = count + 1;
        sparki.moveRight(1);
        print_numbers();
      }
    }
    print_numbers();
    if(!seeLeft && !seeWall) {
      sparki.moveLeft(count);
      // Turn left or around
      state = "turn left";
      print_numbers();
      sparki.moveForward(7.7);
      sparki.moveLeft(90);
      sparki.moveForward(1.5);
      print_numbers();
      if(!seeLeft) {
        state = "turn around";
        print_numbers();
        sparki.moveForward(6.7);
        print_numbers();
        sparki.moveLeft(90);
        print_numbers();
      }
      state = "OK";
      sparki.moveForward();
      print_numbers();
    }
  } 
  else {
    state = "hit wall";
    print_numbers();
    sparki.moveRight(90);
    sparki.moveBackward(3.5);
  }
  
  print_numbers();
}

boolean see_wall(){
  return lineLeft < limit - 300;
}
boolean see_right_edge(){
  return edgeRight < limit;
}
boolean see_left_edge(){
  return edgeLeft < limit;
}
void check_sensors(){
  edgeLeft = sparki.edgeLeft();
  lineLeft = sparki.lineLeft();
  lineRight = sparki.lineRight();
  lineCenter = sparki.lineCenter();
  edgeRight = sparki.edgeRight();
}
void print_numbers() {
  sparki.clearLCD();
  check_sensors();
  seeWall = see_wall();
  seeRight = see_right_edge();
  seeLeft = see_left_edge();
  sparki.print( "Edge left: ");
  sparki.println( edgeLeft );
  sparki.print( "Line left: ");
  sparki.println( lineLeft );
  sparki.print( "Line center: ");
  sparki.println( lineCenter );
  sparki.print( "Line right: ");
  sparki.println( lineRight );
  sparki.print( "Edge right: ");
  sparki.println( edgeRight );
  sparki.print( "State: ");
  sparki.println( state );
  sparki.print( "Vision: ");
  if(seeWall) {
    sparki.print( "wall ");
  }
  if(seeRight) {
    sparki.print( "right ");
  }
  if(seeLeft) {
    sparki.print( "left ");
  }
  sparki.updateLCD();
}

