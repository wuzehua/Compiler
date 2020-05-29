all: test2 test4 test6

TEST2_OBJ = test2.o\
			io.o\

TEST4_OBJ = test4.o\
			io.o\

TEST6_OBJ = test6.o\
			io.o\

io.o: io.c
	gcc -c $< -o $@

test2.o: test2.cmm
	./clang-- -i $< -o $@

test4.o: test4.cmm
	./clang-- -i $< -o $@

test6.o: test6.cmm
	./clang-- -i $< -o $@

clean:
	$(RM) *.o main test2 test4 test6 *.ll

test2: $(TEST2_OBJ)
	gcc $(TEST2_OBJ) -o $@

test4: $(TEST4_OBJ)
	gcc $(TEST4_OBJ) -o $@

test6: $(TEST6_OBJ)
	gcc $(TEST6_OBJ) -o $@

