CC = g++
CFLAGS = -O3 -Wall -Wextra -Wpedantic -std=c++17
SRC_DIR = ./src
INC_DIR = ./src/includes/

%.o: $(SRC_DIR)/%.cpp
	$(CC) -I$(INC_DIR) $(CFLAGS) -c $< -o $@

all: aabb.o camera.o light.o main.o matrix.o obj_parser.o octree.o ray.o scene.o triangle.o vector.o
	$(CC) *.o $(CFLAGS)

clean:
	del *.exe
	del *.raw
	del *.o