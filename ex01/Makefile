NAME = RPN
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g
FILES = main.cpp RPN.cpp

OBJ = $(FILES:.cpp=.o)

all : $(OBJ) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all re fclean clean
