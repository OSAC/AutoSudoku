ksudo: ./usr/src/ksudo/ksudo.cpp
	g++ -o ./usr/bin/ksudo ./usr/src/ksudo/ksudo.cpp
clean:
	rm ./usr/bin/ksudo
