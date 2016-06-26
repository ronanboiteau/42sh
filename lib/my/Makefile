NAME	 = libmy.a

RM	 = rm -f

IDIR	= include/

CC	 = gcc
CFLAGS	+= -I $(IDIR)
CFLAGS	+= -Wall -Wextra
CFLAGS	+= -Wpedantic -Wno-long-long
CFLAGS	+= -Werror

CHAR_IS_DIR	= my_char_is/
CHAR_IS_FILES	= my_char_isalpha.c		\
		  my_char_islower.c		\
		  my_char_isnum.c		\
		  my_char_isprintable.c		\
		  my_char_isupper.c
CHAR_IS		= $(addprefix $(CHAR_IS_DIR), $(CHAR_IS_FILES))

ENV_DIR		= env/
ENV_FILES	= my_envcpy.c			\
		  my_getenv.c			\
		  my_printenv.c			\
		  my_setenv.c			\
		  my_unsetenv.c
ENV		= $(addprefix $(ENV_DIR), $(ENV_FILES))

PRINTF_DIR	= my_printf/
PRINTF_FILES	= compare_char.c	\
		  find_flag.c		\
		  flag_char.c		\
		  flag_int.c		\
		  flag_ptr.c		\
		  flag_str.c		\
		  flag_uint.c		\
		  init.c		\
		  my_printf.c		\
		  my_putchar.c		\
		  my_putnbr_base.c	\
		  my_put_nbr.c		\
		  my_putstr.c		\
		  my_showstr.c
PRINTF		= $(addprefix $(PRINTF_DIR), $(PRINTF_FILES))

STR_IS_DIR	= my_str_is/
STR_IS_FILES	= my_str_isalpha.c		\
		  my_str_islower.c		\
		  my_str_isnum.c		\
		  my_str_isprintable.c		\
		  my_str_isupper.c
STR_IS		= $(addprefix $(STR_IS_DIR), $(STR_IS_FILES))

SRCS_DIR	= src/
SRCS_FILES	= get_next_line.c			\
		  match.c				\
		  my_atoi.c				\
		  my_cmp.c				\
		  my_epur_str.c				\
		  my_find_prime_sup.c			\
		  my_free_2d_tab.c			\
		  my_is_prime.c				\
		  my_max_int_tab.c			\
		  my_min_int_tab.c			\
		  my_power.c				\
		  my_realloc.c				\
		  my_revstr.c				\
		  my_sort_int_tab.c			\
		  my_square_root.c			\
		  my_strcapitalize.c			\
		  my_strcmp.c				\
		  my_strdup.c				\
		  my_strlen.c				\
		  my_strlowcase.c			\
		  my_strncat.c				\
		  my_strncmp.c				\
		  my_strncpy.c				\
		  my_strstr.c				\
		  my_str_to_wordtab.c			\
		  my_strupcase.c			\
		  my_swap.c				\
		  nmatch.c				\
		  $(CHAR_IS)				\
		  $(ENV)				\
		  $(PRINTF)				\
		  $(STR_IS)
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS	 = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
