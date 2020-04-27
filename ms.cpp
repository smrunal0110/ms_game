#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// class MineSweeper definition
#include "ms.h"

//Constructor for class MineSweeper
MineSweeper::MineSweeper() {

	row = 0;
	column = 0;
	num_mines = 0;
	mine_row_placement = 0;
	mine_column_placement = 0;
	player_selected_row = 0;
	player_selected_column = 0;
	selected_flag = 0;
} //MineSweeper()

//next several methods are setters and getters
void MineSweeper::set_row(int r)
{
	row = r;
} //set_row()

void MineSweeper::set_column(int c)
{
	column = c;
} //set_column()

void MineSweeper::set_num_mines(int m)
{
	num_mines = m;
} //set_num_mines

int MineSweeper::get_row()
{
	return row;
} //get_row()

int MineSweeper::get_column()
{
	return column;
} //get_column

int MineSweeper::get_num_mines()
{
	return num_mines;
} //get_num_mines

//displays rwo, column and number of mines used to set up board
void MineSweeper::print_para()
{
	cout << "row = " << row << endl;
	cout << "column = " << column << endl;
	cout << "num_mines = " << num_mines << endl <<endl;
} //print_para()

// validates input against MAX values defined in "ms.h" header file
bool MineSweeper::validate_input(int argc, char *argv[])
{
	bool flag = 1;

	int r,c,m,matrix;

	
	if (argc != 4) {
		cout << "Incorrect number of input, need 4 input (ex. ./a.out 3 5 10). exiting.." << endl;
		flag = 0;
	}
	else {
		r = stoi(argv[1]);
		c = stoi(argv[2]);
		m = stoi(argv[3]);
		matrix = r*c;

		if (r > MAX_ROWS || r == 0) {
			cout << " invalid input for row. exiting.." << endl;
			flag = 0;
		} //if for rows

		if (c > MAX_COLUMNS || c == 0) {
			cout << " invalid input for column exiting.." << endl;
			flag = 0;
		 } //if for column

		if ((m > MAX_MINES) || (m > matrix || m == 0)) {
			cout << "invalid input for number of mines, exiting.." << endl;
			flag = 0;
		 } //if for mines
	} //else


	if (flag == 1)
		return true;
	else
		return false;
} //validate_input()

// randomly generates mines on board
void MineSweeper::place_mines_on_board()
{
	mine_row_placement = rand() % row;
	mine_column_placement = rand() % column;

} //place_mines_on_board

// populates the master board
void MineSweeper::fill_master_board(vector <vector <int> > &board)
{
	//populate matrix with mines
	for (int mines = 0; mines < num_mines; mines++) {
		place_mines_on_board();
		if (board[mine_row_placement][mine_column_placement] == 0)
			board[mine_row_placement][mine_column_placement] = -1;
		else
			--mines;
	} //for mines

	mine_location_hint(board);
} // fill_master_board()

// provide hint regarding location of mines
void MineSweeper::mine_location_hint(vector <vector <int> > &board)
{
	for(int a=0;a<row;++a)
        	for(int b=0; b<column;++b){
                	if(board[a][b]== -1)
                	continue;
                	int x = -1;
                	if(a == 0)
                    	x =0;


                	for (;x <=1;++x){
                    		int y=-1;
                    		if(b==0)
                    		y=0;
                    		for(;y<=1;++y)
                        		if(x+a < row && y+b < column)
                            			if(board[a+x][b+y]==-1)
                                			++board[a][b];


            		} // inner for	
        	} //outer for

} //mine_location_hint()


//prints the board header
void MineSweeper::format_board_header() {
	cout <<"   ";
	for (int i = 0; i < column; i++)
		cout <<setw(2) << i << " ";
	cout << endl;

	cout <<"   ";
	for (int i = 0; i < column; i++)
		cout << setw(2) <<"-" << " " ;
	cout <<endl;

} //format_board_header

// marks mine location with "X" on the board
void MineSweeper::the_board( vector< vector<int> > &board) {
	cout << "The Board:" << endl;
	cout << "==========" << endl;
	format_board_header();

	for (int j = 0; j < board.size(); j++) {
		if (j <10)
			cout << j <<"  |";
		else if (j >= 10)
			cout << j <<" |";

		for (int k = 0; k < column; k++){
				if(board[j][k] == -1)
					//cout << "X|   ";
					cout << setw(3) <<"X|";
				else
					//cout << board[j][k] << "|   ";
					cout << setw(2) << board[j][k] << "|";
			} //inner for
		cout << endl;
	} //outer for

} //the_board()

void MineSweeper::generate_player_board( vector< vector<int> > &board, vector< vector<int> > &player_board) {
	cout << "Player Board" << endl;
	cout << "============" << endl;
	format_board_header();

	for (int j = 0; j < board.size(); j++) {
		if (j < 10 )
			cout << j <<"  |";
		else if (j >= 10)
			cout << j <<" |";

		for (int k = 0; k < column; k++){
			if (player_board[j][k] == 1) {
				if(board[j][k] == -1)
					//cout << "X|   ";
					cout << setw(3) <<"X|";
				else
					//cout << board[j][k] << "|   ";
					cout << setw(2) << board[j][k] << "|";
			} //if
			else if(player_board[j][k] == 0)
				//cout << "*|   ";
				cout <<setw(3)<< "*|";
			else if(player_board[j][k] == 2)
				//cout << "F|   ";
				cout <<setw(3) << "F|";
				
		} //inner for
		cout << endl;
	} // outer for
} //generate_player_board()

// takes player input for selection of board cell to either open or set a flag
void MineSweeper::get_player_input(){

	//player row selection
	while( true ) {
		cout << "enter row number which must be greter or equal to 1 and less than " << row << ": ";
		cin >> player_selected_row;
		if (player_selected_row < row)
			break; //valid row

		cout << "invalid row number, enter valid which must be less than "<<row<< ": ";
	} //while
	
	//player column selection
	while( true ) {
		cout << "enter column number which must be greater or equal to 1 and less than " << column << ": ";
		cin >> player_selected_column;
		if (player_selected_column < column)
			break; //valid row

		cout << "invalid column number, enter valid column which must be less than "<<column << ": ";
	} //while

	while(true) {
		cout << "0 to open location, 1 to set flag: ";
		cin >> selected_flag;
		if( selected_flag == 0 || selected_flag == 1)
			break; //valid flag

		cout << "invalid input, select 0 or 1: ";

	} //while
	
} //get_player_input()


//check to see if player lose
bool MineSweeper::player_lose( vector< vector<int> > &board, vector< vector<int> > &player_board) 
{
    if(player_selected_row >= row || player_selected_column >= column)
        return false;

    //in case flag was chosen
    if(selected_flag == 1){
        player_board[player_selected_row][player_selected_column] = 2;
        return false;
    } //if

    bool temp;
        //in case there were no mines near the selected box recursively
    if(board[player_selected_row][player_selected_column]== 0 ){
        player_board[player_selected_row][player_selected_column]=1;

        //open boxes near it
        int a = -1;
        if(player_selected_row == 0)
		a =0;

        for (;a <=1;++a){
            int b= -1;
            if(player_selected_column == 0)
                b=0;
            for(;b<=1;++b){

                if(player_selected_row + a < row && player_selected_column + b < column){
                    if(player_board[player_selected_row + a][player_selected_column + b]==1)
                    continue;
                    temp = player_lose(board,player_board);

                    } //if

                }// for

            } //for


        return false;
        } //if

    // in case of a mine
    if(board[player_selected_row][player_selected_column]== -1){
            player_board[player_selected_row][player_selected_column]=1;
            return true;

    } //if

        //if none of the above cases
        player_board[player_selected_row][player_selected_column]=1;
        return false;


} //player_lose()



// check to see if player win
bool MineSweeper::player_win( vector< vector<int> > &board, vector< vector<int> > &player_board)
{
     for(int i=0;i<row;i++)
        for(int j=0; j<column;j++){
            if (player_board[i][j] == 0)
                return false;
            else if(player_board[i][j] == 2)
                    if(board[i][j] != -1)
                        return false;

        } //inner for

    return true;

}//player_win()	

