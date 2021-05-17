all:help

help:
	@echo "Usage for Blockchain examples:"
	@echo "----To build python version---- "
	@echo "use 'make python' to build"
	@echo "****Dependency****"
	@echo "make sure you have flask library installed"
	@echo "------------------------------- "
	@echo "----To build cpp version   ----"
	@echo "use 'make cpp' to build"
	@echo "****Dependency****"
	@echo "Make sure you have openssl-devel library installed"
	@echo "------------------------------- "

python:
	python3 basic_bitcoin.py

cpp:basic_bitcoin.o
	./basic_bitcoin.o

basic_bitcoin.o:basic_bitcoin.cpp
	g++ -o basic_bitcoin.o basic_bitcoin.cpp -lssl -lcrypto

clean:
	rm -f basic_bitcoin.o*
