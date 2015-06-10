LIBS=-lssl -lcrypto

all: clean multipass

clean:
	rm -rf multipass

multipass:
	gcc multipass.c $(LIBS) -o multipass

tests:
	$(MAKE) -C tests
