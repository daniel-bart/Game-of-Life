
#include <iostream>
#include<vector>
#include<Windows.h>
#include <fstream>
#include <string>
#include <sstream> 

using namespace std;

vector<vector<int>> dead_state(int y, int x) {
	vector<vector<int>> dead(y, vector<int>(x, 0));
	return dead;
};
vector<vector<int>> random_state(int y, int x) {
	vector<vector<int>> random(y, vector<int>(x, 0));
	int random_number;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			random_number = rand() % 100 +1;
			if (random_number < 51) {
				random[i][j] = 0;
			}
			else {
				random[i][j] = 1;
			}

		}
	}
	return random;
}
void render(vector<vector<int>> &state) {
	for (int i = 0; i < state.size(); i++) {
		for (int j = 0; j < state[0].size(); j++) {
			if (state[i][j] == 1) {
				cout << "#";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}
int sum_alive(vector<vector<int>> &state, int y, int x) {
	int sum;
	if (x == 0 and y == 0) {
		sum = state[y][x + 1] + state[y + 1][x] + state[y + 1][x + 1];
	}
	else if (x == state[0].size() - 1 and y == 0) {
		sum = state[y][x - 1] + state[y + 1][x] + state[y + 1][x - 1];
	}
	else if (x == 0 and y == state.size() - 1) {
		sum = state[y][x + 1] + state[y - 1][x] + state[y - 1][x + 1];
	}
	else if (x == state[0].size() - 1 and y == state.size() - 1) {
		sum = state[y][x - 1] + state[y - 1][x] + state[y - 1][x - 1];
	}
	else if (x == 0 and y != 0 and y != state.size() - 1) {
		sum = state[y - 1][x] + state[y - 1][x + 1] + state[y][x + 1] + state[y + 1][x] + state[y + 1][x + 1];
	}
	else if (y == 0 and x != 0 and x != state[0].size() - 1) {
		sum = state[y][x - 1] + state[y][x + 1] + state[y + 1][x - 1] + state[y + 1][x] + state[y + 1][x + 1];
	}
	else if (x == state[0].size() - 1 and y != 0 and y != state.size() - 1) {
		sum = state[y - 1][x - 1] + state[y - 1][x] + state[y][x - 1] + state[y + 1][x - 1] + state[y + 1][x];
	}
	else if (y == state.size() - 1 and x != 0 and x != state[0].size() - 1) {
		sum = state[y - 1][x - 1] + state[y - 1][x] + state[y - 1][x + 1] + state[y][x - 1] + state[y][x + 1];
	}
	else {
		sum = state[y - 1][x - 1] + state[y - 1][x] + state[y - 1][x + 1] + state[y][x - 1] + state[y][x + 1] + state[y + 1][x - 1] + state[y + 1][x] + state[y + 1][x + 1];
	}
	return sum;
}
vector<vector<int>> next_state(vector<vector<int>> &previous_state) {
	vector<vector<int>> next_state = dead_state(previous_state.size(), previous_state[0].size());
	for (int i = 0; i < previous_state.size(); i++) {
		for (int j = 0; j < previous_state[0].size(); j++) {
			if (sum_alive(previous_state, i, j) < 2 and previous_state[i][j] == 1) {
				next_state[i][j] = 0;
			}
			else if (1 < sum_alive(previous_state, i, j) and sum_alive(previous_state, i, j) < 4 and previous_state[i][j] == 1) {
				next_state[i][j] = 1;
			}
			else if (3 < sum_alive(previous_state, i, j) and previous_state[i][j] == 1) {
				next_state[i][j] = 0;
			}
			else if (sum_alive(previous_state, i, j) == 3 and previous_state[i][j] == 0) {
				next_state[i][j] = 1;
			}
			else {
				next_state[i][j] = previous_state[i][j];
			}
		}
	}
	return next_state;
}
vector<vector<int>> read_state(string file) {
	vector<vector<int>> read_state;
	string line;
	ifstream data(file);
	if (!data.is_open()) {
		cout << "Could not open: " << file << endl;
		exit(EXIT_FAILURE);
	}
	getline(data, line);
	stringstream s;
	s << line;
	int COL = 0;
	double value;
	while (s >> value) {
		COL++;
	}
	data.seekg(0, ios::beg);
	vector<int> row_vec(COL);
	int i = 0;
	while (data.good()) {
			read_state.push_back(row_vec);
			for (int j = 0; j < COL; j++)
			{
				data >> read_state[i][j];
			}
			i++;
		}
	return read_state;
	}
vector<vector<int>> board1;
vector<vector<int>> board2;
int main()
{
	try {
		int width, height, choice;
		string filepath;
		cout << "Do you want to load a file (1) or generate a random pattern (2) ?" << endl;
		cin >> choice;
		if (choice == 1) {
			cout << "Whats the path to the file (with extension)?" << endl;
			getchar(); // for /n char
			getline(cin, filepath);
			board1=read_state(filepath);
		}
		else {
			cout << "Width for random pattern :", cin >> width, cout << endl;
			cout << "Height for random pattern :", cin >> height, cout << endl;
			board1 = random_state(height, width);
		}
		render(board1);
		while (true) {
			system("cls");
			board2 = next_state(board1);
			render(board2);
			board1 = board2;
			Sleep(50); // Increase if stuttering

		}
		/* Test Functions
		board = dead_state(height, width);
		vector<vector<int>> expected_board = dead_state(height, width);
		if (next_state(board) == expected_board) {
			cout << "Dead-State Test Passed!" << endl;
		}
		else {
			cout << "Dead-State Test Failed" << endl;
		}
		board = { {0,0,1 },{0,1,1 },{0,0,0 } };
		expected_board = { {0,1,1} , { 0,1,1 }, { 0,0,0 }};
		if (next_state(board) == expected_board) {
			cout << "3-Neighbours Test Passed!" << endl;
		}
		else {
			cout << "3-Neighbours Test Failed" << endl;
		}
		board = { {0,0,0 },{0,1,0 },{0,0,0 } };
		expected_board = { {0,0,0} , { 0,0,0 }, { 0,0,0 } };
		if (next_state(board) == expected_board) {
			cout << "No-Neighbours Test Passed!" << endl;
		}
		else {
			cout << "No-Neighbours Test Failed" << endl;
		}
		board = {{0,1,0},{1,1,1},{0,1,0}};
		expected_board = {{1,1,1},{1,0,1 },{ 1,1,1 } };
		if (next_state(board) == expected_board) {
			cout << "4-Neighbours Test Passed!" << endl;
		}
		else {
			cout << "4-Neighbours Test Failed" << endl;
		}*/
	}
	catch (const exception& error_)
	{
		cout << "Caught exception: " << error_.what() << endl;
		return 1;
	}
	return 0;
}

