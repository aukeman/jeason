CC=g++
CPPFLAGS=-I. -g

PROGRAM=main

SRC_FILES=main.cc
HDR_FILES=jeason.h

GENERATED_SRC_FILES=jeason.tab.c lex.yy.c
GENERATED_HDR_FILES=jeason.tab.h

OBJ_FILES:=$(patsubst %.c, %.o, $(SRC_FILES) $(GENERATED_SRC_FILES))
OBJ_FILES:=$(patsubst %.cc, %.o, $(OBJ_FILES))

DEP_FILES:=$(patsubst %.c, .%.d, $(SRC_FILES) $(GENERATED_SRC_FILES))
DEP_FILES:=$(patsubst %.cc, .%.d, $(DEP_FILES))

$(PROGRAM) : $(OBJ_FILES)

$(OBJ_FILES) : $(HDR_FILES) $(SRC_FILES) $(GENERATED_SRC_FILES) $(DEP_FILES)

.%.d : %.cc
	echo -n "$@ " > $@
	g++ -MM -I. -I.. $< >> $@

.%.d : %.c
	echo -n "$@ " > $@
	g++ -MM -I. -I.. $< >> $@

-include $(DEP_FILES)

$(GENERATED_SRC_FILES) $(GENERATED_HDR_FILES) : jeason.y jeason.l
	bison -d jeason.y
	flex jeason.l

clean :
	rm -f $(GENERATED_SRC_FILES) $(GENERATED_HDR_FILES) $(DEP_FILES)
	rm -f $(OBJ_FILES)
	rm -f $(PROGRAM)

rebuild : clean $(PROGRAM)