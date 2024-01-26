
NAME := libft.a
CC = gcc

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC_FLAGS := -Wall -Werror -Wextra
OBJDIR := build/

SRCS := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c \
		get_next_line_utils.c

OBJS := $(SRCS:.c=.o)
OBJECTS_PREFIXED := $(addprefix $(OBJDIR), $(OBJS))

SRCSB := ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
			ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJSB := $(SRCSB:.c=.o)
OBJECTS_BONUS_PREFIXED := $(addprefix $(OBJDIR), $(OBJSB))

$(OBJDIR)%.o : %.c libft.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS_PREFIXED)
	@ar rc $(NAME) $(OBJECTS_PREFIXED)
	@echo "Libft Done !"

.PHONY : all clean fclean bonus re so

all: $(NAME) bonus

clean:
	@rm -rf $(OBJDIR)
	@echo "$(NAME): $(RED)object files and directory were deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)Libary was deleted$(RESET)"

re: fclean all

bonus: $(OBJECTS_BONUS_PREFIXED)
	@ar rc $(NAME) $(OBJECTS_BONUS_PREFIXED)
	@echo "Libft Bonus Done !"

so: $(OBJECTS_BONUS_PREFIXED) $(OBJECTS_PREFIXED)
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCSB) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJECTS_BONUS_PREFIXED) $(OBJECTS_PREFIXED)
