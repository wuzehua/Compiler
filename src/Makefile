syn.cpp: syn.y
	bison -d -o $@ $<

syn.hpp: syn.cpp

lex.cpp: lex.l syn.hpp
	flex -o $@ $<