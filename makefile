all:
	@del *.exe
	@del *.raw
	@g++ src/*cpp -O3 -Wall -Wextra
	@cls
	@a.exe