#include <debugnet.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/ctrl.h>

//#define PC
#define TELLO

#ifdef TELLO
#define ip_server "192.168.10.1"
#define port_server 8889
#endif

#ifdef PC
#define ip_server "192.168.1.9"
#define port_server 18194
#endif

int main()
{
	debugNetInit(ip_server,port_server,DEBUG);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    SceCtrlData ctrl;
    sceKernelDelayThread(5*1000*1000);
	debugNetPrintf(-1,"command");
    sceKernelDelayThread(5*1000*1000);
    do{
        unsigned int previousButtons = ctrl.buttons;
        sceCtrlPeekBufferPositive(0, &ctrl, 1);
        unsigned int pressedButtons = ((previousButtons ^ ctrl.buttons) & ctrl.buttons); //determine which buttons have just been depressed; 1 for pressed, 0 for anything else
        if(pressedButtons == SCE_CTRL_CROSS) debugNetPrintf(-1,"takeoff");
        else if(pressedButtons == SCE_CTRL_CIRCLE) debugNetPrintf(-1,"land");
    }while(1);
        
    
    /*
    debugNetInit(ip_server,port_server,DEBUG);
    sceKernelDelayThread(5*1000*1000);
	debugNetPrintf(-1,"command");
    sceKernelDelayThread(5*1000*1000);
	debugNetPrintf(-1,"takeoff");
    sceKernelDelayThread(5*1000*1000);
	debugNetPrintf(-1,"land");
    sceKernelDelayThread(5*1000*1000);
    //debugNetPrintf(INFO,"Test info level\n");	
    */
	debugNetFinish();
	sceKernelExitProcess(0);
	return 0;
}
