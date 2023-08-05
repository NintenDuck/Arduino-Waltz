#include <SPI.h>
#include <SD.h>
#include "TMRpcm.h"

// #define NEXT
// #define _PAUSE

TMRpcm AUDIO;
File ROOT;

char* SD_ROOT = "/";

int SPEAKER_PIN = 9;

int DEFAULT_AUDIO_VOLUME = 7;
int DEFAULT_AUDIO_QUALITY = 1;

void init_sd(){
	Serial.print( "Initializing SD card..." );
	if ( !SD.begin() ){
		Serial.println( "Initializing failed!" );
		while ( 1 );
	}
	Serial.println( "Initialization done." );
}

void init_audio(){
	AUDIO.speakerPin = SPEAKER_PIN;
	AUDIO.setVolume( DEFAULT_AUDIO_VOLUME );
	AUDIO.quality( DEFAULT_AUDIO_QUALITY );
}

void play_audio( char* song_name="none" ){
	// char* void_song = "none"
	if ( song_name == "none" ) return;

	AUDIO.play( song_name );
	Serial.print( "Playing song: " );
	Serial.println( song_name );
}

void setup() {
	Serial.begin(9600);
	while ( !Serial );
	
	init_sd();
	init_audio();
	
	ROOT = SD.open( SD_ROOT );
}


void loop() {
	if ( !AUDIO.isPlaying() ){
		File next_file = ROOT.openNextFile();
		if ( !next_file ){
			ROOT.rewindDirectory();
			return;
		} else {
			play_audio( next_file.name() );
		}
	}
}
