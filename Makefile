CC = g++ -std=c++11 -w -Wno-deprecated 

tag = -i

src = ./source
bin = ./bin

ifdef linux
tag = -n
endif

ssp: ssp.o
	$(CC) -o $(bin)/ssp $(bin)/ssp.o -lfl -lpthread

routing: routing.o binaryTrie.o
	$(CC) -o $(bin)/routing $(bin)/routing.o $(bin)/binaryTrie.o -lfl -lpthread

test: test.o
	$(CC) -o $(bin)/test $(bin)/test.o -lfl -lpthread

test.o: $(src)/test.cc
	$(CC) -o $(bin)/test.o -g -c $(src)/test.cc

routing.o: $(src)/routing.cc
	$(CC) -o $(bin)/routing.o -g -c $(src)/routing.cc

ssp.o: $(src)/ssp.cc
	$(CC) -o $(bin)/ssp.o -g -c $(src)/ssp.cc

binaryTrie.o: $(src)/binaryTrie.cc
	$(CC) -o $(bin)/binaryTrie.o -g -c $(src)/binaryTrie.cc

clean:
	rm -f $(bin)/*.exe 
	rm -f $(bin)/*.o
	rm -f $(bin)/*.out
