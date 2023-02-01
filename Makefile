TARGET=openspeed
OBJS=main.o

CFLAGS=
CXXFLAGS=$(CFLAGS) -std=c++14 -fno-rtti
ASFLAGS=$(CFLAGS)

BUILD_PRX=1
PSP_LARGE_MEMORY=1
PSP_FW_VERSION=500

EXTRA_TARGETS=EBOOT.PBP
PSP_EBOOT_TITLE=OpenSpeed Installer (v0.1a)
#PSP_EBOOT_ICON=ICON0.PNG

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak