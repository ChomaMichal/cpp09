NAME = PmergeMe
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g
FILES = main.cpp PmergeMe.cpp
HFILES = PmergeMe.hpp
		

OBJ = $(FILES:.cpp=.o)

all : $(OBJ) $(NAME)
	

$(NAME): $(OBJ) $(HFILES)
	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)


%.o : %.cpp
	$(CC) $(CFLAGS) -c -O  $< -o $@
	
clean :
	rm -f $(OBJ) $(BOBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

debug :$(HFILES) 
	$(CC) -Wextra -Wall -g -DDEBUG $(FILES) -o debug

debugr: debug
	./debug
.PHONY: all re fclean clean debug
