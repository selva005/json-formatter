CC=gcc

JANSSON=./jansson-2.10
INCDIR=./include
BUILDDIR=./build
DEBUGDIR=./debug
BINDIR=$(BUILDDIR)/bin
OBJDIR=$(BUILDDIR)/obj
DBG_BINDIR=$(DEBUGDIR)/bin
DBG_OBJDIR=$(DEBUGDIR)/obj


vpath %.c ./src
vpath %.h ./include

COPTS=-std=gnu99
DBG_COPTS=$(COPTS) -g -Wall -fno-omit-frame-pointer
REL_COPTS=$(COPTS) -O3 -Werror -fomit-frame-pointer -DNDEBUG

IDIR=-I$(INCDIR) -I$(JANSSON)/src

REL_TARGETS = $(addprefix $(BINDIR)/, jsonf)
DEB_TARGETS = $(addprefix $(DBG_BINDIR)/, jsonf)

OBJS = jsonf.o
REL_OBJS = $(addprefix $(OBJDIR)/, $(OBJS))
DBG_OBJS = $(addprefix $(DBG_OBJDIR)/, $(OBJS))

all: init $(REL_TARGETS) $(DEB_TARGETS)

$(OBJDIR)/%.o: %.c
	$(CC) $(REL_COPTS) -c -o $@ $< $(IDIR)

$(BINDIR)/jsonf: $(REL_OBJS) $(JANSSON)/src/.libs/libjansson.a
	$(CC) $(REL_COPTS) -o $@ $^ $(IDIR)

$(DBG_OBJDIR)/%.o: %.c
	$(CC) $(DBG_COPTS) -c -o $@ $< $(IDIR)

$(DBG_BINDIR)/jsonf: $(DBG_OBJS) $(JANSSON)/src/.libs/libjansson.a
	$(CC) $(DBG_COPTS) -o $@ $^ $(IDIR)

$(JANSSON)/src/.libs/libjansson.a:
	cd $(JANSSON); ./configure && make

init:
	mkdir -p $(BINDIR) $(OBJDIR) $(DBG_OBJDIR) $(DBG_BINDIR)

clean:
	rm -rf $(BUILDDIR)
	rm -rf $(DEBUGDIR)
