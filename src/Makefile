all: compiler

OBJS = 	ast.o\
		context.o \
		type_system.o \
		syn.o \
		lex.o  \
		main.o \

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++17
LDFLAGS = `$(LLVMCONFIG) --ldflags` -lpthread -ldl -lz -lncurses -rdynamic -L/usr/lib
LIBS = `$(LLVMCONFIG) --libs`

clean:
	$(RM) -rf test compiler *.output $(OBJS)

ast.cpp: ast.h

context.cpp: context.h ast.h

type_system.cpp: type_system.h

syn.cpp: syn.y
	bison -d -o $@ $<

syn.hpp: syn.cpp

lex.cpp: lex.l syn.hpp
	flex -o $@ $<

%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $<

compiler: $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)

