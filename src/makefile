CC=gcc
CFLAGS=-ansi -Wall
EXEC=Lexique

all:$(EXEC)

$(EXEC): main.o lexicalTree.o parsing.o save.o opt.o menu.o gui.o
	$(CC) -o $@ $^ $(CFLAGS)

main.o: main.c opt.h menu.h
	$(CC) -o $@ -c $< $(CFLAGS)

lexicalTree.o: lexicalTree.c 
	$(CC) -o $@ -c $< $(CFLAGS)

parsing.o: parsing.c lexicalTree.h
	$(CC) -o $@ -c $< $(CFLAGS)

save.o: save.c lexicalTree.h
	$(CC) -o $@ -c $< $(CFLAGS)

opt.o: opt.c save.h parsing.h
	$(CC) -o $@ -c $< $(CFLAGS)

menu.o: menu.c save.h parsing.h 
	$(CC) -o $@ -c $< $(CFLAGS)

gui.o: gui.c lexicalTree.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o

clearDic:
	rm -f *.DIC

clearLEX:
	rm -f *.LEX 

mrproper: clean clearLEX clearDic
	rm -f $(EXEC)

