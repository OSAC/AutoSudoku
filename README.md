AutoSudoku
==========

simple command line app to solve sudoku problem. 


 OPTIONS
       ksudo --input .......user input option
       ksudo input_file ....solve sudoku of given file
       NOTE:  if 2nd argument for output file is given it stores the result in
       that file in each of above two options.

       [no_arguments]
              when ksudo is run without an argument it stops reporting that no
              input file is provided.

       [input_file]
              field  to specify the input file where problem is written.  NOTE
              that the probelm is 9*9 seperated each character or  value  with
              TAB  in  each  new  line and most importantly the empty field in
              sudoku is marked with 0 (zero) value.

       [output_file]
              field to specify the output of the solution.NOTE that the output
              is  written  in  the file only after you solve the problem.If no
              output file is provided then the result is not saved.

   Control Options
       shift+h.........display this help menu.
       ctrl+a..........auto complete, program itsesf solves the problem.
       <space> ........for user input, provides user to input at desired loca‐
       tion.
       ctrl+f..........for  force input (at your own risk),provides user force
       at some extreme position.
       ctrl+y..........undo (only one time undo after each new step).
       ctrl+h..........show/hide possible values(default hidden) at respective
       positions of the fields.

see man page for more information.
