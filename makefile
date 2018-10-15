all:
	@cls
	@del *.exe
	@del *.raw
	@g++ src/*cpp -O3 -Wall -Wextra -Wpedantic -std=c++17