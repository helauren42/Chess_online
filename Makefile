NAME = chess

SRCS = *.cpp

FLAGS = -lSDL2 -Wall -Werror -Wextra -Wno-unused

OBJS = $(SRCS:.cpp=.o)

CC = c++

all: $(NAME)

$(NAME): $(OBJS)
	c++ $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	c++ $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all