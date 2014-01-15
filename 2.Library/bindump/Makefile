###############################################################
# c-callstack implementation by Kangmo Kim at Nanolat Software.
###############################################################

FILE=main.c
OUT=bindump

CFLAG=-g -O0 -rdynamic

all: ${FILE} 
	gcc ${CFLAG} ${FILE} -o ${OUT} 

clean:
	rm -f ${OUT} 
