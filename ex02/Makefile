NAME = PmergeMe
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g
FILES = main.cpp PmergeMe.cpp
HFILES = PmergeMe.hpp

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

debug : $(FILES)
	$(CC) -Wextra -Wall -g -DDEBUG $(FILES) -o debug

.PHONY: all re fclean clean debug
