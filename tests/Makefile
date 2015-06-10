LIBS=-lssl -lcrypto

all: clean test_digest

clean:
	rm -rf test_digest

test_digest:
	gcc test_digest.c $(LIBS) -o test_digest
