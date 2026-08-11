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

//hold all four together to land and quit
#define exitCombo (SCE_CTRL_LTRIGGER | SCE_CTRL_RTRIGGER | SCE_CTRL_SELECT | SCE_CTRL_START)

int rc(int a);

int main()
{
	debugNetInit(ip_server,port_server,DEBUG);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    SceCtrlData ctrl = {0};
    sceKernelDelayThread(5*1000*1000);
	debugNetUDPPrintf("%s","command");
    sceKernelDelayThread(5*1000*1000);
    debugNetUDPPrintf("%s","speed 100");
    do{
        sceKernelDelayThread(100*1000);
        unsigned int previousButtons = ctrl.buttons;
        sceCtrlPeekBufferPositive(0, &ctrl, 1);
        unsigned int pressedButtons = ((previousButtons ^ ctrl.buttons) & ctrl.buttons); //determine which buttons have just been depressed; 1 for pressed, 0 for anything else

        if((ctrl.buttons & exitCombo) == exitCombo) break;

        //test with & rather than ==, so a command still fires when another button is held at the same time
        if(pressedButtons & SCE_CTRL_TRIANGLE) debugNetUDPPrintf("%s","emergency");
        else if(pressedButtons & SCE_CTRL_CROSS) debugNetUDPPrintf("%s","takeoff");
        else if(pressedButtons & SCE_CTRL_CIRCLE) debugNetUDPPrintf("%s","land");
        else if(pressedButtons & SCE_CTRL_SELECT) debugNetUDPPrintf("%s","speed 50");
        else if(pressedButtons & SCE_CTRL_START) debugNetUDPPrintf("%s","speed 100");
        else debugNetUDPPrintf("rc %i %i %i %i", rc(ctrl.rx), -1 * rc(ctrl.ry), -1 * rc(ctrl.ly), rc(ctrl.lx));
    }while(1);

    //never leave the Tello holding the last rc command we sent: centre the
    //sticks, then land, before we stop talking to it
    debugNetUDPPrintf("%s","rc 0 0 0 0");
    sceKernelDelayThread(100*1000);
    debugNetUDPPrintf("%s","land");
    sceKernelDelayThread(500*1000);

	debugNetFinish();
	sceKernelExitProcess(0);
	return 0;
}

int rc(int a){
    if(a < 128 + stickDeadzone && a >= 128 - stickDeadzone) return 0;
    if(a < 128) return stickMultiplier * (a - 128 + 1 + stickDeadzone);
    return stickMultiplier * (a - 128 - stickDeadzone);
}
