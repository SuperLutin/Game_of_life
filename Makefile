ifdef WINDOWS
CC = i586-mingw32msvc-gcc
else
CC = gcc -std=c11
#CC = clang
endif
CFLAGS = -O3 -Isrc -Wall -Wextra -W -pedantic -pipe -ffast-math -fforce-addr -march=native -fomit-frame-pointer -finline-functions -funroll-loops -funsafe-loop-optimizations

CFLAGS += `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lGL -lGLU

SRCDIR=src/
OBJDIR=obj/

SRC_BASE = $(wildcard $(SRCDIR)*/*.c $(SRCDIR)*.c)
OBJ_BASE = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRC_BASE))

ifdef DEBUG
        CFLAGS += -g
endif

EXEC=jdlv

all: $(EXEC)

$(EXEC) : $(OBJ_BASE)
	mkdir -p $(@D)
	$(CC) -o $@ $(OBJ_BASE) $(LDFLAGS)

$(OBJDIR)%.o : $(SRCDIR)%.c
	mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -f $(OBJDIR)*.o $(EXEC)

re :
	make clean && make
