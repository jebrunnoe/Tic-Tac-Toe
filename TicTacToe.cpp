#include <iostream>
#include <vector>
using namespace std;

int wins[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, 
		  {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, 
		  {0, 4, 8}, {2, 4, 6}};  // Eight possible winning combinations.

void display(char board[9]) 
{
   cout << endl;
   cout << board[0] << " | " << board[1] << " | " << board[2] << endl;
   cout << "--+---+--" << endl;
   cout << board[3] << " | " << board[4] << " | " << board[5] << endl;
   cout << "--+---+--" << endl;
   cout << board[6] << " | " << board[7] << " | " << board[8] << endl;
   cout << endl;
}

char get_status(char board[9])
{
   for(int i = 0; i < 8; i++) {
      // Iterate through the eight winning combinations and see if any of them are filled with the same symbol.
      if(board[wins[i][0]] != ' ' && // Make sure the space is not blank: ' '.
	 board[wins[i][0]] == board[wins[i][1]] && 
	 board[wins[i][1]] == board[wins[i][2]]) { 
	 return board[wins[i][0]]; // Return the winning symbol: X or O.
      }
   }
   for(int i = 0; i < 9; i++) {
      // Check for empty spaces.
      if(board[i] == ' ') {
	 return '\0'; // The game is still in progress.
      }
   }
   return ' '; // The game is tied.
}

char opponent(char player) 
{  // Return the symbol of the opponent of the given player.
   if(player == 'X') {
      return 'O';
   }
   else {
      return 'X';
   }
}

int minimax(char board[9], char player, char caller)
{
   char status = get_status(board);
   if(status != '\0') { // Check if current game state is terminal.
      if(status == ' ') {
	 return 0;   // Tie game
      }
      else if(status == caller) {
	 return 100; // Caller of the function won.
      }
      else {
	 return -100; // Opponent won. 
      }
   }
   vector<int> scores; // Best possible scores from caller's perspective
   for(int i = 0; i < 9; i++) {   
      if(board[i] == ' ') {
	 char clone[9];
	 copy(board, board + 9, clone);
	 clone[i] = player;
	 scores.push_back(minimax(clone, opponent(player), caller)); // Recursive call 
      }
   }
   if(player == caller) { 
      // If the current player called the function, they want to maximize the score. Return the maximum possible score.
      return *max_element(scores.begin(), scores.end());
   }
   else { 
      // If the current player is the opponent, they want to minimize the caller's score. Return the minimum possible score.
      return *min_element(scores.begin(), scores.end());
   }
}

void computer(char board[9], char symbol)
{  
   int scores[9]; // List of best possible score associated with each space.
   for(int i = 0; i < 9; i++) {
      if(board[i] != ' ') {
	 scores[i] = -numeric_limits<int>::max(); // Space is taken, off limits. 
      }
      else {
	 char clone[9];
	 copy(board, board + 9, clone);
	 clone[i] = symbol;
	 scores[i] = minimax(clone, opponent(symbol), symbol); // Player up is the opponent, since a move was just made. Caller is the computer (symbol). 
      }
   }
   int index = distance(scores, max_element(scores, scores + 9)); // Index of highest scoring move
   board[index] = symbol;
}

int input(int lower, int upper)
{ 
   int selection;
   while (!(cin >> selection) || selection < lower || selection > upper) {
      cout << "Invalid selection." << endl;
   }
   return selection;
}

void human(char board[9], char symbol)
{
   cout << "Move choice (1 - 9): ";
   int move;
   move = input(1, 9);
   if(board[move - 1] != ' ') {	 // Don't allow taken spaces to be chosen.
      cout << "Invalid selection." << endl;
      human(board, symbol);
   }
   else {
      board[move - 1] = symbol;
   }
}

int main()
{
   char master_board[9];
   for(int i = 0; i < 9; i++) {
      master_board[i] = ' ';
   }
   
   cout << "1) Play as X" << endl;
   cout << "2) Play as O" << endl;
   int selection = input(1, 2);
   char user_symbol;
   if(selection == 1) {
      user_symbol = 'X';
   }
   else {
      user_symbol = 'O';
   }
   char active_player = 'X'; // X goes first by convention.
   while(get_status(master_board) == '\0') {
      display(master_board);
      if(active_player == user_symbol) {
	 human(master_board, user_symbol);
      }
      else {
	 computer(master_board, opponent(user_symbol));
      }
      active_player = opponent(active_player); // Switch back and forth between X and O.
   }
   display(master_board);
   char result = get_status(master_board);
   if(result == user_symbol) {
      cout << "You win." << endl;
   }
   else if(result == opponent(user_symbol)) {
      cout << "You lose." << endl;
   }
   else {
      cout << "Tie game." << endl;
   }
}
