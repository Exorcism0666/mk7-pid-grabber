.SUFFIXES:

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR 		?= 	$(CURDIR)
include $(DEVKITARM)/3ds_rules

CTRPFLIB	?=	$(DEVKITPRO)/libctrpf

#DEBUG_BUILD	:=	true

DATE		:=	$(shell date '+%Y-%m-%d %H:%M:%S')

GITHUB		:=	https://github.com/H4x0rSpooky/mk7-pid-grabber
CREATOR		:=	H4x0rSpooky
DISCORD		:=	discord.gg/QGUNRK9Xw7

NAME		:=	mk7-pid-grabber

ifeq ($(DEBUG_BUILD),true)
NAME		:=	$(NAME)_dev
endif

ABOUT		:=	$(NAME) is a Principal ID grabbing tool for Mario Kart 7 created by $(CREATOR).\n\nGithub Repository: $(GITHUB)\n\nDiscord Server: $(DISCORD)\n\nUpdate: $(DATE)

MAJOR		:=	1
MINOR		:= 	0
REV			:=	1

TARGET		:= 	$(notdir $(CURDIR))
PLGINFO 	:= 	ctrpf.plgInfo

BUILD		:= 	build
DEBUG		:=	debug

INCLUDES	:= 	include \
				include/ctrpf \
				include/glaze \
				include/magic_enum \
				include/base

SOURCES 	:= 	src \
				src/base \
				src/base/entries \
				src/base/features \
				src/base/hook_types \
				src/base/hooks \
				src/base/memory \
				src/base/services

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH		:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

DEFINES 	:=	-D__3DS__ -DNNSDK -DGITHUB="\"$(GITHUB)\"" -DCREATOR="\"$(CREATOR)\"" -DDISCORD="\"$(DISCORD)\"" -DNAME="\"$(NAME)\"" \
				-DABOUT="\"$(ABOUT)\"" -DMAJOR="\"$(MAJOR)\"" -DMINOR="\"$(MINOR)\"" -DREV="\"$(REV)\"" -DDATE="\"$(DATE)\""

ifeq ($(DEBUG_BUILD),true)
DEFINES		:= $(DEFINES) -D_DEBUG
endif

CFLAGS		:= $(ARCH) -Os -mword-relocations -fomit-frame-pointer -ffunction-sections -fno-strict-aliasing -Wno-psabi
CFLAGS		+= $(INCLUDE) $(DEFINES)

CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++23

ASFLAGS		:= $(ARCH)
LDFLAGS		:= -T $(TOPDIR)/3gx.ld $(ARCH) -Os -fno-lto -Wl,--gc-sections,--strip-discarded

ifneq ($(DEBUG_BUILD),true)
LDFLAGS		:= $(LDFLAGS),--strip-debug
endif

LIBS		:= -lctrpf -lctru
LIBDIRS		:= $(CTRPFLIB) $(CTRULIB) $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(NAME)
export TOPDIR	:=	$(CURDIR)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES			:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES			:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

export LD 		:= 	$(CXX)
export OFILES	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I $(CURDIR)/$(dir) ) \
					$(foreach dir,$(LIBDIRS),-I $(dir)/include) \
					-I $(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L $(dir)/lib)

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------
all: $(BUILD)

$(BUILD):
	@rm -fr $(DEBUG) *.3gx *.elf
ifeq ($(DEBUG_BUILD),true)
		@[ -d $(DEBUG) ] || mkdir -p $(DEBUG)
endif
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(DEBUG) $(BUILD) *.3gx *.elf

re: clean all

#---------------------------------------------------------------------------------

else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).3gx : $(OFILES)

#---------------------------------------------------------------------------------
# you need a rule like this for each extension you use as binary data
#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
ifeq ($(DEBUG_BUILD),true)
.PRECIOUS: %.elf
endif

%.3gx: %.elf
#---------------------------------------------------------------------------------
	@echo creating $(notdir $@)
ifeq ($(DEBUG_BUILD),true)
	@3gxtool -s $(word 1, $^) $(TOPDIR)/$(PLGINFO) $@
	@-mv $(TOPDIR)/$(BUILD)/*.lst $(TOPDIR)/$(DEBUG)/
	@-mv $(TOPDIR)/*.elf $(TOPDIR)/$(DEBUG)/
else
	@3gxtool -d -s $(word 1, $^) $(TOPDIR)/$(PLGINFO) $@
endif
	@echo $(NAME).3gx successfully created!

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
