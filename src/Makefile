syn.cpp: syn.y
	bison -d -o $@ $<

syn.h: syn.cpp

lex.cpp: lex.l syn.h
	flex -o $@ $<