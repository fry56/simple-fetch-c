##
## EPITECH PROJECT, 2022
## make
## File description:
## desc
##

SRC = \
	src/fetch.c \
	src/parse_http_response.c \

OBJ = $(SRC:.c=.o)

GCC = gcc

INCLUDE_FLAGS = \
	-I include \
	-I ../simple-map-c/include \

C_WARNING_FLAGS = -Wextra -Wall -g
C_FLAGS = $(C_WARNING_FLAGS) $(INCLUDE_FLAGS)

.c.o:
	@echo "$(notdir $(CURDIR)): C '$<'"
	@$(GCC) $(C_FLAGS) -c -o $*.o $<

all: simple_fetch.a
.PHONY : all

simple_fetch.a: $(OBJ)
	@ar rc $@ $(OBJ)
.PHONY : simple_fetch.a

clean:
	@find . \( -name "*.o" -or -name "*.a" \) -delete
.PHONY : clean

re: clean all
.PHONY: re