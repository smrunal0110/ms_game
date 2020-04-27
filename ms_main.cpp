#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// MineSweeper Class Definition
#include "ms.h"

int main(int argc, char *argv[]) {
	srand( time( 0 ) );

	MineSweeper mswp;
	bool win = false;
	bool lose = false;

	//validate input
	if (!mswp.validate_input(argc, argv))
	       exit(2);	

	mswp.set_row(stoi(argv[1]));
	mswp.set_column(stoi(argv[2]));
	mswp.set_num_mines(stoi(argv[3]));
	mswp.print_para();

	vector< vector<int> > board(mswp.get_row(), vector<int>(mswp.get_column(), 0));
	vector< vector<int> > player_board(mswp.get_row(), vector<int>(mswp.get_column(), 0));

	mswp.fill_master_board(board);
	mswp.the_board(board);
	cout << endl;

	while (!win && !lose) {
		mswp.generate_player_board(board, player_board);
		mswp.get_player_input();
		lose = mswp.player_lose(board, player_board);
		if (lose)
			break;

		win = mswp.player_win(board, player_board);
	} //while

	if (win){
		cout << "\n\nCONGRATS!! YOU WON THE GAME" <<endl;
		cout << "===========================" << endl<<endl;
		mswp.generate_player_board(board, player_board);
	} //if
	else {
		cout << "\n\nSORRY!! YOU LOST THE GAME" <<endl;
		cout << "=========================" << endl << endl;
		mswp.generate_player_board(board, player_board);
	} //else
		


	return 0;
	//
} //main


