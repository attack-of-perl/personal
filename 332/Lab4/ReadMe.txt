Name:Zach Perlman  444313
Name:AB Brooks     441827
Lab4
12/7/2017
========================================================================
                                LAB4
========================================================================
Division of Labor:
	Part II: Game Lifecycle Management:
    Using our corrected Lab3 assignment as a foundation for this lab,
    we both split the work evenly to alter our GameBase, TicTacToe
    and Gomoku classes to fit the requirements of Part II. 
  Part III: Saving and Restoring a Game:
		AB worked on the quit prompts and save/restore framework and Zach 
    worked on restoring the TicTacToe & Gomuku games from a well-formatted 
    state of our choosing.
  Part IV: Adding a Sudoku Game:
		AB created the Sudoku game files, designed a save/restore framework for
    Sudoku, and built a board and container of 81 pieces. Zach debugged the 
    Sudoku game, bringing it to a working state and fixing ALL ERRORS!
    
Formatting Saved TicTacToe Games: Our Approach
	Our approach for saving a TicTacToe game creates a file that follows this format:
  
  -----------
  tictactoe
  O
  1 1
  2 1
  3 2
  3 1
  1 2
  2 2
  2 3
  -----------
  
  A saved game file (tictactoe.txt) will display the saved-game identifier
  at the top of the file (tictactoe). The next line displays the player
  whose turn is next (O). The following lines represent coordinate pairs
  for each move made in the saved game.
  
  A game with no remaining moves (i.e. a player wins or the board is filled)
  will create the following file (tictactoe.txt):
  
  -----------
  NODATA
  -----------

Formatting Saved Gomoku Games: Our Approach
  Our approach for saving a Gomoku game creates a file that follows this format:
  
  -----------
  gomoku
  W 
  1 1
  4 2
  5 3
  2 4
  3 2
  -----------
  
  A saved game file (gomoku.txt) will display the saved-game identifier
  at the top of the file (gomoku). The next line displays the player
  whose turn is next (W). The following lines represent coordinate pairs
  for each move made in the saved game.
  
  A game with no remaining moves (i.e. a player wins or the board is filled)
  will create the following file (tictactoe.txt):
  
  -----------
  NODATA
  -----------
  
Formatting Saved Sudoku Games: Our Approach
	Our approach for saving a Sudoku game creates a file that follows this 
  format:
  
  -----------------
  sudoku
  0 0 0 0 8 0 0 7 9
  0 0 0 4 1 9 0 0 5
  0 6 0 0 0 0 2 8 0
  7 0 0 0 2 0 0 0 6
  4 0 0 8 0 3 0 0 1
  8 0 0 0 6 0 0 0 3
  0 9 8 0 0 0 0 6 0 
  6 0 0 1 9 5 0 0 0 
  5 3 0 0 7 0 0 0 0
  -----------------
  
  A saved game file (sudoku.txt) will display the saved-game identifier
  at the top of the file (sudoku). The following lines represent the sudoku
  game board in reverse-row order, where 0s are unfilled values.
  
  This particular saved game is created once a player quits & saves after 
  starting a game with the following file (sudoku0, as provided on the 
  assignment page):
  
  -----------------------
    0   0 0 0 8 0 0 7 9
  0 0 0    4 1 9 0 0 5
  0 6 0 0 0 0 2 8 0
  7 0 0 0  2 0 0 0 6
  4 0 0 8 0 3   0 0 1
  8 0 0 0   6 0 0 0 3
  0 9 8 0 0 0 0 6 0 
  6 0 0 1 9    5 0 0 0 
  5 3 0 0 7 0 0   0   0
  ------------------------
  
  As you can see, our approach standardizes the white-space separation to one
  space between each character, and a new line between each row.
  
Documenting Copy Control Design Decisions:
  We chose not to use a copy constructor, move constructor, copy-assignment operator, 
  move-assignment operator, or destructor in any of our classes since they were not needed 
  for the functionality we desired, and the destructor was implicit in the shared_ptr.

cases:

We tested several cases with all 3 games, including:
	+poorly formatted inputs
  +quitting the game at random times
  +saving a game, then quitting and loading
  +loading a saved game, then saving again and loading again
  +playing a game all the way through
  
With Sudoku in particular, we also tested:
	+Winning the game in various ways, using...
  +our own creadted sudoku0 files with easy solutions
  +poorly formatted sudoku0 files
  
Everything worked well in all of our test cases.





