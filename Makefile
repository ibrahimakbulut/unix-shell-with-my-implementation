

all : bunedu cat pwd lsf wc shell

bunedu : bunedu.o
	gcc -o bunedu bunedu.o

cat : cat.o
	gcc -o cat cat.o

pwd : pwd.o
	gcc -o pwd pwd.o

lsf : lsf.o
	gcc -o lsf lsf.o

wc : wc.o
	gcc -o wc wc.o

shell : gtushell.o
	gcc -o shell gtushell.o

bunedu.o : bunedu.c
	gcc -c bunedu.c

cat.o : cat.c
	gcc -c cat.c

pwd.o : pwd.c
	gcc -c pwd.c

lsf.o : lsf.c
	gcc -c lsf.c

wc.o : wc.c
	gcc -c wc.c

gtushell.o : gtushell.c
	gcc -c gtushell.c
clean:
	rm *.o bunedu shell lsf wc cat pwd 

