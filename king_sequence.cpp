/* Task
Pictured below is a keypad:
A B C D E
F G H I J
K L M N O
  1 2 3

We want to find all 10-key sequences that can be keyed into the keypad in the following manner:
•	The initial keypress can be any of the keys.
•	Each subsequent keypress must be a knight move from the previous keypress.
•	There can be at most 2 vowels in the sequence.

A knight move is made in one of the following ways:
1.	Move two steps horizontally and one step vertically.
2.	Move two steps vertically and one step horizontally.
There is no wrapping allowed on a knight move.

Your program should first write the number of valid 10-key sequences on a single line to standard out.
The following lines of output should contain the valid key sequences.
*/

#include <cstdio>
#include <memory.h>
using namespace std;

#define MAX_LENGTH		10
#define MAX_X			4
#define MAX_Y			5
#define MAX_VOWELS		2
#define MAX_MOVES		8

//possible knight moves(8 moves)
int dx[MAX_MOVES] = {  1,  1,  2,  2, -1, -1, -2, -2};
int dy[MAX_MOVES] = {  2, -2,  1, -1,  2, -2,  1, -1};

long long dp[MAX_LENGTH + 1][MAX_X][MAX_Y][MAX_VOWELS + 1];
//table of vowels on map
bool is_vowel[MAX_X][MAX_Y] = {{1, 0, 0, 0, 1},
							   {0, 0, 0, 1, 0},
							   {0, 0, 0, 0, 1},
							   {0, 0, 0, 0, 0}};

char matrix[MAX_X][MAX_Y] = {{'A', 'B', 'C', 'D', 'E'},
							 {'F', 'G', 'H', 'I', 'J'},
							 {'K', 'L', 'M', 'N', 'O'},
							 {'?', '1', '2', '3', '?'}};

char s[MAX_LENGTH+1];
int current_vowels = 0;
int current_length = 0;

bool correct_position(int x, int y)
{
	return (x >= 0) && (x < MAX_X) &&
		   (y >= 0) && (y < MAX_Y) &&
		   !((x == (MAX_X-1)) && (y == 0)) &&
		   !((x == (MAX_X-1)) && (y == (MAX_Y-1)));
}

//dp[current_length][x_position][y_position][current_number_of_vowels] - count number of sequences of length
// current_length, which end in position (x_position, y_position) and have current_number_of_vowels
long long find_count()
{
	memset(dp,0,sizeof(dp));
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			if (correct_position(i,j))
				dp[1][i][j][is_vowel[i][j]] = 1;
	for (int length = 2; length <= MAX_LENGTH; length ++)
		for (int i = 0; i < MAX_X; i++)
			for (int j = 0; j < MAX_Y; j++)
				if (correct_position(i,j))
					for (int move = 0; move < MAX_MOVES; move++)
						if (correct_position(i + dx[move], j + dy[move]))
							if (is_vowel[i][j])
							{
								for (int vowel = 0; vowel < MAX_VOWELS; vowel++)
									dp[length][i][j][vowel+1] += dp[length - 1][i + dx[move]][j + dy[move]][vowel];
							} else
							{
								for (int vowel = 0; vowel < MAX_VOWELS+1; vowel++)
									dp[length][i][j][vowel] += dp[length - 1][i + dx[move]][j + dy[move]][vowel];
							}
	long long total_sequences = 0;
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			if (correct_position(i,j))
				for (int vowel = 0; vowel < MAX_VOWELS+1; vowel ++)
					total_sequences += dp[MAX_LENGTH][i][j][vowel];
	return total_sequences;
}

// From position (x,y) find all possible knight moves
void backtracking(int x, int y)
{
	s[current_length++] = matrix[x][y];
	current_vowels += is_vowel[x][y];
	if (current_vowels > MAX_VOWELS)
	{
		current_vowels -= is_vowel[x][y];
		current_length--;
		return;
	}
	if (current_length == MAX_LENGTH)
	{
		printf("%s\n", s);
		current_length--;
		current_vowels-= is_vowel[x][y];
		return;
	}
	for (int move = 0; move < MAX_MOVES; move++)
		if (correct_position(x + dx[move], y + dy[move]))
			backtracking(x + dx[move], y + dy[move]);
	current_length--;
	current_vowels -= is_vowel[x][y];
}

int main(void)
{
	//numbers of sequences P.S. find with DP
	long long cnt = find_count();
	printf("%lld\n",cnt);
	s[MAX_LENGTH] = '\0';
	for (int i = 0; i < MAX_X; i++)
		for (int j =0 ; j < MAX_Y; j++)
			if (correct_position(i,j))
				backtracking(i,j);
	return 0;
}
