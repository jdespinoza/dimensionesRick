all:
	gcc algorithms.c getDataFromFile.c main.c memoryListFunctions.c myheader.h -o MMU
	g++ -o tron tron.cpp algorithms.c getDataFromFile.c memoryListFunctions.c myheader.h -lSDLmain -lSDL -lGL -lSDL_image
	g++ -o brickBreacker brickBreacker.cpp -lSDLmain -lSDL -lGL -lSDL_image
