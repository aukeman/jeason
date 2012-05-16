CC=g++
CPPFLAGS=-I. -I../include -g -fpic

LDFLAGS=

#-L../lib -Wl,-static -ljeason  -fpic

PROGRAM=main

CC_FILES:=$(wildcard *.cc)
OBJ_FILES:=$(patsubst %.cc, %.o, $(CC_FILES)) 
DEP_FILES:=$(patsubst %.cc, .%.d, $(CC_FILES))

LDLIBS=-lcppunit 

all : $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM) : $(OBJ_FILES) ../lib/libjeason.a

../lib/libjeason.so:
	make -C ..

.%.d : %.cc
	echo -n "$@ " > $@
	g++ -MM -I. -I../include $< >> $@

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),clobber)
ifneq ($(MAKECMDGOALS),rebuild)
-include $(DEP_FILES)
endif
endif
endif

clean :
	rm -f ./*~
	rm -f $(DEP_FILES)
	rm -f $(OBJ_FILES) 

clobber : clean
	rm -f $(PROGRAM)

rebuild : clobber $(DEP_FILES) all