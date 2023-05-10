#include <SPI.h>
#include <SD.h>
#include "TMRpcm.h"

#define next
#defin _pause

TMRpcm audio;
File root;

char sd_root = "/"

int speaker_pin = 9;
int default_audio_volume = 7;
int default_audio_quality = 1;

void init_sd(){
	Serial.print( "Initializing SD card..." );
	if ( !SD.begin() ){
		Serial.println( "Initializing failed!" );
		while ( 1 );
	}
	Serial.println( "Initialization done." );
}

void init_audio(){
	audio.speakerPin = speakerPin;
	audio.setVolume( default_audio_volume );
	audio.quality( default_audio_quality );
}

void setup() {
	Serial.begin(9600);
	while ( !Serial );
	
	init_sd();
	init_audio();
	
	root = SD.open( sd_root );
}


void loop() {
	if ( !audio.isPlaying() ){
		File next_file = root.openNextFile();
		if ( !next_file ){
			root.rewindDirectory();
			return
		}
	}
	
	audio.play( next_file.name() );
	Serial.println( "Playing file: " );
	Serial.println( root.name() );
}
