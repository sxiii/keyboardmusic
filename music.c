# File Updated To Work In 2019 :D
# Updated 30 november 2019 @ Ungleich Hackathon (Hack4Glarus)
# NB: Still a lot of places to improve the code

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h> 
#include <stdlib.h>
#include <termios.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX 6

int intArray[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;

int peek(){ return intArray[front]; }

bool isEmpty(){ return itemCount == 0; }

bool isFull(){ return itemCount == MAX; }

int size(){ return itemCount; }  

void insert(int data){

   if(!isFull()){
	
      if(rear == MAX-1){
         rear = -1;            
      }       

      intArray[++rear] = data;
      itemCount++;
   }
}

int removeData(){
   int data = intArray[front++];
	
   if(front == MAX){
      front = 0;
   }
	
   itemCount--;
   return data;  
}

/* 
  // Seems that we don't need the following libs
  #include <time.h>
  #include <unistd.h>
  #include <sys/types.h>
*/

// These are arrays for pentatonic scales and also a duration array
int array1[]={262,294,330,392,440}; // C major pentatonic scale (C D E G A)
int array2[]={392,440,494,587,659}; // G major pentatonic scale (G A B D E)
int array3[]={277,349,392,466,523}; // Eb major pentatonic scale (Eb F G Bb C)
int array4[]={277,392,440,494,587}; // E minor pentatonic scale
int darray[]={100,150,200,250,300}; // Duration Array

char *waveform[] = {"sine", "square", "triangle", "sawtooth", "trapetz", "exp", "whitenoise", "pinknoise", "brownnoise"};
int rrna[]={262,294,330,392,440,392,440,494,587,659,277,349,392,466,523,277,392,440,494,587};
float delays[] = {0.1f, 0.2f, 0.3f, 0.5f, 0.75f, 1.00f};
// waveform id
int wid = 1;
int did = 1;
float dar = 0.1f;

//max = 5;
// This is for random generating if you would like to implement it. Not used here.
int rnd( int max ) {return (rand() % max) + 1;} 

static struct termios g_old_kbd_mode;

// did somebody press somthing???
static int kbhit(void){
    struct timeval timeout;
    fd_set read_handles;
    int status;

    // check stdin (fd 0) for activity
    FD_ZERO(&read_handles);
    FD_SET(0, &read_handles);
    timeout.tv_sec = timeout.tv_usec = 0;
    status = select(0 + 1, &read_handles, NULL, NULL, &timeout);
    return status;
}

// put the things as they were befor leave..!!!
static void old_attr(void){
    tcsetattr(0, TCSANOW, &g_old_kbd_mode);
}

int fork_n_execute(int frequency, int wid, float dar)
{
  int status;
  pid_t pid;
  pid = fork ();
 
  if(pid == 0)
  {
  char str[80];
  sprintf(str, "play -q -n synth %f %s %i", dar, waveform[wid], frequency);
  system(str);
  exit(EXIT_SUCCESS);
  }
  return status;
}


// main function
int main( void ){
//int main(int argc, char *argv[])
//{
//  int dar = 200;
  int del = 1;

    char ch;
    static char init;
    struct termios new_kbd_mode;

    if(init)
        return;
    // put keyboard (stdin, actually) in raw, unbuffered mode
    tcgetattr(0, &g_old_kbd_mode);
    memcpy(&new_kbd_mode, &g_old_kbd_mode, sizeof(struct termios));
    
    new_kbd_mode.c_lflag &= ~(ICANON | ECHO);
    new_kbd_mode.c_cc[VTIME] = 0;
    new_kbd_mode.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_kbd_mode);
    atexit(old_attr);
    
    printf( "Press Any Key ('q' for exit) \n");
   while (!kbhit()){
   //while (1) {
        // getting the pressed key...
        ch = getchar();
        printf("You pressed - %c\n",ch);
        if (ch == '-') {if (did == 0) {dar = delays[did]; printf("Delay is already lowest: %f\n", dar);}
                        else if (did <= 5) {did = did - 1; dar = delays[did]; printf("Lowering delay to %f\n", dar);}}; 
        if (ch == '+') {if (did == 5) {dar = delays[did]; printf("Delay is already highest: %f\n", dar);}
                        else if (did < 5) {did = did + 1; dar = delays[did]; printf("Setting delay higher to %f\n", dar);}};
      //case 0x38: {printf("Key 8 pressed. Shorter sound."); del = del - 50000; printf("del is");}; break;
//	case 0x39: {printf("Key 9 pressed. Longer sound."); del = del + 50000; printf("del2");}; break;
        if (ch == ' ') {if (wid == 8) {wid = 0; printf("Setting playmode to %s (%i)\n", waveform[wid], wid);}
			else if (wid < 8) {wid = wid + 1; printf("Setting playmode to %s (%i)\n", waveform[wid], wid);}}; 
	if (ch == 'j') {printf("Today random number is: %i\n", rnd(5));}; 
        if (ch == 'm') {printf("Total random key pressed.\n"); fork_n_execute(rrna[rnd(20)],wid,dar);usleep(del);}; 
        if (ch == '*') {printf("Exit key (*) pressed, BB, CU!\n");exit (1);}; 
     
        if (ch == '1') {printf("Key 1 Tone C Freq 262 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[0],wid,dar);usleep(del);}; 
        if (ch == '2') {printf("Key 2 Tone D Freq 294 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[1],wid,dar);usleep(del);}; 
        if (ch == '3') {printf("Key 3 Tone E Freq 330 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[2],wid,dar);usleep(del);}; 
        if (ch == '4') {printf("Key 4 Tone G Freq 392 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[3],wid,dar);usleep(del);}; 
        if (ch == '5') {printf("Key 5 Tone A Freq 440 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[4],wid,dar);usleep(del);}; 
        if (ch == '6') {printf("Random scale 1 key waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array1[rnd(5)],wid,dar);usleep(del);}; 
     
        if (ch == 'q') {printf("Key Q Tone G Freq 392 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[0],wid,dar);usleep(del);}; 
        if (ch == 'w') {printf("Key W Tone A Freq 440 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[1],wid,dar);usleep(del);}; 
        if (ch == 'e') {printf("Key E Tone B Freq 494 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[2],wid,dar);usleep(del);}; 
        if (ch == 'r') {printf("Key R Tone D Freq 587 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[3],wid,dar);usleep(del);}; 
        if (ch == 't') {printf("Key T Tone E Freq 659 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[4],wid,dar);usleep(del);}; 
        if (ch == 'y') {printf("Random scale 2 key waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array2[rnd(5)],wid,dar);usleep(del);}; 

        if (ch == 'a') {printf("Key A Tone Eb Freq 277 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[0],wid,dar);usleep(del);}; 
        if (ch == 's') {printf("Key S Tone F Freq 349 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[1],wid,dar);usleep(del);}; 
        if (ch == 'd') {printf("Key D Tone G Freq 392 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[2],wid,dar);usleep(del);}; 
        if (ch == 'f') {printf("Key F Tone Bb Freq 466 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[3],wid,dar);usleep(del);}; 
        if (ch == 'g') {printf("Key G Tone C Freq 523 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[4],wid,dar);usleep(del);}; 
        if (ch == 'h') {printf("Random scale 3 key waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array3[rnd(5)],wid,dar);usleep(del);}; 

        if (ch == 'z') {printf("Key Z Tone Eb Freq 277 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[0],wid,dar);usleep(del);}; 
        if (ch == 'x') {printf("Key X Tone G Freq 392 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[1],wid,dar);usleep(del);}; 
        if (ch == 'c') {printf("Key C Tone A Freq 440 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[2],wid,dar);usleep(del);}; 
        if (ch == 'v') {printf("Key V Tone B Freq 494 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[3],wid,dar);usleep(del);}; 
        if (ch == 'b') {printf("Key B Tone D Freq 587 waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[4],wid,dar);usleep(del);}; 
        if (ch == 'n') {printf("Random scale 4 key waveform: %s len: %f\n",waveform[wid],dar);fork_n_execute(array4[rnd(5)],wid,dar);usleep(del);}; 
	    //default: ; break;
        main();
   }
   return 0;
}
