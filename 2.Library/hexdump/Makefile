###############################################################
# c-callstack implementation by Kangmo Kim at Nanolat Software.
###############################################################

FILE=main.c
OUT=hexdump

all: ${FILE} 
	gcc -g -O0 -rdynamic ${FILE} -o ${OUT} 

clean:
	rm -f ${OUT} 
