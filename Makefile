NAME = libpoormansfixed.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes
AR = ar
ARFLAGS = rcs

SRC_DIR = srcs
OBJ_DIR = obj
INCLUDE_DIR = includes

# List your source files explicitly here
SRCS = $(SRC_DIR)/conversions.c \
       $(SRC_DIR)/operations_32.c \
       $(SRC_DIR)/operations_64.c

OBJS = $(SRC_DIR:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Convert source files to object files
OBJS = $(OBJ_DIR)/conversions.o \
       $(OBJ_DIR)/operations_32.o \
       $(OBJ_DIR)/operations_64.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

install: $(NAME)
	@mkdir -p /usr/local/lib
	@mkdir -p /usr/local/include
	cp $(NAME) /usr/local/lib/
	cp $(INCLUDE_DIR)/*.h /usr/local/include/

.PHONY: all clean fclean re install
