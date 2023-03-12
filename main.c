// -----------------------------------------------------------------------------
// C-Skeleton to be used with HAM Library from www.ngine.de
// -----------------------------------------------------------------------------
#include "sprites.h"
#include "gba.h"
#include <stdbool.h>
#define INPUT                      (KEY_MASK & (~REG_KEYS))

// x and y_position will be used to store last position of the moving sprite, used for updating the position of space ship and laser
int x_position = 0;
int y_position = 144;

int time_count; // for time counter on top right of screen

int a; // a holds the variable time_count to be passed into assembly

int laser_counter=0; // for increment of NUMB for lasers

// an array of 20 by 4, to store a maximum of 20 lasers, 0 represents N, 1 represents x_position, 2 represents_y_position
// each laser should move by their own timing, hence each laser will have to have its own position stored at 3
int laser_arr[20][4]; 

// variable to start/stop the game and navigate out of "game over" and "win!"
int start_stop=0; // starts at 0 so that it will be divisible by 2, hence start_screen function below will run first 

// count to count_4 is being used as the y coordinates of the objects falling (alien). 
int count = 0;
int count_1 = -32;
int count_2 = -64;
int count_3 = -96;
int count_4 = -128;

// Level one objects variable, 2D array where 0-4 are x positions and 5 will be from count to count_4
// Global variable as it have to be constantly updated from more than 1 function
int obj_arr[5][6] = {
							{0,16,32,48,64,0},
							{224,192,64,96,112,-32},
							{0,16,32,112,176,-64},
							{32,208,80,96,240,-96},
							{176,192,208,224,160,-128},
							};

// Level Two objects variable, 2D array where 0-5 are x positions and 6 will be from count to count_4
// Global variable as it have to be constantly updated from more than 1 function
int lvl2_obj_arr[5][7] = {
							{48,64,80,96,112,128,0},
							{16,112,128,144,160,176,-32},
							{48,176,192,208,224,240,-64},
							{80,96,112,128,208,224,-96},
							{16,96,112,160,176,224,-128},
							};

void drawSprite(int numb, int N, int x, int y)
{
    // Gift function: displays sprite number numb on screen at position (x,y), as sprite object N
    *(unsigned short *)(0x7000000 + 8*N) = y | 0x2000;
    *(unsigned short *)(0x7000002 + 8*N) = x | 0x4000;
    *(unsigned short *)(0x7000004 + 8*N) = numb*8;
}

void checkbutton(void)
{

    u16 buttons = INPUT;
    
    if ((buttons & KEY_A) == KEY_A)
    {
        buttonA();
    }
    if ((buttons & KEY_START) == KEY_START)
    {
        buttonS();
    }
    if ((buttons & KEY_RIGHT) == KEY_RIGHT)
    {
        buttonR();
    }
    if ((buttons & KEY_LEFT) == KEY_LEFT)
    {
        buttonL();
    }
    if ((buttons & KEY_UP) == KEY_UP)
    {
        buttonU();
    }
    if ((buttons & KEY_DOWN) == KEY_DOWN)
    {
        buttonD();
    }
}

void buttonA(void) //Shoot Laser, each laser will have variables stored in a row in the 2D array.
{	
	laser_counter+=1;	//Increments the laser_counter when button is pressed
	laser_arr[laser_counter][0] = 40+laser_counter; // To be used for NUMB in drawSprites
	laser_arr[laser_counter][1] = x_position; // stores x_position of spaceship into array
	laser_arr[laser_counter][2] = y_position; // stores y_postion of spaceship into array
	laser_arr[laser_counter][3] = 0; // to offset the y_position
	if(laser_counter>10) // initially set at 20, since I wanted to have a maximum of 20 lasers. However, at a value of 20, if the A button is held down, the game jumps to level 2.
	{
		laser_counter = 0;		
	}
}

// Function to draw a black screen on Visual Boy Advance. Used to clear the screen of sprites
void black_screen(void) { 
	int i;
	int j;
	int k=0;
	
	for(i=0;i<240;i+=16) {
		for(j=0;j<160;j+=16) {
			drawSprite(19,100+k,i,j); // Black Box
			k +=1;
		}
	}
}

// Draws the sprite for menu screen
void start_screen(void) {
	if(start_stop%2 == 0) { //if start_stop variable is divisable by 2, the game is being played and hence this sprites will not be drawn. 

	drawSprite(1,51,100,120); //ST
	drawSprite(2,52,116,120);//AR
	drawSprite(3,53,132,120); //T 
	drawSprite(5,55,80,48); //menu S
	drawSprite(6,56,96,48); //P  
	drawSprite(7,57,112,48); //A   
	drawSprite(8,58,128,48); //C 
	drawSprite(9,59,144,48);//E 
	drawSprite(10,60,56,70); //E 
	drawSprite(11,61,72,70); //X 
	drawSprite(12,62,88,70); //P
	drawSprite(13,63,104,70); //L	
	drawSprite(14,64,120,70); //O 
	drawSprite(15,65,136,70); //R
	drawSprite(16,66,152,70); //E
	drawSprite(17,67,168,70); //R
	drawSprite(20,68,100,100); //PR
	drawSprite(21,69,116,100); //ES
	drawSprite(22,70,132,100); //S
	}
}
// Shift menu screen sprites out of screen
void out_screen(void) {

	drawSprite(1,51,-16,-16); //ST
	drawSprite(2,52,-16,-16);//AR
	drawSprite(3,53,-16,-16); //T 
	drawSprite(5,55,-16,-16); //menu S
	drawSprite(6,56,-16,-16); //P  
	drawSprite(7,57,-16,-16); //A   
	drawSprite(8,58,-16,-16); //C 
	drawSprite(9,59,-16,-16);//E 
	drawSprite(10,60,-16,-16); //E 
	drawSprite(11,61,-16,-16); //X 
	drawSprite(12,62,-16,-16); //P
	drawSprite(13,63,-16,-16); //L	
	drawSprite(14,64,-16,-16); //O 
	drawSprite(15,65,-16,-16); //R
	drawSprite(16,66,-16,-16); //E
	drawSprite(17,67,-16,-16);//R
	drawSprite(20,68,-16,-16); //PR
	drawSprite(21,69,-16,-16); //ES
	drawSprite(22,70,-16,-16); //S 
}

void buttonS(void) // Start Game, goes to menu screen or end game
{
	 start_stop += 1; // Increments start_stop variable when buttonS is pressed
	 int i;
	 int j;

	 if (start_stop%2 == 1) //when start_stop is pressed, timer 0,1,3 will start and the game will run
	 {
	 	REG_TM1D = 1433; // for obj to fall every 1 second interval
	 	REG_TM1CNT = TIMER_FREQUENCY_256|TIMER_ENABLE|TIMER_INTERRUPTS;
	
   	REG_TM0D =	56763; // set for screen to be displayed at 30fps
    	REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE|TIMER_INTERRUPTS; 
		
		// resets laser positions
		for (i=0;i<20;i++) {
			for(j=0;j<4;j++) {
				laser_arr[i][j] = 0;
			} 
		} 
		count = 0; //reset the counts variables
		count_1 = -32;
		count_2 = -64;
		count_3 = -96;
		count_4 = -128;
		out_screen(); // call function to shift menu screen sprites out of screen
	 }
	 else  //stops the game when start is pressed again, remove TIMER_INTERRUPTS for timer 0,1,3
	 {
		REG_TM1D = 1433; // for obj to fall every 1 second interval
	 	REG_TM1CNT = TIMER_FREQUENCY_256|TIMER_ENABLE; // removes the TIMER_INTERRUPT
	
   	REG_TM0D =	56763; // set for screen to be displayed at 30fps
    	REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;

		black_screen(); // draws a black screen to clear out all current sprites
		time_count = 0; // reset time_count for next round
		x_position = 0; // resets x_position and y_position for spaceship
		y_position = 144;
		a=-1; //resets time_count for assembly function
	 }
}


void buttonR(void) //move right
{	 
	 x_position += 1;
	 if (x_position > 224) { //if you try to move the spaceship out of the screen this prevents it
	 	x_position -= 16;		
	 } 
	 return x_position;
}

void buttonL(void) //move left
{
	x_position -= 1;
	if (x_position < 0) { //if you try to move the spaceship out of the screen this prevents it
		x_position += 16;
	}
	return x_position; 
}

void buttonU(void) //move up
{
	 y_position -= 1;
	 if (y_position < 0) { //if you try to move the spaceship out of the screen this prevents it
	 	y_position += 16;		
	 } 
	 return y_position;
}

void buttonD(void) //move down
{
	 y_position += 1;
	 if (y_position > 144) { //if you try to move the spaceship out of the screen this prevents it
	 	y_position -= 16;		
	 } 
	 return y_position;
}


void objinit(void) // initialize sprites based on time_count variable. if it is <50 it display level 1 sprites. If it is >50 it displays level 2 sprites
{
	int num = 0;
	if(time_count<50){ //level 1 
	for (num = 0; num < 5; num++) // draw the sprites by going through the 2D array of obj_arr where 0-4 of each row are x coordinate and 5 is y coordinate
	{
		drawSprite(4,num+10,obj_arr[0][num],count);
		drawSprite(4,num+15,obj_arr[1][num],count_1);
		drawSprite(4,num+20,obj_arr[2][num],count_2);
		drawSprite(4,num+25,obj_arr[3][num],count_3);
		drawSprite(4,num+30,obj_arr[4][num],count_4);
	}
	int i;
	// row0 to row4 are the same as rows in the 2D array obj_arr
	// whenever the alien collide with the laser, the alien will be shifted out of the screen (This is in a function collideinit() below),
	// row0 to row5 will be used to update the obj_arr once again so that the object will appear back again from the top of the screen.
	int row0[] = {0,16,32,48,64,0};
	int row1[] = {224,192,64,96,112,-32};
	int row2[] = {0,16,32,112,176,-64};
	int row3[] = {32,208,80,96,240,-96};
	int row4[] = {176,192,208,224,160,-128};
	// 
	if (count>=160) { // if count is more than 160, the sprite will go out of screen, this resets the sprite back to the screen top of the screen
		count = 0;
		for (i=0;i<5;i++) {
			obj_arr[0][i] = row0[i]; // update obj_arr with the original position of each sprite
		}
	}
	if (count_1>=160) { 
		count_1 = -32;
		for (i=0;i<5;i++) {
			obj_arr[1][i] = row1[i];
		}
	}
	if (count_2>=160) {
		count_2 = -64;
		for (i=0;i<5;i++) {
			obj_arr[2][i] = row2[i];
		}
	}
	if (count_3>=160) {
		count_3 = -96;
		for (i=0;i<5;i++) {
			obj_arr[3][i] = row3[i];
		}
	}
	if (count_4>=160) {
		count_4 = -128;
		for (i=0;i<5;i++) {
			obj_arr[4][i] = row4[i];
		}
	}
	//updates the y coordinates for each row of objects incase they were shifted out due to the laser 
	obj_arr[0][5] = count;
	obj_arr[1][5] = count_1;
	obj_arr[2][5] = count_2;
	obj_arr[3][5] = count_3;
	obj_arr[4][5] = count_4;
	} 
	else if (time_count>=50 && time_count<101) { //level 2 
	if (time_count ==50) { // sets the level 2 sprites to fall from the top 
		count = 0;
		count_1 = -32;
		count_2 = -64;
		count_3 = -96;
		count_4 = -128;
	}
	for (num = 0; num < 6; num++) // draw the sprites by going through the 2D array of obj_arr where 0-5 of each row are x coordinate and 6 is y coordinate
	{
		drawSprite(27,num+10,lvl2_obj_arr[0][num],count);
		drawSprite(27,num+16,lvl2_obj_arr[1][num],count_1);
		drawSprite(27,num+22,lvl2_obj_arr[2][num],count_2);
		drawSprite(27,num+28,lvl2_obj_arr[3][num],count_3);
		drawSprite(27,num+34,lvl2_obj_arr[4][num],count_4);
	}
	int i;
	// row5 to row9 are the same as rows in the 2D array lvl2_obj_arr
	// whenever the alien collide with the laser, the alien will be shifted out of the screen. This is in a function collideinit() below.
	// row5 to row9 will be used to update the lvl2_obj_arr once again so that the alien will appear back again from the top of the screen.
	int row5[] = {48,64,80,96,112,128,0};
	int row6[] = {16,112,128,144,160,176,-32};
	int row7[] = {48,176,192,208,224,240,-64};
	int row8[] = {80,96,112,128,208,224,-96};
	int row9[] = {16,96,112,160,176,224,-128};

	if (count>=160) { // if count is more than 160, the sprite will go out of screen, this resets the sprite back to the screen top of the screen
		count = 0;
		for (i=0;i<6;i++) {  // update obj_arr with the original x coordinate of the sprites
			lvl2_obj_arr[0][i] = row5[i];
		}
	}
	if (count_1>=160) { 
		count_1 = -32;
		for (i=0;i<6;i++) {
			lvl2_obj_arr[1][i] = row6[i];
		}
	}
	if (count_2>=160) { 
		count_2 = -64;
		for (i=0;i<6;i++) {
			lvl2_obj_arr[2][i] = row7[i];
		}
	}
	if (count_3>=160) { 
		count_3 = -96;
		for (i=0;i<6;i++) {
			lvl2_obj_arr[3][i] = row8[i];
		}
	}
	if (count_4>=160) { 
		count_4 = -128;
		for (i=0;i<6;i++) {
			lvl2_obj_arr[4][i] = row9[i];
		}
	}
	//updates the y coordinates for each row of sprites incase they were shifted out due to the laser 
	lvl2_obj_arr[0][6] = count;
	lvl2_obj_arr[1][6] = count_1;
	lvl2_obj_arr[2][6] = count_2;
	lvl2_obj_arr[3][6] = count_3;
	lvl2_obj_arr[4][6] = count_4;
	} 
	if(time_count>100) { // game will display win! when count >100
	if (time_count == 101) {
		count = 0;
		count_1 = -32;
		count_2 = -64; 
		count_3 = -96;
		count_4 = -128;
	}
		time_count =100; 
		drawSprite(38,21,104,76); //WI
		drawSprite(39,22,120,76); //N!
		drawSprite(1,100,100,140); //ST
		drawSprite(2,101,116,140);//AR
		drawSprite(3,102,132,140); //T 
		drawSprite(20,99,100,120); //PR
		drawSprite(21,98,116,120); //ES
		drawSprite(22,97,132,120); //S

	}
}

void laserinit(void) //Draws the laser that have been stored in the laser_arr
{ 
	int num;
	int y;
	for(num=0;num<10;num++)
	{
		y = laser_arr[num][2]+laser_arr[num][3]; // update new y coordinate of laser
		drawSprite(18,laser_arr[num][0],laser_arr[num][1],y);	// draw laser sprite
		laser_arr[num][3] -= 4; // laser moving upwards
		if(y < 0) // if y coordinate is less than zero, remove the laser
		{
			laser_arr[num][1] = 0;
			laser_arr[num][2] = -16;
			laser_arr[num][3] = -16;
		}
	}	
}

void collideinit(void) 
// ends the game, showing game over screen if spaceship and alien collides.
// shifts alien sprite out of screen if laser and alien collides.
{
	int i;
	int j;
	int k;
	int x;
	int y;
	if (a <=50) {
	for (i=0;i<20;i++) // loop to check if the laser and the sprite collides
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<5;k++)
			{
				if( (obj_arr[j][k] <= laser_arr[i][1]+5) && ((obj_arr[j][k]+15) >= laser_arr[i][1])) // checks if  x_coordinate of alien <= x_coordinate of the laser <= x_coordinate of alien +15
				{
					if((obj_arr[j][5]-8 <= (laser_arr[i][2]+laser_arr[i][3])) && ((obj_arr[j][5]+15) >= (laser_arr[i][2]+laser_arr[i][3])))  // checks if  y_coordinate of alien <= y_coordinate of the laser <= y_coordinate of alien +15
					{ 
						obj_arr[j][k] = -100; //shift object out of screen
						laser_arr[i][2] = -100; //shift laser out of screen (not working)
					}
				}
				if( (obj_arr[j][k] <= laser_arr[i][1]+9) && ((obj_arr[j][k]+15) >= laser_arr[i][1])) // checks if  x_coordinate of alien <= x_coordinate of the laser <= x_coordinate of alien +15
				{
					if((obj_arr[j][5]-8 <= (laser_arr[i][2]+laser_arr[i][3])) && ((obj_arr[j][5]+15) >= (laser_arr[i][2]+laser_arr[i][3])))  // checks if  y_coordinate of alien <= y_coordinate of the laser <= y_coordinate of alien +15
					{ 
						obj_arr[j][k] = -100; //shift object out of screen
						laser_arr[i][2] = -100; //shift laser out of screen (not working)
					}
				}
			}
		}
	}


	for(x=0;x<5;x++){ // loop to check if spaceship and alien collides, checks for all four corners of spaceship to all four sides of alien, stop timer 0 and 1 and draw "GAME OVER" if it collides
		for(y=0;y<5;y++){
			if (y_position <= obj_arr[x][5]+15 && y_position >= obj_arr[x][5]){ //comparing the top left corner of the spaceship sprite to the area
				if (x_position >= obj_arr[x][y] && x_position <= obj_arr[x][y]+15){
					REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE; // stop timers 0 and 1 if collides
					REG_TM1CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					drawSprite(23,21,84,76); //GA
					drawSprite(24,22,100,76); //ME
					drawSprite(25,23,124,76); //OV
					drawSprite(26,24,140,76); //ER
					drawSprite(1,100,100,120); //ST
					drawSprite(2,101,116,120);//AR
					drawSprite(3,102,132,120); //T 
					drawSprite(20,99,100,100); //PR
					drawSprite(21,98,116,100); //ES
					drawSprite(22,97,132,100); //S
				}
			}
			if (y_position+15 <= obj_arr[x][5]+15 && y_position+15 >= obj_arr[x][5] ){ //compare the bottom right corner of the spaceship sprite to the area
				if (x_position+15 >= obj_arr[x][y] && x_position+15 <= obj_arr[x][y]+15){
					REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					REG_TM1CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					drawSprite(23,21,84,76); //GA
					drawSprite(24,22,100,76); //ME
					drawSprite(25,23,124,76); //OV
					drawSprite(26,24,140,76); //ER
					drawSprite(1,100,100,120); //ST
					drawSprite(2,101,116,120);//AR
					drawSprite(3,102,132,120); //T 
					drawSprite(20,99,100,100); //PR
					drawSprite(21,98,116,100); //ES
					drawSprite(22,97,132,100); //S
				}
			}
			if (y_position+15 <= obj_arr[x][5]+15 && y_position+15 >= obj_arr[x][5] ){ //compare the bottom left corner of the spaceship sprite to the area
				if (x_position >= obj_arr[x][y] && x_position <= obj_arr[x][y]+15){
					REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					REG_TM1CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					drawSprite(23,21,84,76); //GA
					drawSprite(24,22,100,76); //ME
					drawSprite(25,23,124,76); //OV
					drawSprite(26,24,140,76); //ER
					drawSprite(1,100,100,120); //ST
					drawSprite(2,101,116,120);//AR
					drawSprite(3,102,132,120); //T 
					drawSprite(20,99,100,100); //PR
					drawSprite(21,98,116,100); //ES
					drawSprite(22,97,132,100); //S
				}	
			}
			if (y_position <= obj_arr[x][5]+15 && y_position >= obj_arr[x][5] ){ //compare the top right corner of the spaceship to the area. The same concept for the laser.
				if (x_position+15 >= obj_arr[x][y] && x_position+15 <= obj_arr[x][y]+15){ 
					REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					REG_TM1CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					drawSprite(23,21,84,76); //GA
					drawSprite(24,22,100,76); //ME
					drawSprite(25,23,124,76); //OV
					drawSprite(26,24,140,76); //ER
					drawSprite(1,100,100,120); //ST
					drawSprite(2,101,116,120);//AR
					drawSprite(3,102,132,120); //T 
					drawSprite(20,99,100,100); //PR
					drawSprite(21,98,116,100); //ES
					drawSprite(22,97,132,100); //S
				}
			}
		}
	}
  	}
	else if (a > 50) { // repeat this for level 2 objects
	for (i=0;i<20;i++) // for loop to determine laser and alien collision
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<6;k++)
			{
				if( (lvl2_obj_arr[j][k] <= laser_arr[i][1]+5) && ((lvl2_obj_arr[j][k]+15) >= laser_arr[i][1]))	// checks if  x_coordinate of alien <= x_coordinate of the laser <= x_coordinate of alien +15
				{
					if((lvl2_obj_arr[j][6] <= (laser_arr[i][2]+laser_arr[i][3])) && ((lvl2_obj_arr[j][6]+15) >= (laser_arr[i][2]+laser_arr[i][3])))  // checks if  y_coordinate of alien <= y_coordinate of the laser <= y_coordinate of alien +15
					{ 
						lvl2_obj_arr[j][k] = -100; //shift object out of screen
						laser_arr[i][2] = -100; //shift laser out of screen (not working)
					}
				}
				if( (obj_arr[j][k] <= laser_arr[i][1]+9) && ((obj_arr[j][k]+15) >= laser_arr[i][1])) // checks if  x_coordinate of alien <= x_coordinate of the laser <= x_coordinate of alien +15
				{
					if((obj_arr[j][5]-8 <= (laser_arr[i][2]+laser_arr[i][3])) && ((obj_arr[j][5]+15) >= (laser_arr[i][2]+laser_arr[i][3])))  // checks if  y_coordinate of alien <= y_coordinate of the laser <= y_coordinate of alien +15
					{ 
						obj_arr[j][k] = -100; //shift object out of screen
						laser_arr[i][2] = -100; //shift laser out of screen (not working)
					}
				}
			}
		}
	}
	for(x=0;x<5;x++){ //for loop to determine alien and spaceship collision
		for(y=0;y<6;y++){
			if (y_position <= lvl2_obj_arr[x][6]+15 && y_position >= lvl2_obj_arr[x][6]){ //comparing the top left corner of the spaceship sprite to the area
				if (x_position >= lvl2_obj_arr[x][y] && x_position <= lvl2_obj_arr[x][y]+15){
					REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					REG_TM1CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					drawSprite(23,21,84,76); //GA
					drawSprite(24,22,100,76); //ME
					drawSprite(25,23,124,76); //OV
					drawSprite(26,24,140,76); //ER
					drawSprite(1,100,100,120); //ST
					drawSprite(2,101,116,120);//AR
					drawSprite(3,102,132,120); //T 
					drawSprite(20,99,100,100); //PR
					drawSprite(21,98,116,100); //ES
					drawSprite(22,97,132,100); //S
				}
			}
			if (y_position+15 <= lvl2_obj_arr[x][6]+15 && y_position+15 >= lvl2_obj_arr[x][6] ){ //compare the bottom right corner of the spaceship sprite to the area
				if (x_position+15 >= lvl2_obj_arr[x][y] && x_position+15 <= lvl2_obj_arr[x][y]+15){
					REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					REG_TM1CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					drawSprite(23,21,84,76); //GA
					drawSprite(24,22,100,76); //ME
					drawSprite(25,23,124,76); //OV
					drawSprite(26,24,140,76); //ER
					drawSprite(1,100,100,120); //ST
					drawSprite(2,101,116,120);//AR
					drawSprite(3,102,132,120); //T 
					drawSprite(20,99,100,100); //PR
					drawSprite(21,98,116,100); //ES
					drawSprite(22,97,132,100); //S
				}
			}
			if (y_position+15 <= lvl2_obj_arr[x][6]+15 && y_position+15 >= lvl2_obj_arr[x][6] ){ //compare the bottom left corner of the spaceship sprite to the area
				if (x_position >= lvl2_obj_arr[x][y] && x_position <= lvl2_obj_arr[x][y]+15){
					REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					REG_TM1CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					drawSprite(23,21,84,76); //GA
					drawSprite(24,22,100,76); //ME
					drawSprite(25,23,124,76); //OV
					drawSprite(26,24,140,76); //ER
					drawSprite(1,100,100,120); //ST
					drawSprite(2,101,116,120);//AR
					drawSprite(3,102,132,120); //T 
					drawSprite(20,99,100,100); //PR
					drawSprite(21,98,116,100); //ES
					drawSprite(22,97,132,100); //S
				}
			}
			if (y_position <= lvl2_obj_arr[x][6]+15 && y_position >= lvl2_obj_arr[x][6] ){ //compare the top right corner of the spaceship to the area. The same concept for the laser.
				if (x_position+15 >= lvl2_obj_arr[x][y] && x_position+15 <= lvl2_obj_arr[x][y]+15){ 
					REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					REG_TM1CNT = TIMER_FREQUENCY_64|TIMER_ENABLE;
					drawSprite(23,21,84,76); //GA
					drawSprite(24,22,100,76); //ME
					drawSprite(25,23,124,76); //OV
					drawSprite(26,24,140,76); //ER
					drawSprite(1,100,100,120); //ST
					drawSprite(2,101,116,120);//AR
					drawSprite(3,102,132,120); //T 
					drawSprite(20,99,100,100); //PR
					drawSprite(21,98,116,100); //ES
					drawSprite(22,97,132,100); //S

				}
			}
		}
	}
	}
}
// function to make spaceship move down the screen if not button is pressed
void moving_downwards(void){
	y_position+=1; 
	if(y_position>=144){
		y_position = 144; }
}


void Handler(void)
{
    REG_IME = 0x00; // Stop all other interrupt handling, while we handle this current one

    if ((REG_IF & INT_TIMER0 ) == INT_TIMER0) 
    {
	 	drawSprite(0,0,x_position,y_position); //draw Spaceship
		checkbutton();
		moving_downwards();
		collideinit();
		checkbutton();
	 }

    if ((REG_IF & INT_TIMER1 ) == INT_TIMER1) // one 1second timer
    {
		count += 16;
		count_1 += 16;
		count_2 += 16;
		count_3 += 16;
		count_4 += 16;
		objinit();
		laserinit();
		//checkbutton();
		time_count=timer_count(a); // assembly function
		a=timer_count(a);
		drawSprite(((time_count/100)+28),1,208,16); // Draw timer on top right hand corner of screen
		drawSprite((((time_count/10)%10)+28),2,216,16);
		drawSprite(((time_count%10)+28),3,224,16);

	 }

    if ((REG_IF & INT_TIMER2 ) == INT_TIMER2) 
    {
		checkbutton();
		start_screen();

	 }

    REG_IF = REG_IF; // Update interrupt table, to confirm we have handled this interrupt 
    
    REG_IME = 0x01;  // Re-enable interrupt handling	
}

int main(void)
{
	int i;
	int j;
    // Set Mode 2
    *(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;
    // Fill SpritePal
    for (i = 0; i < NCOLS; i++)
		  spritePal[i] = palette[i];
    // Fill SpriteData
    for (i = 0; i < 128*16*16; i++)
        spriteData[i] = (sprites[i*2+1] << 8) + sprites[i*2];\
	 
	 for(j=2;j<277;j++) { 
				drawSprite(0,j,240,160); //cover the gibberish on screen. 
			}


	// Set Handler Function for interrupts and enable selected interrupts
	 REG_INT = (int)&Handler;
    REG_IE = INT_TIMER0|INT_TIMER1|INT_TIMER2; 	
	 REG_IME = 0x1;	

	 REG_TM2D = 56763; // For the menu screen	
	 REG_TM2CNT = TIMER_FREQUENCY_64|TIMER_ENABLE|TIMER_INTERRUPTS;
	
	 REG_TM1D = 1433; // for spikes to fall every 1 second interval
	 REG_TM1CNT = TIMER_FREQUENCY_256|TIMER_ENABLE;

    REG_TM0D =	56763; // set for screen to be displayed at 30fps
    REG_TM0CNT = TIMER_FREQUENCY_64|TIMER_ENABLE; 

	 while(1)
	 {}

	return 0;
}

