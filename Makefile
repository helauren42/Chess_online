NAME = chess

SRCS = $(wildcard ./SRCS/*.cpp)

CFLAGS = -Wall -Werror -Wextra -Wno-unused
LDFLAGS = -lSDL2 -lSDL2_image

OBJS = $(SRCS:./SRCS/%.cpp=./obj/%.o)

CC = c++

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	$(MAKE) clean

./obj/%.o: ./SRCS/%.cpp
	mkdir -p ./obj 
	$(CC) $(CFLAGS) -g3 -c $< -o $@

clean:
	rm -rf ./obj

fclean: clean
	rm -f $(NAME)

re: fclean all
