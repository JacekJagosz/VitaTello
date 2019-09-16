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

#define stickDeadzone 10
const float stickMultiplier = (float)101/(128-stickDeadzone);
int rc(int a);

int main()
{
	debugNetInit(ip_server,port_server,DEBUG);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    SceCtrlData ctrl;
    sceKernelDelayThread(5*1000*1000);
	debugNetPrintf(-1,"command");
    sceKernelDelayThread(5*1000*1000);
    do{
        sceKernelDelayThread(100*1000);
        unsigned int previousButtons = ctrl.buttons;
        sceCtrlPeekBufferPositive(0, &ctrl, 1);
        unsigned int pressedButtons = ((previousButtons ^ ctrl.buttons) & ctrl.buttons); //determine which buttons have just been depressed; 1 for pressed, 0 for anything else
        if(pressedButtons == SCE_CTRL_TRIANGLE) debugNetPrintf(-1,"emergency");
        else if(pressedButtons == SCE_CTRL_CROSS) debugNetPrintf(-1,"takeoff");
        else if(pressedButtons == SCE_CTRL_CIRCLE) debugNetPrintf(-1,"land");
        else debugNetPrintf(-1,"rc %i %i %i %i", rc(ctrl.rx), -1 * rc(ctrl.ry), -1 * rc(ctrl.ly), rc(ctrl.lx));
    }while(1);
    
	debugNetFinish();
	sceKernelExitProcess(0);
	return 0;
}

int rc(int a){
    if(a < 128 + stickDeadzone && a >= 128 - stickDeadzone) return 0;
    if(a < 128) return stickMultiplier * (a - 128 + 1 + stickDeadzone);
    if(a >= 128) return stickMultiplier * (a - 128 - stickDeadzone);
}
