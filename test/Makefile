all: test2 test4 test6

TEST2_OBJ = test2.o\
			io.o\

TEST4_OBJ = test4.o\
			io.o\

TEST6_OBJ = test6.o\
			io.o\

GUI_OBJ = test1.o\
		  OpenGL.o\
		  io.o\

io.o: io.c
	gcc -c $< -o $@

OpenGL.o: OpenGL.c
	gcc -c $< -o $@

test1.o: test1.cmm
	./clang-- -i $< -o $@ -d test1.puml

test2.o: test2.cmm
	./clang-- -i $< -o $@ -d test2.puml

test4.o: test4.cmm
	./clang-- -i $< -o $@ -d test4.puml

test6.o: test6.cmm
	./clang-- -i $< -o $@ -d test6.puml

clean:
	$(RM) *.o main *.elf *.ll *.puml *.dot .*.dot

test2: $(TEST2_OBJ)
	gcc $(TEST2_OBJ) -o $@.elf

test4: $(TEST4_OBJ)
	gcc $(TEST4_OBJ) -o $@.elf

test6: $(TEST6_OBJ)
	gcc $(TEST6_OBJ) -o $@.elf

gui: $(GUI_OBJ)
	gcc $(GUI_OBJ) -o $@.elf -lglfw -lglew -framework OpenGL -I/usr/local/include -L/usr/local/lib

cfg:
	llvm-as < test.ll | opt -analyze --dot-cfg -o main.dot

cfg2png:
	dot -Tpng .main.dot -o main.png

