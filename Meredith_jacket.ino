#include <Adafruit_NeoPixel.h>
#define LED_PIN 6
#define LED_COUNT 110
#define POT A0
#define LEFT 3
#define RIGHT 2
#define CONTROL 4

int mode = 0;
int numberofmodes = 4;

bool canmove = 1;

String message[4] = {"i love meredith", "stay hydrated", "tell your friends you love them", "i made this patch myself and i am quite proud of it"};
int messagenumber = 0;

unsigned long lastdb = 0;
unsigned long dbdelay = 200;

bool isthereanapple = 0;
int applex = 0;
int appley = 0;
int snakex = 5;
int snakey = 3;
int snakedirection = 0;
int snakelength = 5;
int delaytime = 200;

int drawingx = 0;
int drawingy = 0;

int animationindex = 0;

const bool alphabet[27][5][5] PROGMEM = 
{
	{
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1}
	},

	{
		{1, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 0}
	},

	{
		{0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0},
		{0, 1, 1, 1, 1}
	},

	{
		{1, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 0}
	},

	{
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0},
		{1, 1, 1, 1, 0},
		{1, 0, 0, 0, 0},
		{1, 1, 1, 1, 1}
	},

	{
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0},
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0}
	},

	{
		{0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 1, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 1}
	},

	{
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1}
	},

	{
		{0, 1, 1, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 1, 1, 0}
	},

	{
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 0}
	},

	{
		{1, 0, 0, 0, 1},
		{1, 0, 0, 1, 0},
		{1, 1, 1, 0, 0},
		{1, 0, 0, 1, 0},
		{1, 0, 0, 0, 1}
	},

	{
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0},
		{1, 1, 1, 1, 1}
	},

	{
		{0, 1, 0, 1, 0},
		{1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1}
	},

	{
		{1, 0, 0, 0, 1},
		{1, 1, 0, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 0, 1, 1},
		{1, 0, 0, 0, 1}
	},

	{
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 0}
	},

	{
		{1, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 0},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0}
	},

	{
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 1, 0},
		{0, 1, 1, 0, 1}
	},

	{
		{1, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 0},
		{1, 0, 0, 1, 0},
		{1, 0, 0, 0, 1}
	},

	{
		{0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 0, 0, 0, 1},
		{1, 1, 1, 1, 0}
	},

	{
		{1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},

	{
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 0}
	},

	{
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0},
		{0, 0, 1, 0, 0}
	},

	{
		{1, 0, 0, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1},
		{0, 1, 0, 1, 0}
	},

	{
		{1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 0, 1, 0},
		{1, 0, 0, 0, 1}
	},

	{
		{1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},

	{
		{1, 1, 1, 1, 1},
		{0, 0, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 0, 0, 0},
		{1, 1, 1, 1, 1}
	},

    {
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	}
	
};


int myPixels[10][11] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int myDrawing[10][11] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const int myAnimations[4][10][11] PROGMEM = {
{
{0, 0, 3, 3, 0, 0, 0, 3, 3, 0, 0},
{0, 3, 2, 2, 3, 0, 3, 2, 2, 3, 0},
{3, 2, 1, 1, 2, 3, 2, 1, 1, 2, 3},
{3, 2, 1, 1, 1, 2, 1, 1, 1, 2, 3},
{3, 2, 1, 1, 1, 2, 1, 1, 1, 2, 3},
{0, 3, 2, 1, 1, 1, 1, 1, 2, 3, 0},
{0, 0, 3, 2, 1, 1, 1, 2, 3, 0, 0},
{0, 0, 0, 3, 2, 1, 2, 3, 0, 0, 0},
{0, 0, 0, 0, 3, 2, 3, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0}
},

{
{0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0},
{0, 0, 4, 0, 0, 1, 0, 0, 4, 0, 0},
{0, 4, 0, 0, 1, 0, 1, 0, 0, 4, 0},
{4, 0, 0, 1, 0, 0, 0, 1, 0, 0, 4},
{0, 0, 1, 0, 0, 2, 0, 0, 1, 0, 0},
{0, 1, 0, 0, 2, 0, 2, 0, 0, 1, 0},
{1, 0, 0, 2, 0, 0, 0, 2, 0, 0, 1},
{0, 0, 2, 0, 0, 3, 0, 0, 2, 0, 0},
{0, 2, 0, 0, 3, 0, 3, 0, 0, 2, 0},
{2, 0, 0, 3, 0, 0, 0, 3, 0, 0, 2}
},

{
{0, 0, 4, 0, 0, 2, 0, 0, 4, 0, 0},
{0, 4, 3, 0, 0, 1, 0, 0, 3, 4, 0},
{0, 0, 0, 3, 3, 0, 3, 3, 0, 0, 0},
{2, 0, 0, 3, 3, 2, 3, 3, 0, 0, 2},
{0, 1, 4, 4, 2, 1, 2, 4, 4, 1, 0},
{0, 1, 4, 4, 2, 1, 2, 4, 4, 1, 0},
{2, 0, 0, 3, 3, 2, 3, 3, 0, 0, 2},
{0, 0, 0, 3, 3, 0, 3, 3, 0, 0, 0},
{0, 4, 3, 0, 0, 1, 0, 0, 3, 4, 0},
{0, 0, 4, 0, 0, 2, 0, 0, 4, 0, 0}
},

{
{0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 0},
{0, 1, 0, 0, 3, 0, 1, 2, 0, 0, 0},
{2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2},
{0, 0, 4, 0, 2, 0, 4, 0, 0, 4, 0},
{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 1, 4, 0, 0, 0, 0, 2, 0},
{0, 3, 0, 0, 0, 0, 1, 0, 0, 4, 0},
{0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0},
{2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0},
{0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 3}
}
};


int myFlag[10][11] = {
{0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0},
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
{0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
{0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0},
{0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0},
{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}
};

// just make this an alogrithm

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

uint32_t colour1 = strip.Color(50, 0, 200);
uint32_t colour2 = strip.Color(100, 0, 150);
uint32_t colour3 = strip.Color(150, 0, 100);
uint32_t colour4 = strip.Color(0, 0, 0);

uint32_t animationcolours[4] = {colour1, colour2, colour3, colour4};

uint32_t tblue = strip.Color(91, 50, 250);
uint32_t tpink = strip.Color(245, 50, 184);
uint32_t twhite = strip.Color(200, 200, 200);

uint32_t flagcolours[3] = {tblue, tpink, twhite};

////////////////////////////////////////////////

void setup() {
  randomSeed(analogRead(5));
 strip.begin(); //always needed
 strip.show(); // 0 data => off.
 strip.setBrightness(100); // ~20% (max = 255)
 Serial.begin(9600);
 pinMode(POT, INPUT);
 pinMode(LEFT, INPUT_PULLUP);
 pinMode(RIGHT, INPUT_PULLUP);
 pinMode(CONTROL, INPUT_PULLUP);
 
attachInterrupt(digitalPinToInterrupt(LEFT), leftclick, FALLING);
attachInterrupt(digitalPinToInterrupt(RIGHT), rightclick, FALLING);

placeasnake();

}

////////////////////////////////////////////////////////

int writemessage(String message) 
{
	int sl = message.length();
	int l = sl * 6 + 11;
	
	for(int s = 0; s < l; s++)
	{
		strip.clear();
		
		uint32_t saver = animationcolours[0];

    for(int i = 0; i < 2; i++)
    {
    	animationcolours[i] = animationcolours[i+1];
    }

    animationcolours[2] = saver;
	
		for(int n = 0; n < sl; n++)
		{
			int offset = n * 6 + 10 - s;
			int letter = (int) message[n] - 97;
            if (letter == -65)
            {
                letter = 26;
            }

for(int i = 0; i < 5; i++)
{
	for(int j = 0; j < 5; j++)
	{
		if((j+offset) < 11 && (j+offset) >-1)
		{
			 bool pixel = pgm_read_byte(&alphabet[letter][i][j]);
			 if(pixel >  0)
			 {
			 	 if((j+offset) % 2 == 0)
			 	 {
			 	 	strip.setPixelColor(10*(j+offset)+9-(i+2), animationcolours[0]);}
			  		else
			  		{	
			  			strip.setPixelColor((10*(j+offset))+(i+2), animationcolours[0]);}
			 		}
				}
			}
		}
	}
	strip.show();
	delay(80);			
}
messagenumber++;
if (messagenumber == 4)
{
  messagenumber = 0;
}
}

/////////////////////////////////

void placeasnake()
{

snakex = 5;
snakey = 3;
snakedirection = 0;
snakelength = 6;
delaytime = 200;


for(int i = 0; i < snakelength; i++)
{myPixels[snakey+i][snakex] = i+1;}

if(isthereanapple == 0)
{placeanapple();}

updategridsnake();

delay(1000);

}

////////////////////////////////////////////////

void placeanapple()

{

delaytime = delaytime - 10;
if(delaytime < 50)
{delaytime = 50;}

do {

isthereanapple = 0;

applex = random(10);
appley = random(9);

if(myPixels[applex][appley]==0)
{myPixels[applex][appley] = -1;
isthereanapple = 1;
}
} while (isthereanapple == 0);
  
}

////////////////////////////////////////////////

void leftclick() {

if((millis() - lastdb) > dbdelay)

{
lastdb = millis();
canmove = 0;

if(digitalRead(CONTROL) == 0)
{mode--;
if(mode < 0)
{mode = 3;}
  
switch(mode)
{
  case 0:
  for(int i = 0; i < 10; i++)
{for(int j = 0; j < 11; j++)
  {
myPixels[i][j] = 0;
isthereanapple = 0;
  }}
  placeasnake();
  break;
  
  case 3:
  
  for(int i = 0; i < 10; i++)
{for(int j = 0; j < 11; j++)
  {
myDrawing[i][j] = 0;
  }}
  break;
}
  
}
else
{switch(mode)
{

case 0:
snakedirection--;
if(snakedirection < 0)
{snakedirection = 3;}
break;

case 2:
messagenumber--;
if(messagenumber < 0)
{
    messagenumber = 3;
}
break;

case 1:
animationindex--;
if(animationindex < 0)
{
    animationindex = 4;
}
break;

case 3:

myDrawing[drawingy][drawingx] = 1;

drawingx++;
if(drawingx > 10)
{
    drawingx = 0;
    drawingy++;
    if(drawingy > 9)
    {
        drawingy = 0;
    }
}

break;

}}}}

////////////////////////////////////////////////

void rightclick() {

if((millis() - lastdb) > dbdelay)

{
lastdb = millis();
canmove = 0;

if(digitalRead(CONTROL) == 0)
{mode = mode + 1;
if(mode ==  numberofmodes)
{mode = 0;}
  
switch(mode)
{
  case 0:
  for(int i = 0; i < 10; i++)
{for(int j = 0; j < 11; j++)
  {
myPixels[i][j] = 0;
isthereanapple = 0;
  }}
  placeasnake();
  break;
  
  case 3:
  
  for(int i = 0; i < 10; i++)
{for(int j = 0; j < 11; j++)
  {
myDrawing[i][j] = 0;
  }}
  
  break;
}  
  
}
else
{switch(mode)
{

case 0:
snakedirection++;
if(snakedirection > 3)
{snakedirection = 0;}
break;

case 2:
messagenumber++;
if(messagenumber == 4)
{
    messagenumber = 0;
}
break;

case 1:
animationindex++;
if(animationindex == 5)
{
    animationindex = 0;
}
break;

case 3:

myDrawing[drawingy][drawingx] = 0;

drawingx++;
if(drawingx > 10)
{
    drawingx = 0;
    drawingy++;
    if(drawingy > 9)
    {
        drawingy = 0;
    }
}

break;

}}}}

////////////////////////////////////////////////

void snakestep() {

//moves the coordinates of snake head

switch(snakedirection)
{
case 0:
snakey = snakey - 1;
if(snakey < 0)
{snakey = 9;}
break;

case 1:
snakex = snakex + 1;
if(snakex > 10)
{snakex = 0;}
break;

case 2:
snakey = snakey + 1;
if(snakey > 9)
{snakey = 0;}
break;

case 3:
snakex = snakex - 1;
if(snakex < 0)
{snakex = 10;}
break;
}

//draws the tail of the snake
  
for(int i = 0; i < 10; i++)
{for(int j = 0; j < 11; j++)
{if(myPixels[i][j]>0)
{myPixels[i][j] = myPixels[i][j] + 1;
if(myPixels[i][j] > snakelength)
{if(myPixels[snakey][snakex] == -1)
{snakelength = snakelength + 1;
placeanapple();
}
else
{myPixels[i][j] = 0;}}
}
}}

if(myPixels[snakey][snakex] > 1)
{
gameover();
placeasnake();
}

//makes the snake head 1

myPixels[snakey][snakex] = 1;

canmove = 1;
  
}

////////////////////////////////////////////////

void updategridsnake() {

strip.clear();
for(int i = 0; i < 10; i++)
{for(int j = 0; j < 11; j++)
  {
  if(myPixels[i][j] > 0)  
  {if(j % 2 == 0)
  {strip.setPixelColor(10*j+9-i, 255-myPixels[i][j]*(255/snakelength), 0, myPixels[i][j]*(255/snakelength));}
  else
  {strip.setPixelColor((10*j)+i, 255-myPixels[i][j]*(255/snakelength), 0, myPixels[i][j]*(255/snakelength));}}
  
  if(myPixels[i][j] == -1)  
  {if(j % 2 == 0)
  {strip.setPixelColor(10*j+9-i, 0, 255, 0);}
  else
  {strip.setPixelColor((10*j)+i, 0, 255, 0);}}
    
  }}

strip.show();
delay(delaytime);

}

///////////////////////////////////////////

void drawing() {

uint32_t saver = animationcolours[0];

for(int i = 0; i < 3; i++)
{
	animationcolours[i] = animationcolours[i+1];
}

animationcolours[2] = saver;

strip.clear();
for(int i = 0; i < 10; i++)
{for(int j = 0; j < 11; j++)
  {
  if(myDrawing[i][j] > 0)
  {
  if(j % 2 == 0)
  {strip.setPixelColor(10*j+9-i, animationcolours[0]);}
  else
  {strip.setPixelColor((10*j)+i, animationcolours[0]);}
  }
}	
}

if(drawingx % 2 == 0)
  {strip.setPixelColor(10*drawingx+9-drawingy, 0, 250, 0);}
  else
  {strip.setPixelColor((10*drawingx)+drawingy, 0, 250, 0);}

strip.show();
delay(200);

}

void animation(int animationnumber) {

uint32_t saver = animationcolours[0];

for(int i = 0; i < 4; i++)
{
	animationcolours[i] = animationcolours[i+1];
}

animationcolours[3] = saver;

strip.clear();
for(int i = 0; i < 10; i++)
{for(int j = 0; j < 11; j++)
  {
  int pixel = pgm_read_word_near(&(myAnimations[animationnumber][i][j]));
  if(pixel > 0)
  {
  if(j % 2 == 0)
  {strip.setPixelColor(10*j+9-i, animationcolours[pixel-1]);}
  else
  {strip.setPixelColor((10*j)+i, animationcolours[pixel-1]);}
  }
}	
}

strip.show();
delay(200);

}

///////////////////////////////////////////

void updategridflag() {

strip.clear();

for(int i = 0; i < 10; i++)
{for(int j = 0; j < 11; j++)
  {
  if(myFlag[i][j] >  0)
  {if(j % 2 == 0)
  {strip.setPixelColor(10*j+9-i, flagcolours[myFlag[i][j]-1]);}
  else
  {strip.setPixelColor((10*j)+i, flagcolours[myFlag[i][j]-1]);}
  }
}
}

strip.show();
delay(200);

}

///////////////////////////////////////////


void gameover() {

for(int i = 0; i < 10; i++)
{for(int j = 0; j < 11; j++)
  {
myPixels[i][j] = 0;
isthereanapple = 0;
  }}


strip.clear();

writemessage("game over");

delay(100);

}

///////////////////////////////////////////


void loop() {

switch(mode)
{
case 0:  
snakestep();
updategridsnake();
break;

case 2:

writemessage(message[messagenumber]);

break;

case 1:
if(animationindex == 4)
{
    updategridflag();
}
else
{
    animation(animationindex);
}
break;

case 3:
drawing();
break;

}

// move this to each function 
}



