CFLAGS = -Wall -g

tests: data.o parser_generic.o parser_test.o parser_uiribbon.o tests.o uiribbon_creator.o uiribbon_transformer.o

%.o: parser_generic.h parser_test.h parser_uiribbon.h uiribbon_transformer.h

clean:
	rm -rf *.o tests

.PHONY: clean
