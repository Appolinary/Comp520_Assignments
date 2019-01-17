
mini : lex.yy.c y.tab.c y.tab.h Main.c 
	gcc lex.yy.c y.tab.c y.tab.h Main.c -o $@ -lfl

lex.yy.c: MiniLang.l
	flex MiniLang.l

y.tab.c: MiniLang.y
	bison --yacc MiniLang.y

y.tab.h: MiniLang.y
	bison -dy MiniLang.y


.PHONY: clean

clean:
	rm lex.yy.c y.tab.c y.tab.h mini

run:
	cat Program.txt | ./mini
