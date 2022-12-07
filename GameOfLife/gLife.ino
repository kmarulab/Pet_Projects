#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
// Works on the Generic MAX7219 8x8 LED Matrix
//runs on the Arduino Uno R3
LedControl lc=LedControl(12,11,10,1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //while(!Serial);
    /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  
  bool gridOne[10][10]={};
  bool octagon[10][10]=    {
        //octagon
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
  bool mold[10][10]=    {
        //mold
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    
    while(true){
      displayGrid(mold);
      evaluateGrid(mold);
      Serial.println("\t\t\t\tNew Generation");
      delay(500);
      lc.clearDisplay(0);
    }
      
}

void loop() {
  // put your main code here, to run repeatedly:

}

void displayGrid(bool gridOne[10][10]){
  for(int m=1;m<9;m++){
    for(int n=1;n<9;n++){
          if(gridOne[m][n]==true){
            //light the respective led
            lc.setLed(0, m-1, n-1, 1);
            Serial.print(" 0 ");
            if(n==8){
              Serial.print("\n");
              }           
          }
          else{
            //do nothing
            Serial.print(" . ");
            if(n==8){
              Serial.print("\n");
            }
         }        
      }
    }
  }

 void copyGrid(bool gridOne[10][10], bool gridTwo[10][10]){
    for(int m=0;m<9;m++){
      for(int n=0; n<9;n++){
          gridTwo[m][n]=gridOne[m][n];
        }
      }
  }

void evaluateGrid(bool gridOne[10][10]){
    bool gridTwo[10][10]={};
    copyGrid(gridOne,gridTwo);
    //first two outer loops to access individual cells
    //two inner loops to compare the state
    for(int j=1;j<9;j++){
      for(int k=1;k<9;k++){
        int neighbours=0;
        
        for(int a=-1;a<2;a++){
          for(int b=-1;b<2;b++){
            if(!(a==0 && b==0)){
              if(gridTwo[j+a][k+b]){
                ++neighbours;
                }
              }
            }
          }

          if(neighbours<2){
            gridOne[j][k]=false;
            }
          else if(neighbours==3){
            gridOne[j][k]= true;
            }
           else if(neighbours>3){
            gridOne[j][k]= false;
            }
        }
      }
    }
