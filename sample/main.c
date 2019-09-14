#include <debugnet.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>



#define ip_server "192.168.10.1"
#define port_server 8889
int main()
{
	int ret;
	ret=debugNetInit(ip_server,port_server,DEBUG);
    sceKernelDelayThread(5*1000*1000);
	debugNetPrintf(-1,"command");
    sceKernelDelayThread(5*1000*1000);
	debugNetPrintf(-1,"takeoff");
    sceKernelDelayThread(5*1000*1000);
	debugNetPrintf(-1,"land");
    sceKernelDelayThread(5*1000*1000);
    //debugNetPrintf(INFO,"Test info level\n");	
	debugNetFinish();
	sceKernelExitProcess(0);
	return 0;
}
