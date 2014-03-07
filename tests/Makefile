CC=g++
CPPFLAGS=-I. -I../include -g -fpic

LDFLAGS=-L../lib -fpic -Wl,-rpath="../lib"

PROGRAM=main

CC_FILES:=$(wildcard *.cc)
OBJ_FILES:=$(patsubst %.cc, %.o, $(CC_FILES)) 
DEP_FILES:=$(patsubst %.cc, .%.d, $(CC_FILES)) 

LDLIBS=-lcppunit -ljeason

.PHONY: jeason

all : jeason $(PROGRAM)
	./$(PROGRAM)

jeason:
	make -C ..

$(PROGRAM) : $(OBJ_FILES)


.%.d : %.cc
	echo -n "$@ " > $@
	g++ -fpic -MM -I. -I../include $< >> $@

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