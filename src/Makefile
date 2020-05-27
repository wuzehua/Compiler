all: compiler

OBJS = 	ast.o\
		context.o \
		type_helper.o \
		syn.o \
		lex.o  \
		main.o \

LLVMCONFIG = llvm-config
CPPFLAGS = `$(LLVMCONFIG) --cppflags` -std=c++17
LDFLAGS = `$(LLVMCONFIG) --ldflags` -L/usr/lib
LIBS = `$(LLVMCONFIG) --libs`
BUILD_DIR = ../build

clean:
	$(RM) -rf test compiler *.output $(BUILD_DIR)/$(OBJS)

ast.cpp: ast.h

context.cpp: context.h ast.h

type_helper.cpp: type_helper.h

syn.cpp: syn.y
	bison -d -o $@ $<

syn.hpp: syn.cpp

lex.cpp: lex.l syn.hpp
	flex -o $@ $<

%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $(BUILD_DIR)/$@ $<

compiler: $(OBJS)
	g++ $(CPPFLAGS) -o $(BUILD_DIR)/$@ $(BUILD_DIR)/*.o $(LIBS) $(LDFLAGS)

