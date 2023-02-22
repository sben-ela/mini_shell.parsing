CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
READ = -L/goinfre/sben-ela/homebrew/opt/readline/lib
INCLUDE = -I/goinfre/sben-ela/homebrew/opt/readline/include
PROG = mini_shell
LIBFT = Libft/libft.a
SOURCES = mini_shell.c ft_split_v2.c utils.c parse_redirect.c  ft_error.c \
		handle_couts.c expanding.c parse.c  $(LIBFT)

OBJECTS = $(SOURCES:.c=.o)

all : $(PROG)
$(PROG) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJECTS) -lreadline $(READ)

%.o : %.c
	$(CC) $(CFLAGS) -c  $(INCLUDE) $<
$(LIBFT) :
	make -C ./Libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean
fclean: clean
	rm -f $(NAME) $(PROG) $(LIBFT)
	make -C libft fclean
bonus: all
	ar rc $(NAME)

re: fclean all
