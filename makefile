all:
	gcc algorithms.c getDataFromFile.c main.c memoryListFunctions.c myheader.h -o prueba
	g++ -o tron tron.cpp -lSDLmain -lSDL -lGL -lSDL_image
