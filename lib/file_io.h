/*
Took from https://en.wikibooks.org/wiki/PSP_Development/Filesystem/Reading_Writing_Files 
Modified it a bit :grin:
*/


// include psp stuff
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>

// calloc, malloc, relloc
#include <stdlib.h>

// include commons stuff
#include "./callback.h"


// configure PSP stuff
#define VERS    1
#define REVS    0
#define ROOT "umd0:/"

// make printing easier on us
#define printf pspDebugScreenPrintf


void crash(int error, const char* crasher, const char* message) {
	sceDisplayWaitVblankStart();
	printf("Error (%d) : %s\n", error, crasher);
	printf("%s\n", message);
	sceKernelSleepThread();
}

void test_crash() {
	sceDisplayWaitVblankStart();
	printf("No crash occured.");
	sceKernelSleepThread();
}



void check_file(SceIoStat* info, const char* path) {
	// open file description
	int status;
	if((status = sceIoGetstat(path, info)) < 0)
		crash(status, "Checking File", "File not found or no access!");
}

int open_file(const char* path, int params, int chmod) {
	// open file handle
	int uid = sceIoOpen(path, params, chmod);
	if(uid < 0)
		crash(uid, "Opening File", "File not found or no access!");
	return uid;
}

void close_file(int uid) {
	int status;
	if((status = sceIoClose(uid)) < 0)
		crash(status, "Close File", "File could not be closed!");
}

void write_file(int uid, const char* out, int size) {
	// write to file
	if(sceIoWrite(uid, out, size) != size)
		crash(uid, "Writing File", "File wrote incorrect number of bytes!");
}

void read_file(int uid, char** out, int size) {
	// allocate, read into buffer, pad with \0
	char* buffer = (char*)calloc(size+1, sizeof(char));
	if(buffer == 0)
		crash(0, "Memory Allocation", "Memory allocation failed!");
	int read = sceIoRead(uid, buffer, size);
	if(read != size)
		crash(read, "Read File", "File size read doesn't match expected!");
	buffer[size] = '\0';
	*out = buffer;
}

void do_example3() {
	const char* src = ROOT "test.txt";
	const char* out = ROOT "diff.txt";
	
	// Copy file test.txt > diff.txt
	char* file_data;
	SceIoStat info;
	check_file(&info, src);
	
	// multiple files can be open at once, but since using one variable
	// closing the file would be wise before losing the data
	int uid = open_file(src, PSP_O_RDONLY, 0777);
	read_file(uid, &file_data, (int)info.st_size);
	close_file(uid);
	
	uid = open_file(out, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	write_file(uid, file_data, (int)info.st_size);
	close_file(uid);
	
	free(file_data);
	file_data = 0;
}
