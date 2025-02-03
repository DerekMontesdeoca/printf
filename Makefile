CC := cc

LIBFT := libft
LIBFT_DIR := libft

NAME := libftprintf.a
SRCS := ft_printf.c
OBJS := $(SRCS:.c=.o)
HEADERS := ft_printf.h $(LIBFT_DIR)/libft.h
LIBRARY_INCLUDES := ./libft
CFLAGS := -Wall -Wextra -Werror
ifeq ($(DEBUG), TRUE)
	CFLAGS += -g3
endif
CPPFLAGS := $(addprefix -I, $(LIBRARY_INCLUDES))

################################################################################
# Rules                                                                        #
################################################################################

all: $(NAME) $(LIBFT)

$(NAME): $(OBJS) 
	@ar -rcsv $@ $?

%.o: %.c $(HEADERS)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
