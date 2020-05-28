all: main

OBJS = 	test.o\
		io.o \

test.o: test.cmm
	./clang-- -i $< -o $@

clean:
	$(RM) test.o main *.ll

main: $(OBJS)
	gcc $(OBJS) -o $@
