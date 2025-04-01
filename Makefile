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

BONUS_SRCS := string_length_bonus.c writer_bonus.c ft_printf_bonus.c \
			  parser_bonus.c parser_token_bonus.c parser_padding_bonus.c \
			  parser_write_string_bonus.c writer_write_format_bonus.c \
			  parser_parse_format_string_bonus.c parser_write_nbr_bonus.c \
			  parser_hash_flag_bonus.c
BONUS_OBJS := $(BONUS_SRCS:.c=.o)
BONUS_HEADERS := ft_printf_bonus.h parser_bonus.h $(LIBFT_DIR)/libft.h \
				 writer_bonus.h parser_private_bonus.h string_length_bonus.h

LIBRARY_INCLUDES := $(LIBFT_DIR)
override CFLAGS += -Wall -Wextra -Werror -fPIE
ifeq ($(DEBUG), TRUE)
	override CFLAGS += -g3 -fno-omit-frame-pointer
endif
override CPPFLAGS += $(addprefix -I, $(LIBRARY_INCLUDES))

################################################################################
# Rules                                                                        #
################################################################################

all: $(NAME)

bonus: $(LIBFT) $(BONUS_OBJS)
	touch $@
	cp $(LIBFT) $(NAME)
	ar -rcsv $(NAME) $(filter $?, $(BONUS_OBJS))

$(NAME): $(LIBFT) $(OBJS)
	rm -rf bonus
	cp $(LIBFT) $@
	@ar -rcsv $@ $(filter $?, $(OBJS))

bonus_lib: $(BONUS_OBJS)

$(OBJS): %.o: %.c $(HEADERS)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(BONUS_OBJS): %.o: %.c $(BONUS_HEADERS)
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) bonus
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus_lib
