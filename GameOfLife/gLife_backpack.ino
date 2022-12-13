
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
/*
	Connect + to 5v
	Connect - to GND
	Connect SCL/C to Analog 5
	Connect SDA/D to Analog 4
	Install the GFX and LEDBackpack libraries
*/
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
 volatile int n=0;
 volatile int gen=0;
  bool states[6][10][10]={{
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
	},
	{
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
	},
	//state3
	{
  	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  	{0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
  	{0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
  	{0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
  	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
  	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
  	{0, 1, 0, 1, 0, 0, 1, 0, 0, 0},
  	{0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
  	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
  	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  	},
  	//state4
  	{
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
    	{0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
    	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	},
 	//state5
 	{
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
    	{0, 1, 1, 0, 0, 0, 0, 1, 0, 0},
    	{0, 1, 0, 0, 1, 1, 1, 0, 1, 0},
    	{0, 0, 0, 1, 1, 0, 1, 0, 0, 0},
    	{0, 1, 0, 0, 0, 1, 1, 0, 0, 0},
    	{0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
    	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    	{0, 1, 0, 1, 1, 0, 1, 1, 1, 0},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	},
	//state6
	{
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
    	{0, 1, 0, 0, 1, 1, 1, 0, 1, 0},
    	{0, 1, 0, 1, 1, 0, 1, 0, 1, 0},
    	{0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
    	{0, 1, 0, 1, 1, 1, 0, 0, 1, 0},
    	{0, 1, 1, 0, 0, 0, 0, 0, 1, 0},
    	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	}
	};
void setup() {
  Serial.begin(9600);
  matrix.begin(0x70);  // pass in the address
}

void loop() {
  // put your main code here, to run repeatedly:
  if(gen>9){
	n++;
	gen=0;
  	}
  	if(n<6){
  		displayGrid(states[n]);
  		evaluateGrid(states[n]);
  		matrix.clear();}
  else{
    	matrix.setTextSize(1);
    	matrix.setTextWrap(false);
    	matrix.setTextColor(LED_ON);

    	for (int8_t x=0; x>=-36; x--) {
      	matrix.clear();
      	matrix.setCursor(x,0);
      	matrix.print("The");
      	matrix.writeDisplay();
      	delay(100);
    		}
  	for (int8_t x=7; x>=-36; x--) {
      	matrix.clear();
      	matrix.setCursor(x,0);
      	matrix.print("End!");
      	matrix.writeDisplay();
      	delay(100);
    		}
	}

}

//code that displays the grid on the matrix
void displayGrid(bool gridOne[10][10]){
  for(int m=1;m<9;m++){
	for(int n=1;n<9;n++){
      	if(gridOne[m][n]==true){
        		//light the respective led
        		matrix.drawPixel(m-1, n-1, 1);
        		matrix.writeDisplay();
        		//Serial.print(" 0 ");
        	if(n==8){
          		//Serial.print("\n");
          	}      	 
      	}
      	else{
        		//do nothing
        		//Serial.print(" . ");
        	if(n==8){
          		//Serial.print("\n");
        			}
     			}   	 
  		}
	}
  gen++;
  }
//transfers the a grid onto another grid
 void copyGrid(bool gridOne[10][10], bool gridTwo[10][10]){
	for(int m=0;m<9;m++){
  	for(int n=0; n<9;n++){
      	gridTwo[m][n]=gridOne[m][n];
    	}
  	}
  }
//does the logic that goes into determining which
//cell proceeds to the next cycle as alive or dead
void evaluateGrid(bool gridOne[10][10]){
	bool gridTwo[10][10]={};
	copyGrid(gridOne,gridTwo);
	//first two outer loops to access individual cells
	//two inner loops to compare the state
	for(int j=1;j<9;j++){
  		for(int k=1;k<9;k++){
    			int neighbours=0;
   			//takes count of the live neighbours 
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

