TARGET = main
INCLDIR = ./include
SRCDIR = src
BINDIR = bin
LIBS = 
CC = gcc
CFLAGS = -O0 -g -lncurses
CFLAGS += -I$(INCLDIR)
RM = rm -f

OBJDIR = obj

$(OBJDIR):
	mkdir -p $(OBJDIR)

# PATHS
_DEPS = main.h Arraylist.h introScreen.h SNLogger.h game.h
DEPS = $(patsubst %, $(INCLDIR)/%, $(_DEPS))

_OBJS = main.o Arraylist.o introScreen.o SNLogger.o game.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

# RULES
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS) | $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

valgrind:
	make
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

run:
	make
	./$(TARGET)
	
.PHONY: clean
clean:
	$(RM) $(OBJDIR)/*.o *~core $(INCLDIR)/*~