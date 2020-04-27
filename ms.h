#ifndef MS_H
#define MS_H

#include <vector>

#define MAX_ROWS 25
#define MAX_COLUMNS 25
#define MAX_MINES 20

class MineSweeper {
	private:
		//variables
		int row;
		int column;
		int num_mines;
		int mine_row_placement;
		int mine_column_placement;
		int player_selected_row;
		int player_selected_column;
		int selected_flag;

		//methods
		void place_mines_on_board();
		void format_board_header();
		void mine_location_hint(vector <vector <int> > &); 

	public:
		//methods
		MineSweeper();
		bool validate_input(int argc, char *argv[]);
		void set_row(int r);
		void set_column(int c);
		void set_num_mines(int m);
		int get_row();
		int get_column();
		int get_num_mines();
		void print_para();
		void fill_master_board(vector <vector <int> > &); 
		void the_board(vector <vector <int> > &); 
		void generate_player_board(vector <vector <int> > &, vector <vector <int> > &); 
		void get_player_input();
		bool player_lose(vector <vector <int> > &, vector <vector <int> > &); 
		bool player_win(vector <vector <int> > &, vector <vector <int> > &); 
		

		//vector objects
		vector< vector<int> > board;
		vector< vector<int> > player_board;

};
#endif
