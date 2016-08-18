pro: main.o Media.o SearchEngine.o Book.o Video.o Periodic.o Film.o
	g++ main.o Media.o SearchEngine.o Book.o Video.o Periodic.o Film.o -o pro

main.o: main.cpp Media.h SearchEngine.h Book.h
	g++ -g -c main.cpp

Media.o: Media.cpp Media.h
	g++ -g -c Media.cpp

SearchEngine.o: SearchEngine.cpp SearchEngine.h
	g++ -g -c SearchEngine.cpp

Book.o: Book.cpp Book.h
	g++ -g -c Book.cpp

Video.o: Video.cpp Video.h
	g++ -g -c Video.cpp

Periodic.o: Periodic.cpp Periodic.h
	g++ -g -c Periodic.cpp

Film.o: Film.cpp Film.h
	g++ -g -c Film.cpp

clean:
	rm -f *.o pro
