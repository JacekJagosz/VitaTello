//#include <debugnet.h>
#include <enet/enet.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/ctrl.h>
#include <psp2/sysmodule.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <string.h>

#define PC
//#define TELLO

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

ENetAddress address;
ENetAddress pc;
ENetHost * server;
ENetPeer *peer;

int main()
{
	
    int ret = 0;

    ret = sceSysmoduleLoadModule(SCE_SYSMODULE_NET);

    size_t net_mem_sz = 100 * 1024;
    SceNetInitParam net_param = {0};
    net_param.memory = calloc(net_mem_sz, 1);
    net_param.size = net_mem_sz;
    ret = sceNetInit(&net_param);

    ret = sceNetCtlInit();
    sceKernelDelayThread(2*1000*1000);
    address.host = ENET_HOST_ANY;
    //address.port = port_server;
    server = enet_host_create (NULL, 32, 2, 0, 0);
    enet_address_set_host (& pc, "192.168.1.9");
    pc.port = port_server;
    ENetPacket * packet = enet_packet_create ("packet", strlen ("packet") + 1, ENET_PACKET_FLAG_RELIABLE);
    peer = enet_host_connect (server, & pc, 2, 0);
    enet_host_flush (server);
    enet_peer_send (peer, 0, packet);
    enet_host_flush (server);
    sceKernelDelayThread(5*1000*1000);
    /*debugNetInit(ip_server,port_server,DEBUG);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    SceCtrlData ctrl;
    sceKernelDelayThread(5*1000*1000);
	debugNetPrintf(-1,"command");
    sceKernelDelayThread(5*1000*1000);
    debugNetPrintf(-1,"speed 50");
    do{
        sceKernelDelayThread(100*1000);
        unsigned int previousButtons = ctrl.buttons;
        sceCtrlPeekBufferPositive(0, &ctrl, 1);
        unsigned int pressedButtons = ((previousButtons ^ ctrl.buttons) & ctrl.buttons); //determine which buttons have just been depressed; 1 for pressed, 0 for anything else
        if(pressedButtons == SCE_CTRL_TRIANGLE) debugNetPrintf(-1,"emergency");
        else if(pressedButtons == SCE_CTRL_CROSS) debugNetPrintf(-1,"takeoff");
        else if(pressedButtons == SCE_CTRL_CIRCLE) debugNetPrintf(-1,"land");
        else if(pressedButtons == SCE_CTRL_SELECT) debugNetPrintf(-1,"speed 50");
        else if(pressedButtons == SCE_CTRL_START) debugNetPrintf(-1,"speed 100");
        else debugNetPrintf(-1,"rc %i %i %i %i", rc(ctrl.rx), -1 * rc(ctrl.ry), -1 * rc(ctrl.ly), rc(ctrl.lx));
    }while(1);
    
	debugNetFinish();
    */
    enet_host_destroy(server);
    atexit (enet_deinitialize);
	sceKernelExitProcess(0);
	return 0;
}

int rc(int a){
    if(a < 128 + stickDeadzone && a >= 128 - stickDeadzone) return 0;
    if(a < 128) return stickMultiplier * (a - 128 + 1 + stickDeadzone);
    if(a >= 128) return stickMultiplier * (a - 128 - stickDeadzone);
}
