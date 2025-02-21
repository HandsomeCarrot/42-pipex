#created executable file
NAME = libft.a

#compiler
CC = cc
#compiler flags
CFLAGS = -Wall -Wextra -Werror -g

#archiver with it's flags and filename.
ARNAME = ar rcs $(NAME)

#delete with flags
RM = rm -f

#all mandatory files
SRCS =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c

#turns source files into object files
OBJS := $(SRCS:%.c=%.o)

#finds all BONUS files in sourcefolder endning on _bonus.c
BONUS_SRCS =	ft_lstnew_bonus.c \
				ft_lstadd_back_bonus.c \
			 	ft_lstadd_front_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstmap_bonus.c \
			 	ft_lstnew_bonus.c \
				ft_lstsize_bonus.c

#turns BONUS source files into object files
BONUS_OBJS := $(BONUS_SRCS:%.c=%.o)

#name of the created file for check if any function needs recompilation.
BONUS = libft_bonus

PRINTF_SRCS =	ft_printf.c \
				ft_printf_args.c \
				ft_printf_char.c \
				ft_printf_int.c \
				ft_printf_str.c \
				ft_printf_uint.c \
				ft_printf_ptr.c \
				ft_printf_hex.c \
				ft_printf_percent.c

PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)

ALL_OBJS = $(OBJS) $(BONUS_OBJS) $(PRINTF_OBJS)

#runs $(NAME)
all: $(NAME)

#creates the library for the mandatory part
$(NAME): $(OBJS)
	$(ARNAME) $^

#compiles only bonus files and creates a seperate file named libft_bonus.
#That file is only there to check if Library needs to be redone (to not re-link)
$(BONUS) : $(BONUS_OBJS)
	$(ARNAME) $^
	touch $(BONUS)

bonus: $(BONUS)

allbonus: $(ALL_OBJS)
	$(ARNAME) $^

#deletes all object files
clean:
	$(RM) $(ALL_OBJS)

#runs clean and deletes library
fclean: clean
	$(RM) $(NAME) $(BONUS)

#runs fclean and $(NAME)
re: fclean $(NAME)

.PHONY: all, bonus, clean, fclean, re
