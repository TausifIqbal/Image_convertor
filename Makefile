LIBDIR 	     	:= libs
LIBDIRDYNAMIC	:= libsdynamic
OBJDIR 			:= obj
EXEDIR 			:= bin

EXE 			:= $(EXEDIR)/calc
LIBS 			:= $(addprefix $(LIBDIR)/,libimage.a libmatrixmath.a)
LIBSD 			:= $(addprefix $(LIBDIRDYNAMIC)/,libimage.so libmatrixmath.so)
OBJS 			:= $(addprefix $(OBJDIR)/,$(patsubst src/%.c,%.o,$(wildcard src/*.c)))
OBJSD 			:= $(addprefix $(LIBDIRDYNAMIC)/,$(patsubst src/%.c,%.o,$(wildcard src/*.c)))

vpath %.c src
all: build
	

build: $(EXE) |  output
	@echo "compilation done and executable produced"

$(EXE): obj/main.o liba | $(EXEDIR)
	gcc -o $@ -I include $< -L libs -limage -lmatrixmath

$(OBJDIR)/%.o: %.c include/calc.h | $(OBJDIR)
	gcc -o $@ -c -I include $<

$(LIBDIR)/libimage.a: obj/read_write.o obj/grayscale.o obj/blurRGB.o | $(LIBDIR)
	ar rcs $@ $^

$(LIBDIR)/libmatrixmath.a: obj/Product.o | $(LIBDIR)
	ar rcs $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(LIBDIRDYNAMIC):
	mkdir -p $(LIBDIRDYNAMIC)

$(EXEDIR):
	mkdir -p $(EXEDIR)

output:
	mkdir -p output
run: build
	./bin/calc

liba: $(LIBS)
	@echo "static-linked library created"

$(LIBDIRDYNAMIC)/%.o: %.c include/calc.h | $(LIBDIRDYNAMIC)
	gcc -fPIC -o $@ -c -I include $<

$(LIBDIRDYNAMIC)/libimage.so: libsdynamic/read_write.o libsdynamic/grayscale.o libsdynamic/blurRGB.o | $(LIBDIRDYNAMIC)
	gcc -shared -o $@ $^

$(LIBDIRDYNAMIC)/libmatrixmath.so: libsdynamic/Product.o | $(LIBDIRDYNAMIC)
	gcc -shared -o $@ $^
	
libso: $(LIBSD)
	@echo "dynamic-linked library created"
	
bin/calc_d:obj/main.o libso | $(EXEDIR)
	gcc -o $@ -I include $< -L libsdynamic -limage -lmatrixmath
	

T1:
	./bin/calc < ./src/T1.txt
T2:
	./bin/calc < ./src/T2.txt


test1:
	./bin/calc < ./src/test1.txt 
test2:
	./bin/calc < ./src/test2.txt 
test3:
	./bin/calc < ./src/test3.txt 

tests: test1 test2 test3
		@echo "all cases covered"


.PHONY: clean
clean:
		rm -rf $(EXEDIR) $(OBJDIR) $(LIBDIR) $(LIBDIRDYNAMIC) output
