SHELL=/bin/bash
CXX=g++
#OPT = -O2 -DNDEBUG # production use
OPT=-g2   #debug mode

CPPFLAGS=$(OPT) -I.
LDFLAGS= 
#extract all cpp sources
SOURCES=$(wildcard \
	net/*.cpp \
	db/*.cpp \
	fs/*.cpp \
	)

#each cpp file should be an object file
LIBOBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

LIBRARY = libpio.a


all: $(LIBRARY)

dependless = %.o %.a %.d %.h
expand = $($(var)) $(var) $(var).d
depend_test = $(if $(filter $(dependless),$(var)),$(var),$(expand))
depend = $(sort $(foreach var,$(1),$(depend_test)))

#auto generates all .o and .cpp.d dependencies
$(LIBRARY): $(call depend, $(SOURCES)) $(LIBOBJECTS)
	rm -f $@
	$(AR) -rs $@ $(LIBOBJECTS)


# used to generate the dependencies file and .o dependencies: .o need to be added by the dirctory name
%.cpp.d: %.cpp
	$(CXX) -M $(CPPFLAGS) $< | sed 's:$(notdir $*).o:$*.o $@:g' > $@

clean:
	-rm -f *.o *.d net/*.o net/*.d db/*.o db/*.d fs/*.o fs/*.d
	-rm -f *.a

# Include automatically generated dependency files  
-include $(wildcard *.d */*.d)
