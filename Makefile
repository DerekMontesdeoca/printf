CC := cc
NAME := libftprintf.a
CFLAGS := -Wall -Wextra -Werror
ifeq ($(DEBUG), TRUE)
	CFLAGS += -g3
endif
SRCS := ft_printf.c
OBJS := $(SRCS:.c=.o)
HEADERS := ft_printf.h

################################################################################
# Rules                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcsv $@ $?

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
