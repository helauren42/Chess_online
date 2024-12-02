NAME = chess

SRCS = $(wildcard ./SRCS/*.cpp)

FLAGS = -Wall -Werror -Wextra -Wno-unused
LDFLAGS = -lSDL2

OBJS = $(SRCS:.cpp=.o)

CC = c++

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
