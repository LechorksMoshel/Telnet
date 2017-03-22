CXX            = g++
CXXFLAGS       = -fPIC -Wall -O3 -g
GLIBS          = -stdlib=libc++ -pthread 

INCLUDEDIR       = ./include/
SRCDIR           = ./src/
CXX	         += -I$(INCLUDEDIR) -I.
OUTOBJ	         = ./obj/

CC_FILES := $(wildcard src/*.cxx)
HH_FILES := $(wildcard include/*.h)
OBJ_FILES := $(addprefix $(OUTOBJ),$(notdir $(CC_FILES:.cxx=.o)))

all: telnet_serv

telnet_serv:  $(SRCDIR)telnet_serv.C $(OBJ_FILES) $(HH_FILES)
	echo $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o telnet_serv $(OBJ_FILES) $(GLIBS) $ $<
	echo $(OBJ_FILES)
	touch telnet_serv

$(OUTOBJ)%.o: src/%.cxx include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OUTOBJ)*.o
	rm -rf *.dSYM
	rm -f telnet_serv
