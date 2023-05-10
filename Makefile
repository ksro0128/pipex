CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c pipex.c pipex_utils.c pipex_utils2.c utils.c ft_split.c
SRCS_BONUS = main_bonus.c pipex.c pipex_utils.c pipex_utils2.c utils.c \
ft_split.c multiple_pipex_bonus.c multiple_pipex_utils_bonus.c \
here_doc_bonus.c here_doc_utils_bonus.c gnl.c gnl_utils.c ft_strcmp.c
NAME = pipex
OBJSALL = main.o main_bonus.o pipex.o pipex_utils.o pipex_utils2.o utils.o \
ft_split.o multiple_pipex_bonus.o multiple_pipex_utils_bonus.o \
here_doc_bonus.o here_doc_utils_bonus.o gnl.o gnl_utils.o ft_strcmp.o

ifdef BONUS_FLAG
OBJS = $(SRCS_BONUS:.c=.o)
else
OBJS = $(SRCS:.c=.o)
endif

all : $(NAME)

bonus :
	make BONUS_FLAG=1

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $^ -c
	
clean :
	rm -rf $(OBJSALL)

fclean : clean
	rm -rf $(NAME)

re :
	make fclean
	make all
	
.PHONY : re clean fclean all bonus