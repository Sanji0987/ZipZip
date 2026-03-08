CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
OBJDIR = obj

ifdef DEBUG
CFLAGS += -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
TARGET = main_debug
else
TARGET = main
endif

SRC = main.c hashtable.c
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c hashtable.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) main main_debug

.PHONY: all clean
