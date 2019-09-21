cmake_minimum_required(VERSION 3.0)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else()
        message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif()
endif()

project(VitaTello)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_TITLEID "JAGJ00001")
set(VITA_VERSION  "00.01")

set(CFLAGS "-Wl,-q -Wall -O3")

include_directories(
    third_party/vita-enet/include/
)

add_executable(${PROJECT_NAME}.elf 
    src/main.c
    third_party/vita-enet/callbacks.c
	third_party/vita-enet/compress.c
	third_party/vita-enet/host.c
	third_party/vita-enet/list.c
	third_party/vita-enet/packet.c
	third_party/vita-enet/peer.c
	third_party/vita-enet/protocol.c
	third_party/vita-enet/vita.c
)
target_compile_options(${PROJECT_NAME}.elf PRIVATE ${CFLAGS})

target_link_libraries(${PROJECT_NAME}.elf
        c
	#debugnet
	SceNetCtl_stub
	SceNet_stub
	SceSysmodule_stub
	SceCtrl_stub
	ScePower_stub
	SceVideodec_stub
	SceCommonDialog_stub
	SceIme_stub
	)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME}.elf)
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
    VERSION ${VITA_VERSION}
	NAME ${PROJECT_NAME}
	FILE sce_sys/icon0.png sce_sys/icon0.png
    FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
    FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
    FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)
