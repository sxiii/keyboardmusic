# Keyboard Music
Keyboard Music Jukebox, Linux (GCC) compilable

![Img](https://imgur.com/RQTBjOg.png)

## :: DESCRIPTION ::
This is C source for small musical pentatonic toy-program for Linux that I wrote.
This program has C major, G major, Eb major and E minor pentatonic scales.
You can play them right from keyboard (12345, QWERT, ASDFG, ZXCVB).

## Usage in 5 steps
0. Download git, if you don't already ( ubuntu: `sudo apt install git` )
1. Download sox (required to play sound, ubuntu: `sudo apt install sox` )
2. Download this repo ( `git clone https://github.com/sxiii/keyboardmusic` )
3. Change directory to recently downloaded: ( `cd keyboardmusic` )
4. Compile the file with: `gcc -o pentatonic pentatonic.c`
5. If compilation got successful, run the program with `./pentatonic`

## How to use
Just press the keys on the keyboard: 12345, QWERT, ASDFG, ZXCVB. You should here the sound.

# Supported platforms supported
Tested on Ubuntu 13.04 Alpha with gcc/g++ (Ubuntu/Linaro 4.7.2-19ubuntu1) 
Tested on Ubuntu 16.04.3 with gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.5)

# Future plans
* Small buffer for recently played notes
* Random note selection
* Button to change the length of the notes
* Some algorithms to automatically write music... (hard task but who knows...)

# Requirements
* It does need Sox to work, since command "play" is used.
* The code is in work for now. It is not final version. Please contribute if you like it.
* I am totally newbie in C, so there might be many other possibilities of replicating my work in other, more correct and easy way.

# About this project
* Created 4 feb 2013 by Security XIII at Gmail Dot Com
