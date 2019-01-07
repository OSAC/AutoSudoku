#AutoSudoku
```bash
simple command line app to solve sudoku problem. 
```
==========
##Configuration and Installation<br/>
```bash
$ make 		      	     # to make the executable file ksudo
$ make deb		         # to create a debian installation package
$ sudo make install	   # to make debian installation package and install
$ make	clean	    	   # to remove all make
$ sudo make remove	   # to remove installed (ksudoku) package
```
##Usage Help
```bash
./ksudo --input            # input puzzle from stdin
./ksudo --auto             # auto generated puzzle with default level
./ksudo --auto lev	       # auto generated puzzle with level "lev"
./ksudo infile outfile     # puzzle from 'infile' and solved output on 'outfile'
./ksudo -h                 # display usage information
```
###Screenshoot

![alt tag](https://raw.github.com/OSAC/AutoSudoku/master/ScreenShoot.png)
