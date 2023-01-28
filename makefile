NAME=so
CPPFLAGS:=-std=c++17 -ggdb
CPP_SOURCE=$(wildcard src/*.cpp)

H_SOURCE=${wildcard src/*.h}

OBJ=$(CPP_SOURCE:.cpp=.o)

CC=g++

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) -o $@ $< $(CPPFLAGS)

main.o: main.cpp $(H_SOURCE)
	$(CC) -o $@ $< $(CPPFLAGS)

clean:
	rm -rf src/*.o $(NAME) *~
