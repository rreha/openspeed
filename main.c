#include <stdio.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
//#include "lib/callback.h"
#include "lib/file_io.h"
PSP_MODULE_INFO("OpenSpeed", 0, 1, 0);

void copy_pro() {
	const char* src = ROOT "sensme/pro661/NPIA00013/EBOOT.PBP";
	const char* out = ROOT "../../APP/NPIA00013/EBOOT.PBP"; // using relative path because of ef0 (psp go)
	
	char* file_data;
	SceIoStat info;
	check_file(&info, src);

	int uid = open_file(src, PSP_O_RDONLY, 0777);
	read_file(uid, &file_data, (int)info.st_size);
	close_file(uid);
	
	uid = open_file(out, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	write_file(uid, file_data, (int)info.st_size);
	close_file(uid);
	
	free(file_data);
	file_data = 0;
}

void copy_lme() {
	const char* src = ROOT "sensme/lme661/NPIA00013/EBOOT.PBP";
	const char* out = ROOT "../../APP/NPIA00013/EBOOT.PBP"; // using relative path because of ef0 (psp go)
	
	char* file_data;
	SceIoStat info;
	check_file(&info, src);

	int uid = open_file(src, PSP_O_RDONLY, 0777);
	read_file(uid, &file_data, (int)info.st_size);
	close_file(uid);
	
	uid = open_file(out, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	write_file(uid, file_data, (int)info.st_size);
	close_file(uid);
	
	free(file_data);
	file_data = 0;
}

int main(){
    pspDebugScreenInit();
    pspDebugScreenClear();
    SetupCallbacks();
    pspDebugScreenSetXY(0, 0);
    int version_num = sceKernelDevkitVersion(); // stole from PSPIdent source
	  char *version_chr = (char *)&version_num;
      if (version_num < 661){
        pspDebugScreenPrintf("ERROR!: Your PSP firmware is %i.%i%i!!! This program only works with 6.61!\n\n", version_chr[3], version_chr[2], version_chr[1]);
      }
    pspDebugScreenSetTextColor(0xFF99CCFF);
    pspDebugScreenPrintf("OpenSpeed v1 - reha\n");
    pspDebugScreenPrintf("\n**************************\n");
    pspDebugScreenSetTextColor(0xFFFFFFFF);
    pspDebugScreenPrintf("\nPress X to replace SensMe with 6.61 PRO-C2 Launcher\n");
    pspDebugScreenPrintf("Press O to replace SensMe with 6.61 LME 2.3 Launcher\n");
    pspDebugScreenPrintf("Press [] to uninstall\n");
    pspDebugScreenPrintf("Press /\\ to exit\n");
    sceDisplayWaitVblankStart();
    
    SceCtrlData pad;

   while(1) {
		sceCtrlReadBufferPositive(&pad, 1);
		if (pad.Buttons & PSP_CTRL_CROSS)
			{
      pspDebugScreenPrintf("\n\nStarting...\n");
      pspDebugScreenPrintf("Creating /APP/NPIA00013...\n");
      sceIoMkdir("../../APP/NPIA00013", 0777);
      pspDebugScreenPrintf("Copying SensMe PRO-C2 launcher to /APP/NPIA00013...\n");
      copy_pro();
      pspDebugScreenPrintf("\nDone! Exiting...");
      sceKernelDelayThread(3*1000*1000);
      sceKernelExitGame();
      }

    if (pad.Buttons & PSP_CTRL_CIRCLE)
			{
      pspDebugScreenPrintf("\n\nStarting...\n");
      pspDebugScreenPrintf("Creating /APP/NPIA00013...\n");
      sceIoMkdir("../../APP/NPIA00013", 0777);
      pspDebugScreenPrintf("Copying SensMe LME 2.3 launcher to /APP/NPIA00013...\n");
      copy_lme();
      pspDebugScreenPrintf("\nDone! Exiting...");
      sceKernelDelayThread(3*1000*1000);
      sceKernelExitGame();
      }

      if (pad.Buttons & PSP_CTRL_SQUARE)
			{
      pspDebugScreenPrintf("\n\nUninstalling...\n");
      pspDebugScreenPrintf("Deleting /APP/NPIA00013...\n");
      sceIoRemove("../../APP/NPIA00013");
      pspDebugScreenPrintf("\nDone! Exiting...");
      sceKernelDelayThread(3*1000*1000);
      sceKernelExitGame();
      }

    if (pad.Buttons & PSP_CTRL_TRIANGLE)
			{
      pspDebugScreenPrintf("Exiting...\n"); 
      sceKernelExitGame();
      }
	}
}