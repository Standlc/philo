NAME		=	philo

SOURCES		=	main.c					utils/utils.c \
			check_for_deads.c		philosopher_states.c \
			utils/threads_utils.c	init.c \


OBJECTS		= 	$(SOURCES:.c=.o)

DEPENDECIES	=	philo.h Makefile

RM			=	rm -f

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror 

all : $(NAME)

$(NAME) : $(OBJECTS)
		$(CC) $(OBJECTS) -pthread -o $(NAME)

%.o : %.c $(DEPENDECIES)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) $(OBJECTS)

fclean:	clean
		@$(RM) $(NAME)

re : fclean all

.PHONY : all re fclean clean