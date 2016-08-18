a.out: BufferedFile.o StreamSource.o main.o
	g++ -g  BufferedFile.o StreamSource.o main.o  -o  a.out

BufferedFile.o: BufferedFile.cpp BufferedFile.h
	g++ -g  -c  BufferedFile.cpp

StreamSource.o: StreamSource.cpp StreamSource.h
	g++ -g  -c  StreamSource.cpp

main.o: main.cpp  StreamSource.h
	g++ -g  -c  main.cpp

clean:
	rm -f *.o a.out