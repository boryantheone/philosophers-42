NAME	= philo

NAME_BONUS	= philo_bonus

HEAD	= philo.h

FUNC	= philo.c philo_utils.c parser.c

BONUS_FUNC	= philo_bonus.c parser.c philo_utils_bonus.c

OBJS	= ${FUNC:.c=.o}

BONUS_OBJS	= ${BONUS_FUNC:.c=.o}

CC	= gcc

CFLAGS	= -Wall -Werror -Wextra

RM	= rm -f

.PHONY: all clean fclean re bonus

all : ${NAME}

${NAME} :	${OBJS} ${HEAD}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

bonus	: ${NAME_BONUS}

${NAME_BONUS}	:	${BONUS_OBJS} ${HEAD}
					${CC} ${CFLAGS} ${BONUS_OBJS} -o ${NAME_BONUS}

clean	:
			${RM} ${OBJS} ${BONUS_OBJS}

fclean	:	clean
			${RM} ${NAME} ${NAME_BONUS}

re	:	fclean clean all bonus