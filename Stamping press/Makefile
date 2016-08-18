stamp: test.o stampstream.o stampbuf.o stamp.o
	g++ -g test.o stampstream.o stampbuf.o stamp.o -o stamp

test.o: test.cpp stampbuf.h stampstream.h
	g++ -g -c test.cpp

stampstream.o: stampstream.cpp stampstream.h
	g++ -g -c stampstream.cpp

stampbuf.o: stampbuf.cpp stampbuf.h
	g++ -g -c stampbuf.cpp

stamp.o: stamp.cpp stamp.h
	g++ -g -c stamp.cpp

clean:
	rm -f *.o stamp
