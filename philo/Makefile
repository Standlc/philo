NAME	=	philo

SOURCES	=	main.c					\

OBJECTS	= 	$(SOURCES:.c=.o)

RM		=	rm -f

CC		=	cc

CFLAGS	=	-Wall -Wextra #-Werror

all : $(NAME)

$(NAME) : $(OBJECTS)
		$(CC) $(OBJECTS) -pthread -o $(NAME)

%.o : %.c philo.h Makefile
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		@$(RM) $(OBJECTS)

fclean:	clean
		@$(RM) $(NAME)

re : fclean all

.PHONY : all re fclean clean