################################################################################
# LIBFTPRINTF.A                                                                #
################################################################################

CC := cc

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

NAME := libftprintf.a
SRCS := string_length.c writer.c ft_printf.c parser.c parser_token.c \
		parser_padding.c parser_write_string.c writer_write_format.c \
		parser_parse_format_string.c parser_write_nbr.c parser_hash_flag.c
OBJS := $(SRCS:.c=.o)
HEADERS := ft_printf.h parser.h $(LIBFT_DIR)/libft.h writer.h parser_private.h \
		   string_length.h
LIBRARY_INCLUDES := $(LIBFT_DIR)
override CFLAGS += -Wall -Wextra -Werror
ifeq ($(DEBUG), TRUE)
	override CFLAGS += -g3 -fno-omit-frame-pointer
endif
override CPPFLAGS += $(addprefix -I, $(LIBRARY_INCLUDES))

################################################################################
# Rules                                                                        #
################################################################################

all: $(LIBFT) $(NAME)

bonus: all

$(NAME): $(OBJS)
	@ar -rcsv $@ $?

%.o: %.c $(HEADERS)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
