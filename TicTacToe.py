master_board = [' '] * 9
wins = [[0, 1, 2], [3, 4, 5], [6, 7, 8], 
        [0, 3, 6], [1, 4, 7], [2, 5, 8], 
        [0, 4, 8], [2, 4, 6]] # Eight possible winning combinations.

def display(board):
   print
   print board[0] + ' | ' + board[1] + ' | ' + board[2]
   print '--+---+--'
   print board[3] + ' | ' + board[4] + ' | ' + board[5]
   print '--+---+--'
   print board[6] + ' | ' + board[7] + ' | ' + board[8]
   print

def get_status(board):
   # Iterate through the eight winning combinations and see if any of them are filled with the same symbol.
   for win in wins: 
      if board[win[0]] == board[win[1]] == board[win[2]] and board[win[0]] != ' ': # Make sure the space is not blank: ' '.
	 return board[win[0]] # Return the winning symbol: X or O.
   for value in board:
      if value == ' ': # Check for empty spaces.
	 return None # The game is still in progress.
   return ' ' # The game is tied.
      
def opponent(player):
   #  Return the symbol of the opponent of the given player.
   if player == 'X': return 'O'
   if player == 'O': return 'X'

def minimax(board, player, caller):
   status = get_status(board)
   if status != None: #	Check if current game state is terminal.
      if status == ' ': 
	 return 0 # Tie game.
      elif status == caller: 
	 return 100 # Caller of minimax won. 
      else:
	 return -100 # Opponent won. 
   scores = list() # Best possible scores from caller's perspective
   for i in range(9):
      if board[i] == ' ':
	 copy = list(board)
	 copy[i] = player
	 scores.append(minimax(copy[:], opponent(player), caller)) # Recursive call
   if player == caller:
      #  If the current player called the function, they want to maximize the score. Return the maximum possible score.
      return max(scores)
   else: 
      # If the current player is the opponent, they want to minimize the caller's score. Return the minimum possible score.
      return min(scores)

def computer(board, symbol):
   scores = [-float("inf")] * 9 # List of best possible scores associated with each space. 
   for i in range(9):
      if board[i] == ' ':
	 copy = list(board)
	 copy[i] = symbol
	 scores[i] = minimax(copy[:], opponent(symbol), symbol) # Player up is the opponent, since a move was just made. Caller is the computer (symbol).
   index = scores.index(max(scores)) # Index of highest scoring move.
   board[index] = symbol

def get_input(lower, upper):
   selection = input()
   if selection < lower or selection > upper:
      print "Invalid selection."
      selection = get_input(lower, upper)
   return selection

def human(board, symbol):
   print "Move choice (1 - 9): "
   move = get_input(1, 9)
   if board[move - 1] != ' ':
      print "Invalid selection."
      human(board, symbol)
   else:
      board[move - 1] = symbol

def play():
   print "1) Play as X"
   print "2) Play as O"
   selection = get_input(1, 2)
   if selection == 1:
      user_symbol = 'X'
   else:
      user_symbol = 'O'

   player = 'X' # X goes first by convention
   while get_status(master_board) == None:
      display(master_board)
      if player == user_symbol:
	 human(master_board, user_symbol)
      else:
	 computer(master_board, opponent(user_symbol))
      player = opponent(player) # Switch back and forth between X and O.
   
   display(master_board)
   result = get_status(master_board)
   if result == user_symbol:
      print "You win."
   elif result == opponent(user_symbol):
      print "You lose."
   else:
      print "Tie game."	    

play()
