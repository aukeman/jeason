CC=g++
CPPFLAGS=-Isrc -Iinclude -g -fpic

LIB=lib/libjeason.a
DSO=lib/libjeason.so

PRECOMPILED_HEADER=include/jeason/jeason.h.gch
PRECOMPILED_HEADER_DEP=include/jeason/.jeason.d

GENERATED_SRC_FILES=src/jeason.tab.c src/lex.yy.c
GENERATED_HDR_FILES=src/jeason.tab.h

OBJ_FILES:=$(patsubst src/%.c, src/%.o, $(GENERATED_SRC_FILES))
DEP_FILES:=$(patsubst src/%.c, src/.%.d, $(GENERATED_SRC_FILES)) $(PRECOMPILED_HEADER_DEP)

all: $(PRECOMPILED_HEADER) $(LIB) $(DSO)

$(DSO): $(OBJ_FILES)
	g++ -fpic -shared -o $@ $(OBJ_FILES)

$(LIB): $(LIB)($(OBJ_FILES))

.%.d : %.cc
	echo -n "$@ " > $@
	g++ -MM -Isrc -Iinclude $< >> $@

.%.d : %.c
	echo -n "$@ " > $@
	g++ -MM -Isrc -Iinclude $< >> $@

.%.d : %.h
	echo -n "$@ " > $@
	g++ -MM -Isrc -Iinclude $< -MT $<.gch >> $@


$(PRECOMPILED_HEADER): $(patsubst %.gch, %, $(PRECOMPILED_HEADER))
	$(CC) $(CPPFLAGS) -c -o $@ $<

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),clobber)
ifneq ($(MAKECMDGOALS),rebuild)
-include $(DEP_FILES)
endif
endif
endif

$(GENERATED_SRC_FILES) $(GENERATED_HDR_FILES) : src/jeason.y src/jeason.l
	bison -d -o src/jeason.tab.c src/jeason.y 
	flex -o src/lex.yy.c src/jeason.l 

clean :
	rm -f ./*~ ./src/*~ ./include/*~ ./include/jeason/*~ ./include/jeason/impl/*~
	rm -f $(GENERATED_SRC_FILES) $(GENERATED_HDR_FILES) $(DEP_FILES)
	rm -f $(OBJ_FILES)

clobber : clean
	rm -f $(LIB)
	rm -f $(DSO)

rebuild : clobber $(DEP_FILES) all