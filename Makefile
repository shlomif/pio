SHELL=/bin/bash
CXX=g++
CC=gcc
#OPT = -O2 -DNDEBUG # production use
OPT=-g2   #debug mode

CPPFLAGS=$(OPT) -I. -Idb/leveldb/include
LDFLAGS= -L. -lev -lleveldb
#extract all cpp sources
SOURCES=$(wildcard \
	net/*.cpp \
	db/*.cpp \
	fs/*.cpp \
	utils/*.cpp\
	./*.cpp \
	)


#each cpp file should be an object file
LIBOBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

LIBRARY = libpio.a
LEVELDB = libleveldb.a
SNAPPY  = snappy-install
CARES_LIB = libcares.a


ifneq ($(wildcard config-host.mak),)
all: $(LIBRARY) $(LEVELDB) $(CARES_LIB)
include config-host.mak
config-host.mak: configure
	@echo $@ is out-of-date, running configure	
	@sed -n "/.*Configured with/s/[^:]*: //p" $@ | sh
else
config-host.mak:
	@echo "Please call configure before running make"
	@exit 1
endif

include ares.makefile


dependless = %.o %.a %.d %.h
expand = $($(var)) $(var) $(var).d
depend_test = $(if $(filter $(dependless),$(var)),$(var),$(expand))
depend = $(sort $(foreach var,$(1),$(depend_test)))

#auto generates all .o and .cpp.d dependencies
$(LIBRARY): $(call depend, $(SOURCES)) $(LIBOBJECTS)
	rm -f $@
	$(AR) -rs $@ $(LIBOBJECTS)

$(LEVELDB): 
	make -C db/leveldb
	mv db/leveldb/$@ ./
	make -C db/leveldb clean

$(CARES_OBJS): %.o: %.c
	$(CC) -o $*.o -c $(CFLAGS)  $< -DHAVE_CONFIG_H

$(CARES_LIB): $(CARES_OBJS)
	$(AR) -rs $@ $(CARES_OBJS)

# used to generate the dependencies file and .o dependencies: .o need to be added by the dirctory name
%.cpp.d: %.cpp
	$(CXX) -M $(CPPFLAGS) $< | sed 's:$(notdir $*).o:$*.o $@:g' > $@

TEST_SOURCES=$(wildcard test/*.cpp)
TEST_OBJECTS = $(patsubst %.cpp, %.o, $(TEST_SOURCES))
TEST_EXEC=test/test_tcp_server test/test_tcp_client test/test_timer

test: $(call depend, $(TEST_SOURCES)) $(TEST_OBJECTS) $(TEST_EXEC) 

test/test_tcp_server: test/test_tcp_server.o $(LIBRARY)
	$(CXX) $(CPPFLAGS) -L. -lpio $(LDFLAGS) -o $@ $<

test/test_tcp_client: test/test_tcp_client.o $(LIBRARY)
	$(CXX) $(CPPFLAGS) -L. -lpio $(LDFLAGS) -o $@ $<	

test/test_timer: test/test_timer.o $(LIBRARY)
	$(CXX) $(CPPFLAGS) -L. -lpio $(LDFLAGS) -o $@ $<

clean:
	-rm -f *.o *.d net/*.o net/*.d db/*.o db/*.d fs/*.o fs/*.d dns/ares/*.o
	-rm -f $(TEST_EXEC)
	-rm -f test/*.d test/*.o


# Include automatically generated dependency files  
-include $(wildcard *.d */*.d)
