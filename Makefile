CFLAGS = -Wall
CPPFLAGS = -MMD
LIBS = myPrintConsole/pr_lib.a myReadKey/rk_lib.a mySimpleComputer/sc_lib.a myBigChars/bc_lib.a myTerm/mt_lib.a 

all: sa_lib sc_lib mt_lib bc_lib rk_lib pr_lib sb_lib console font sat sbt

sc_lib:
	cd mySimpleComputer && $(MAKE) all
	
mt_lib:
	cd myTerm && $(MAKE) all

bc_lib:
	cd myBigChars && $(MAKE) all

rk_lib:
	cd myReadKey && $(MAKE) all

pr_lib:
	cd myPrintConsole && $(MAKE) all
	
sa_lib:
	cd simpleassembler && $(MAKE) all
	
sb_lib:
	cd simplebasic && $(MAKE) all
	
sat: console/sat

console/sat: console/sat.o simpleassembler/sa_lib.a $(LIBS)
	gcc $(CFLAGS) -o $@ $^

console/sat.o: console/sat.c 
	gcc -c $(CFLAGS) $(CPPFLAGS) -I . -o $@ $<
	
sbt: console/sbt

console/sbt: console/sbt.o simplebasic/sb_lib.a $(LIBS)
	gcc $(CFLAGS) -o $@ $^

console/sbt.o: console/sbt.c 
	gcc -c $(CFLAGS) $(CPPFLAGS) -I . -o $@ $<


font: console/font

console/font: console/font.o $(LIBS)
	gcc $(CFLAGS) -o $@ $^

console/font.o: console/font.c 
	gcc -c $(CFLAGS) $(CPPFLAGS) -I . -o $@ $<

console: console/console

console/console: console/console.o $(LIBS)
	gcc $(CFLAGS) -o $@ $^

console/console.o: console/console.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I . -o $@ $<
	
test: console/test

console/test: console/test.o
	gcc $(CFLAGS) -o $@ $^ -lm
	
console/test.o: console/test.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $<

clean:
	rm */*.[oad]
run_pr01:
	./console/pr01
run_console:
	./console/console
run_font:
	./console/font
	
	
.PHONY: clean test all run
	
-include console/test.d console/pr01.d
