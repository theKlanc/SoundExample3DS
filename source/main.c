#include <3ds.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


u8* buffer;
u32 size;

static void audio_load(const char *audio);
static void audio_stop(void);


int main()
{
	// Inits
	srvInit();
	aptInit();
	hidInit(NULL);
	bool stop = 0;
	

	csndInit();//start Audio Lib
	u32 kDown;
	

	while (aptMainLoop()){
		
		hidScanInput();
		kDown = hidKeysDown();
		if (kDown & KEY_START){   //PRESS START TO RETURN TO HBL
			stop=1;
		}
		if (kDown & KEY_A){   // PRESS A TO PLAY
			audio_load("audio/original_raw.bin");
		}
		if (stop){ break; }
	}

	audio_stop();
	audio_stop();
	csndExit();

	hidExit();
	aptExit();
	srvExit();

	// Return to hbmenu
	return 0;
}


void audio_load(const char *audio){

	FILE *file = fopen(audio, "rb");

	// seek to end of file
	fseek(file, 0, SEEK_END);

	// file pointer tells us the size
	off_t size = ftell(file);

	// seek back to start
	fseek(file, 0, SEEK_SET);

	//allocate a buffer
	buffer = linearAlloc(size);

	//read contents !
	off_t bytesRead = fread(buffer, 1, size, file);
	//u8 test = &buffer;

	//close the file because we like being nice and tidy
	fclose(file);

	csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_REPEAT, 48000, 1, 0, buffer, buffer, size);
	linearFree(buffer);
}
void audio_stop(void){
	csndExecCmds(true);
	CSND_SetPlayState(0x8, 0);
	memset(buffer, 0, size);
	GSPGPU_FlushDataCache(NULL, buffer, size);
	linearFree(buffer);
}
