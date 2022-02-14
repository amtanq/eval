CPP = g++
OUT = eval
INC = include
SRC = src/parse.cpp src/main.cpp

all: build

build:
	$(CPP) -I $(INC) -o $(OUT) $(SRC)

clean:
	rm -rf $(OUT)
