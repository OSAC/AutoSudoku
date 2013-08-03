ksudo: ./usr/src/ksudo/ksudo.cpp
	g++ -o ./usr/bin/ksudo ./usr/src/ksudo/ksudo.cpp
	cp ./usr/bin/ksudo .
clean:
	rm ./usr/bin/ksudo
