#include <SPI.h>
#include <SD.h>
#include "TMRpcm.h"

#define NEXT
#defin _PAUSE

TMRpcm AUDIO;
File ROOT;

char sd_root = "/"

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
	AUDIO.speakerPin = speakerPin;
	AUDIO.setVolume( DEFAULT_AUDIO_VOLUME );
	AUDIO.quality( DEFAULT_AUDIO_QUALITY );
}

void setup() {
	Serial.begin(9600);
	while ( !Serial );
	
	init_sd();
	init_audio();
	
	ROOT = SD.open( sd_root );
}


void loop() {
	if ( !AUDIO.isPlaying() ){
		File next_file = ROOT.openNextFile();
		if ( !next_file ){
			ROOT.rewindDirectory();
			return
		}
	}

	AUDIO.play( next_file.name() );
	Serial.println( "Playing file: " );
	Serial.println( ROOT.name() );
}
