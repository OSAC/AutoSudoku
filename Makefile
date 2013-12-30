ksudo: 
	g++ -o ./usr/bin/ksudo ./usr/src/ksudo/ksudo.cpp
<<<<<<< HEAD
	ln -s ./usr/bin/ksudo ./ksudo
=======
	cp ./usr/bin/ksudo .
>>>>>>> 5cb29f5b813ad3794e7df52461d67bb44ad39666
clean:
	rm ./usr/bin/ksudo
	rm ./ksudo
	rm -f ksudoku_1.2_i386.deb
deb:
	make 
	mkdir ./ksudoku_1.2_i386
	cp -r ./DEBIAN ./ksudoku_1.2_i386/
	cp -r ./usr ./ksudoku_1.2_i386/
	dpkg -b ./ksudoku_1.2_i386/
	rm -rf ./ksudoku_1.2_i386/
install:
	make deb
	sudo dpkg -i ./ksudoku_1.2_i386.deb
remove:
	sudo dpkg --purge ksudoku
