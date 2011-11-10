SHELL=/bin/bash
CXX=g++
#OPT = -O2 -DNDEBUG # production use
OPT=-g2   #debug mode

CPPFLAGS=$(OPT) -I. -Idb/leveldb/include
LDFLAGS= -L. -lev -lleveldb
#extract all cpp sources
SOURCES=$(wildcard \
	net/*.cpp \
	db/*.cpp \
	fs/*.cpp \
	./*.cpp \
	)

#each cpp file should be an object file
LIBOBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

LIBRARY = libpio.a
LEVELDB = libleveldb.a
SNAPPY  = snappy-install
all: $(LIBRARY) $(LEVELDB)

dependless = %.o %.a %.d %.h
expand = $($(var)) $(var) $(var).d
depend_test = $(if $(filter $(dependless),$(var)),$(var),$(expand))
depend = $(sort $(foreach var,$(1),$(depend_test)))

#auto generates all .o and .cpp.d dependencies
$(LIBRARY): $(call depend, $(SOURCES)) $(LIBOBJECTS)
	rm -f $@
	$(AR) -rs $@ $(LIBOBJECTS)

$(LEVELDB): $(SNAPPY)
	make -C db/leveldb
	mv db/leveldb/$@ ./
	make -C db/leveldb clean

$(SNAPPY):
	echo "install snappy compression library"
	sudo make -C utils/snappy-1.0.4 install
	make -C utils/snappy-1.0.4 distclean

# used to generate the dependencies file and .o dependencies: .o need to be added by the dirctory name
%.cpp.d: %.cpp
	$(CXX) -M $(CPPFLAGS) $< | sed 's:$(notdir $*).o:$*.o $@:g' > $@

TEST_SOURCES=$(wildcard test/*.cpp)
TEST_OBJECTS = $(patsubst %.cpp, %.o, $(TEST_SOURCES))
TEST_EXEC=test/test_tcp_server test/test_tcp_client

test: $(call depend, $(TEST_SOURCES)) $(TEST_OBJECTS) $(TEST_EXEC) 

test/test_tcp_server: test/test_tcp_server.o $(LIBRARY)
	$(CXX) $(CPPFLAGS) -L. -lpio $(LDFLAGS) -o $@ $<

test/test_tcp_client: test/test_tcp_client.o $(LIBRARY)
	$(CXX) $(CPPFLAGS) -L. -lpio $(LDFLAGS) -o $@ $<	

clean:
	-rm -f *.o *.d net/*.o net/*.d db/*.o db/*.d fs/*.o fs/*.d
	-rm -f $(TEST_EXEC)
	-rm -f test/*.d test/*.o
# Include automatically generated dependency files  
-include $(wildcard *.d */*.d)
