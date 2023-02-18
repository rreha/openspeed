#include <stdio.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspsdk.h>
#include <pspiofilemgr.h>
#include "lib/kubridge.h"
//#include "lib/callback.h" no need to include this since its already included inside of the "file_io1.h"
#include "lib/file_io1.h"


// colors (stole from pspident again <3)
#define RGB(r, g, b) (0xFF000000 | ((b)<<16) | ((g)<<8) | (r))
#define RED RGB(255,0,0)
#define BLACK RGB(0,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(50,140,255)
#define ORANGE RGB(255,127,0)
#define WHITE RGB(255,255,255)

PSP_MODULE_INFO("OpenSpeed", 0, 1, 0);

int main(){
    pspDebugScreenInit();
    pspDebugScreenClear();
    SetupCallbacks();
    pspDebugScreenSetXY(0, 0);
	  int model = kuKernelGetModel();
	  int n1000 = 0;
    int version_num = sceKernelDevkitVersion(); // stole from PSPIdent source
	  char *version_chr = (char *)&version_num;
      if (version_num < 0x06060110){
        pspDebugScreenSetTextColor(RED);
        pspDebugScreenPrintf("ERROR: Your PSP firmware is %i.%i%i!!! \nThis program only works with 6.61!\nExiting...", version_chr[3], version_chr[2], version_chr[1]);
		    sceKernelDelayThread(4*1000*1000);
		    sceKernelExitGame();
      }
	        if (model == 3){
		        n1000 = 1;
	        }
    pspDebugScreenSetTextColor(GREEN);
    pspDebugScreenPrintf("OpenSpeed v1.0a - reha\n");
    pspDebugScreenPrintf("\n**************************\n");
    pspDebugScreenSetTextColor(WHITE);
    pspDebugScreenPrintf("\nPress X to replace SensMe with 6.61 PRO-C2 Launcher\n");
    pspDebugScreenPrintf("Press O to replace SensMe with 6.61 LME 2.3 Launcher\n");
    pspDebugScreenPrintf("Press [] to uninstall\n");
    pspDebugScreenPrintf("Press /\\ to exit\n");
	  pspDebugScreenPrintf("# Your model is: %d\n# Your FW is: %i.%i%i", model, version_chr[3], version_chr[2], version_chr[1]);
    sceDisplayWaitVblankStart();
    
    SceCtrlData pad;

   while(1) {
		sceCtrlReadBufferPositive(&pad, 1);
		if (pad.Buttons & PSP_CTRL_CROSS) //PRO-C
			{
        if ((n1000 == 1)){ // PSP GO ROUTE
          pspDebugScreenPrintf("\n\nPSP Go detected! Starting...\n");
          pspDebugScreenPrintf("Creating ef0:/PSP/APP/...\n");

          int mdprogo;
          mdprogo = sceIoMkdir("ef0:/PSP/APP", 0777);
            if(mdprogo < 0){
              pspDebugScreenSetTextColor(RED);
			        pspDebugScreenPrintf("ERROR: Failed to create APP, maybe you already installed? \nExiting...\n");
			        sceKernelDelayThread(3*1000*1000);
      	      sceKernelExitGame();
		        }
          pspDebugScreenPrintf("Creating ef0:/PSP/APP/NPIA00013/...\n");

          int mdprogo2;
          mdprogo2 = sceIoMkdir("ef0:/PSP/APP/NPIA00013", 0777);
            if(mdprogo2 < 0){
              pspDebugScreenSetTextColor(RED);
			        pspDebugScreenPrintf("ERROR: Failed to create NPIA00013, maybe you already installed? \nExiting...\n");
			        sceKernelDelayThread(3*1000*1000);
      	      sceKernelExitGame();
		        }

          pspDebugScreenPrintf("Copying SensMe PRO-C2 launcher to ef0:/PSP/APP/NPIA00013/...\n");
          copy_file("/sensme/pro661/NPIA00013/EBOOT.PBP","ef0:/PSP/APP/NPIA00013/EBOOT.PBP");
          pspDebugScreenPrintf("\nDone! Exiting...");
          sceKernelDelayThread(3*1000*1000);
          sceKernelExitGame();
        }

      // DEFAULT ROUTE (NON-GO)
      pspDebugScreenPrintf("\n\nStarting...\n");
      pspDebugScreenPrintf("Creating ms0:/PSP/APP/...\n");

      int mdpro;
      mdpro = sceIoMkdir("ms0:/PSP/APP", 0777);
      if(mdpro < 0){
        pspDebugScreenSetTextColor(RED);
			  pspDebugScreenPrintf("ERROR: Failed to create APP, maybe you already installed? \nExiting...\n");
			  sceKernelDelayThread(3*1000*1000);
      	sceKernelExitGame();
		  }
      pspDebugScreenPrintf("Creating ms0:/PSP/APP/NPIA00013/...\n");

      int mdpro2;
      mdpro2 = sceIoMkdir("ms0:/PSP/APP/NPIA00013", 0777);
      if(mdpro2 < 0){
        pspDebugScreenSetTextColor(RED);
			  pspDebugScreenPrintf("ERROR: Failed to create NPIA00013, maybe you already installed? \nExiting...\n");
			  sceKernelDelayThread(3*1000*1000);
      	sceKernelExitGame();
		  }

      pspDebugScreenPrintf("Copying SensMe PRO-C2 launcher to ms0:/PSP/APP/NPIA00013/...\n");
      copy_file("/sensme/pro661/NPIA00013/EBOOT.PBP","ms0:/PSP/APP/NPIA00013/EBOOT.PBP");
      pspDebugScreenPrintf("\nDone! Exiting...");
      sceKernelDelayThread(3*1000*1000);
      sceKernelExitGame();
      		}


    if (pad.Buttons & PSP_CTRL_CIRCLE) //LME 2.3
			{
        if ((n1000 == 1)){ // PSP GO ROUTE
          pspDebugScreenPrintf("\n\nPSP Go detected! Starting...\n");
          pspDebugScreenPrintf("Creating ef0:/PSP/APP/...\n");

          int mdprogo;
          mdprogo = sceIoMkdir("ef0:/PSP/APP", 0777);
            if(mdprogo < 0){
              pspDebugScreenSetTextColor(RED);
			        pspDebugScreenPrintf("ERROR: Failed to create APP, maybe you already installed? \nExiting...\n");
			        sceKernelDelayThread(3*1000*1000);
      	      sceKernelExitGame();
		        }
          pspDebugScreenPrintf("Creating ef0:/PSP/APP/NPIA00013/...\n");

          int mdprogo2;
          mdprogo2 = sceIoMkdir("ef0:/PSP/APP/NPIA00013", 0777);
            if(mdprogo2 < 0){
              pspDebugScreenSetTextColor(RED);
			        pspDebugScreenPrintf("ERROR: Failed to create NPIA00013, maybe you already installed? \nExiting...\n");
			        sceKernelDelayThread(3*1000*1000);
      	      sceKernelExitGame();
		        }

          pspDebugScreenPrintf("Copying SensMe LME 2.3 launcher to ef0:/PSP/APP/NPIA00013/...\n");
          copy_file("/sensme/lme661/NPIA00013/EBOOT.PBP","ef0:/PSP/APP/NPIA00013/EBOOT.PBP");
          pspDebugScreenPrintf("\nDone! Exiting...");
          sceKernelDelayThread(3*1000*1000);
          sceKernelExitGame();
        }

      // DEFAULT ROUTE (NON-GO)
      pspDebugScreenPrintf("\n\nStarting...\n");
      pspDebugScreenPrintf("Creating ms0:/PSP/APP/...\n");

      int mdlme; 
      mdlme = sceIoMkdir("ms0:/PSP/APP", 0777);
      if(mdlme < 0){
        pspDebugScreenSetTextColor(RED);
			  pspDebugScreenPrintf("ERROR: Failed to create APP, maybe you already installed? \nExiting...\n");
			  sceKernelDelayThread(3*1000*1000);
      	sceKernelExitGame();
		  }
      pspDebugScreenPrintf("Creating ms0:/PSP/APP/NPIA00013/...\n");

      int mdlme2;
      mdlme2 = sceIoMkdir("ms0:/PSP/APP/NPIA00013", 0777);
      if(mdlme2 < 0){
        pspDebugScreenSetTextColor(RED);
			  pspDebugScreenPrintf("ERROR: Failed to create NPIA00013, maybe you already installed? \nExiting...\n");
			  sceKernelDelayThread(3*1000*1000);
      	sceKernelExitGame();
		  }
      pspDebugScreenPrintf("Copying SensMe LME 2.3 launcher to ms0:/PSP/APP/NPIA00013/...\n");
      copy_file("/sensme/lme661/NPIA00013/EBOOT.PBP","ms0:/PSP/APP/NPIA00013/EBOOT.PBP");
      pspDebugScreenPrintf("\nDone! Exiting...");
      sceKernelDelayThread(3*1000*1000);
      sceKernelExitGame();
    		}


      if (pad.Buttons & PSP_CTRL_SQUARE)
			{
        if ((n1000 == 1)){ // PSP GO ROUTE
        pspDebugScreenPrintf("\n\nPSP Go detected! Uninstalling...\n");
        pspDebugScreenPrintf("Deleting ef0:/PSP/APP/NPIA00013/EBOOT.PBP...\n");

        int rfgo;
        rfgo = sceIoRemove("ef0:/PSP/APP/NPIA00013/EBOOT.PBP");
          if (rfgo < 0){
            pspDebugScreenSetTextColor(RED);
			      pspDebugScreenPrintf("ERROR: Failed to delete EBOOT.PBP, maybe you don't have it installed? \nExiting...\n");
			      sceKernelDelayThread(3*1000*1000);
      	    sceKernelExitGame();
          }

        pspDebugScreenPrintf("Deleting ef0:/PSP/APP/NPIA00013/...\n");
      
        int rdgo;
        rdgo = sceIoRmdir("ef0:/PSP/APP/NPIA00013");
	  	    if(rdgo < 0){
            pspDebugScreenSetTextColor(RED);
			      pspDebugScreenPrintf("ERROR: Failed to delete NPIA00013, maybe you don't have it installed? \nExiting...\n");
			      sceKernelDelayThread(3*1000*1000);
      	    sceKernelExitGame();
		      } 

          pspDebugScreenPrintf("Deleting ef0:/PSP/APP/...\n");

          int rdgo2;
          rdgo2 = sceIoRmdir("ef0:/PSP/APP");
	  	      if(rdgo2 < 0){
              pspDebugScreenSetTextColor(RED);
			        pspDebugScreenPrintf("ERROR: Failed to delete APP, maybe you don't have it installed? \nExiting...\n");
			        sceKernelDelayThread(3*1000*1000);
      	      sceKernelExitGame();
		        }
          pspDebugScreenPrintf("\nDone! Exiting...");
          sceKernelDelayThread(3*1000*1000);
          sceKernelExitGame();
        }
      
      // DEFAULT ROUTE (NON-GO)
      pspDebugScreenPrintf("\n\nUninstalling...\n");
      pspDebugScreenPrintf("Deleting ms0:/PSP/APP/NPIA00013/EBOOT.PBP...\n");
      int rf;
      rf = sceIoRemove("ms0:/PSP/APP/NPIA00013/EBOOT.PBP");
      if (rf < 0){
        pspDebugScreenSetTextColor(RED);
			  pspDebugScreenPrintf("ERROR: Failed to delete EBOOT.PBP, maybe you don't have it installed? \nExiting...\n");
			  sceKernelDelayThread(3*1000*1000);
      	sceKernelExitGame();
      }

      pspDebugScreenPrintf("Deleting ms0:/PSP/APP/NPIA00013/...\n");
      
      int rd;
      rd = sceIoRmdir("ms0:/PSP/APP/NPIA00013");
	  	if(rd < 0){
        pspDebugScreenSetTextColor(RED);
			  pspDebugScreenPrintf("ERROR: Failed to delete NPIA00013, maybe you don't have it installed? \nExiting...\n");
			  sceKernelDelayThread(3*1000*1000);
      	sceKernelExitGame();
		  }

      pspDebugScreenPrintf("Deleting ms0:/PSP/APP/...\n");

      int rd2;
      rd2 = sceIoRmdir("ms0:/PSP/APP");
	  	if(rd2 < 0){
        pspDebugScreenSetTextColor(RED);
			  pspDebugScreenPrintf("ERROR: Failed to delete APP, maybe you don't have it installed? \nExiting...\n");
			  sceKernelDelayThread(3*1000*1000);
      	sceKernelExitGame();
		  }
      pspDebugScreenPrintf("\nDone! Exiting...");
      sceKernelDelayThread(3*1000*1000);
      sceKernelExitGame();
     		}


    if (pad.Buttons & PSP_CTRL_TRIANGLE)
			{
      pspDebugScreenPrintf("\nExiting...\n");
      sceKernelDelayThread(3*1000*1000); 
      sceKernelExitGame();
      }
	}
}