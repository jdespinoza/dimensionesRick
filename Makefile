COMPILER = gcc
FILESYSTEM_FILES = fileSystem.c

build: $(FILESYSTEM_FILES)
	$(COMPILER) $(FILESYSTEM_FILES) -o fileSystem `pkg-config fuse --cflags --libs`
	echo 'To Mount: ./fileSystem -f [mount point]'
	mkdir prueba
	mkdir pruebaroot

clean:
	rm fileSystem
