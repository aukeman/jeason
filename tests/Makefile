CC=g++
CPPFLAGS=-I. -I.. -g

PROGRAM=main

CC_FILES:=$(wildcard *.cc)
OBJ_FILES:=$(patsubst %.cc, %.o, $(CC_FILES)) ../lex.yy.o ../jeason.tab.o 
DEP_FILES:=$(patsubst %.cc, .%.d, $(CC_FILES))

LDLIBS=-lcppunit 

TEST_OBJ_FILES:=$(wildcard ../*.o)

all : $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM) : $(OBJ_FILES) 

.%.d : %.cc
	echo -n "$@ " > $@
	g++ -MM -I. -I.. $< >> $@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEP_FILES)
endif

clean :
	rm -f *~
	rm -f $(PROGRAM)
	rm -f $(OBJ_FILES)
	rm -f $(DEP_FILES)
