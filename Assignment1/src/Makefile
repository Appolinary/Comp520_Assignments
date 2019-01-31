
mini : tree.h tree.c lex.yy.c y.tab.c y.tab.h Main.c pretty.h pretty.c
	gcc tree.h tree.c lex.yy.c y.tab.c y.tab.h Main.c pretty.h pretty.c -o $@ -lfl

lex.yy.c: MiniLang.l
	flex MiniLang.l

y.tab.c: MiniLang.y
	bison --yacc MiniLang.y

y.tab.h: MiniLang.y
	bison -dy MiniLang.y


.PHONY: clean
.PHONY: run

clean:
	rm lex.yy.c y.tab.c y.tab.h mini

run:
	cat perfectsquare.min | ./mini "parse"
