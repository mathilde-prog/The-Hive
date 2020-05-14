CC=gcc

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

FONCTIONS= interface.c interface_combat.c scan.c
LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image 
INCLUDES=-I${SDLINC_DIR}

PROG=interface

all: interface

interface: interface.c
	${CC} -o ${PROG} ${FONCTIONS} ${LIBS} ${INCLUDES}

clean:
	rm -f ${PROG}
	rm -f *.o
