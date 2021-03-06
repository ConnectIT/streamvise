MODULE_NAME=cit-udhcpd

# SIL Makefile for Yuma Server Instrumentation Library
#  

############### SOURCE PROFILE ##############################

SUBDIR_NM=$(MODULE_NAME)

SUBDIR_CPP=

############### TARGET PROFILE ##############################

ifndef PREFIX
    PREFIX=/usr
endif

TARGET=../bin

LIB_INST=../lib

WORK_INST=$(YUMA_HOME)/target/lib

ifdef LIB64
REAL_INST=$(DESTDIR)$(PREFIX)/lib64/yuma
else
REAL_INST=$(DESTDIR)$(PREFIX)/lib/yuma
endif


#################### MAKE RULES ########################

all: sil_dummy sil_lib

#################### PLATFORM DEFINITIONS ############
CINCBASE=$(DESTDIR)$(PREFIX)/include

CINC = -I. -I$(CINCBASE)/yuma/platform -I$(CINCBASE)/yuma/ncx \
     -I$(CINCBASE)/yuma/agt -I$(CINCBASE) -I$(CINCBASE)/libxml2 \
     -I$(CINCBASE)/libxml2/libxml

ifdef FREEBSD
CINC += -I/usr/local/include -I/usr/local/include/libxml2 \
     -I/usr/local/include/libxml2/libxml
endif

# added /sw/include for MacOSX
ifdef MAC
# MACOSX version
  CINC +=-I/sw/include
  CFLAGS += -DMACOSX=1
endif

LBASE=../lib

ifdef DESTDIR
OWNER=
else
ifdef MAC
OWNER=-oroot
else
ifdef CYGWIN
OWNER=
else
OWNER= --owner=root
endif
endif
endif

### GCC + [LINUX or MACOSX]

ifdef DEBUG
WERROR= -Werror
else
WERROR=
endif

CWARN=-Wall -Wno-long-long -Wformat-y2k -Winit-self \
	-Wswitch-default -Wunused-parameter \
	-Wextra -Wundef -Wshadow -Wpointer-arith \
	-Wwrite-strings -Wbad-function-cast -Wcast-qual -Wcast-align \
	-Waggregate-return -Wstrict-prototypes -Wold-style-definition \
	-Wmissing-prototypes -Wmissing-declarations \
	-Wpacked -Winvalid-pch \
	-Wredundant-decls -Wnested-externs -Winline -std=gnu99 $(WERROR)


# -Wunreachable-code removed due to -O3
# -O3 changed to -O2 due to code bloat from inline functions

CDEFS=-DDEBUG=1 -DLINUX=1 -DGCC=1

ifndef NOFLOAT
  CDEFS += -DHAS_FLOAT=1
endif

# production (0) or debug (1) build
ifdef DEBUG
  CFLAGS += -ggdb3
else
  CFLAGS += -O2
endif

CFLAGS += $(CDEFS) $(CWARN)

ifndef CYGWIN
   CFLAGS += -fPIC
endif

# memory leak debugging mode
ifdef MEMTRACE
  CFLAGS += -DMEMORY_DEBUG=1
endif

ifdef RELEASE
  CFLAGS += -DRELEASE=$(RELEASE)
endif

ifdef LIB64
   CFLAGS += -DLIB64=1
endif


ifdef MAC
   GRP=
else
ifdef DESTDIR
   GRP=
else
ifdef CYGWIN
   GRP=
else
   GRP=--group=root
endif
endif
endif

ifdef STATIC
LIBSUFFIX=a
else
ifdef MAC
LIBSUFFIX=dylib
else
LIBSUFFIX=so
endif
endif

CC?=gcc
LINK?=$(CC)
LINT=splint
LINTFLAGS= '-weak -macrovarprefix "m_"'
##LIBFLAGS=-lsocket

LIBTOOL=ar
#LFLAGS=-v --no-as-needed
LFLAGS=-lm
LPATH=-L$(LBASE)

CEES = $(wildcard *.c)

HEES = $(wildcard *.h)

ifdef YUMA_HOME
LAGT= -L$(YUMA_HOME)/target/lib -lagt -lncx
else
LAGT=
endif


################ OBJS RULE #############
OBJS = $(patsubst %.c,$(TARGET)/%.o,$(CEES))

################ DEPS RULE #############
DEPS = $(patsubst %.c,%.D,$(wildcard *.c))

######################## PLATFORM DEFINITIONS #############
PLATFORM_CPP=

.PHONY: all superclean clean test install uninstall \
        distclean depend lint

######################### MAKE DEPENDENCIES ###############
COMPILE.c= $(CC) $(CFLAGS) $(CPPFLAGS) $(PLATFORM_CPP) \
           $(CINC) $(SUBDIR_CPP) $(TARGET_ARCH) -c


$(TARGET)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(PLATFORM_CPP) \
        $(CINC) $(SUBDIR_CPP) $(TARGET_ARCH) -c -o $@ $< 


# Common library rule

$(LBASE)/lib%.a: $(OBJS)
	$(LIBTOOL) cr $@ $(OBJS)
	ranlib $@

# dependency rule to make temp .D files from .c sources
# all the .D files are collected and appended to the
# appropriate Makefile when 'make depend' is run
# this rule is kept here to make sure it matches COMPILE.c
%.D: %.c
	$(CC) -MM -MG -MT $(TARGET)/$(patsubst %.c,%.o,$<) \
	-Wall -Wcomment $(CPPFLAGS) $(PLATFORM_CPP) $(CINC) \
	$(SUBDIR_CPP) $(TARGET_ARCH) -c $< > $@


################## MAKE DEPENDENCIES #####################
# following depend rule is the GNU version! Other versions TBD
depend: dependencies

dependencies: $(DEPS)
	@if [ ! -f Makefile ]; then \
	    echo "Error: Makefile missing!"; \
	    exit 1; \
	fi
	@rm -f dependencies
	@for i in $(DEPS); do \
	  if [ -f $$i ] ; then \
	    (cat $$i >> dependencies; echo "" >> dependencies) ; \
	  else \
	    (echo "*** Warning: Dependency file $i.D is missing! (Skipping...) ***"; \
	     echo "# Warning: Missing file $$i !!!") ; \
	  fi; \
	done
	@echo "" >> dependencies
# delete the .D files to force make depend to rebuild them each time
# that target is built
#	@rm -f $(DEPS)


test:

install:
	mkdir -p $(REAL_INST)
	install $(LIB_INST)/lib$(SUBDIR_NM).$(LIBSUFFIX) $(REAL_INST)

work:
ifdef YUMA_HOME
	mkdir -p $(WORK_INST)        
	install $(LIB_INST)/lib$(SUBDIR_NM).$(LIBSUFFIX) $(WORK_INST)
endif

sil_lib: $(LIB_INST)/lib$(SUBDIR_NM).$(LIBSUFFIX)

# this dummy rule keeps make from deleting the $(OBJS) as
# intermediate files
sil_dummy: dependencies $(OBJS)

clean:
	rm -f $(OBJS) $(LIB_INST)/lib$(SUBDIR_NM).*

superclean:
	rm -f *~  $(DEPS) dependencies $(OBJS) \
	$(LIB_INST)/lib$(SUBDIR_NM).*

ifdef FREEBSD
ADD_DL=
else
ADD_DL=-ldl  -L../lib -lcit-helper
endif

$(LIB_INST)/lib$(SUBDIR_NM).so: $(OBJS)
	$(LINK) $(CFLAGS) $(LDFLAGS) -shared -rdynamic -Wl,-soname,lib$(SUBDIR_NM).so -o $@ $(OBJS) $(ADD_DL) $(LAGT)


$(LBASE)/lib$(SUBDIR_NM).dylib: $(OBJS)
	$(LINK) $(CFLAGS) $(LDFLAGS) -shared -dynamiclib -std=gnu99 -current_version 1.0 \
	-undefined dynamic_lookup \
	-o $@ -install_name lib$(SUBDIR_NM).dylib $(OBJS) -lxml2

code:
	yangdump format=h indent=4 module=$(SUBDIR_NM) output=$(SUBDIR_NM).h
	yangdump format=c indent=4 module=$(SUBDIR_NM) output=$(SUBDIR_NM).c


# prevent the make program from choking on all the symbols
# that get generated from autogenerated make rules
.NOEXPORT:

include dependencies
