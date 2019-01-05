#include "stdio.h"
#include <stdlib.h>

void print_chessboard(int chess_board[8][8])
{
	int i,j;
	for ( i = 0; i < 8; ++i)
	{
		for ( j = 0; j < 8; ++j)
			printf("%3d ",chess_board[i][j] );
		printf("\n\n");
	}
	printf("*****************\n");
}


int TestValidWays(int chess_board[8][8], int row, int col)
{
	/*计算可走的路径数量*/
	int i;
	int next_row[8] = {-2, -1, 1, 2, 2, 1, -1, -2};  //下一步访问的各个点相对当前点位置
	int next_col[8] = {1, 2, 2, 1, -1, -2, -2, -1};


	int nValid=0;
	int temp_row, temp_col;
	for ( i = 0; i < 8; ++i)
	{
		temp_row = row + next_row[i];
		temp_col = col + next_col[i];
		if (temp_row < 0 || temp_row >7 || temp_col < 0 || temp_col >7)
			continue;	//超出棋盘范围
		if ( chess_board[temp_row][temp_col] )
			continue;	//要访问的点已经访问过了
		nValid ++;
	}

    return nValid;
}

int _knight(int chess_board[8][8], int row, int col, int move_times)
{
	/*
	棋盘内，0为未走过的点，走过的点按访问顺序填入1，2，...
	row col为本次要访问的点
	move_times是本次访问填入棋盘的值
	*/
	
	int i;
	int next_row[8] = {-2, -1, 1, 2, 2, 1, -1, -2};  //下一步访问的各个点相对当前点位置
	int next_col[8] = {1, 2, 2, 1, -1, -2, -2, -1};

	// int next_row[8]={2,1,-1,-2,-2,-1, 1, 2};
	// int next_col[8]={1,2, 2, 1,-1,-2, -2,-1};

	if (row < 0 || row >7 || col < 0 || col >7)
		return 0;	//超出棋盘范围
	if (chess_board[row][col] )
		return 0;	//要访问的点已经访问过了

	chess_board[row][col] = move_times;

	if (move_times == 64)
		return 1;	//遍历完成


	//找出下一步棋中，再下一次可走路径最少的
	//先尝试这个点

	int least_ways = 9;
	int tested_ways;
	int try_row, try_col;
	int least_ways_row, least_ways_col;
	for ( i = 0; i < 8; ++i)
	{
		try_row = row + next_row[i];
		try_col = col + next_col[i];
		if (try_row < 0 || try_row >7 || try_col < 0 || try_col >7)
			continue;	//超出棋盘范围
		if (chess_board[try_row][try_col] )
			continue;	//要访问的点已经访问过了
		tested_ways = TestValidWays(chess_board, try_row, try_col);
			
		if (tested_ways < least_ways)
			{
				least_ways = tested_ways;
				least_ways_row = try_row;
				least_ways_col = try_col;
			}
	}


	if ( _knight(chess_board, least_ways_row, least_ways_col, move_times+1) )
	{
		return 1;
	}

	//如果上次选的路径无解，再遍历其他所有可能路径
	for ( i = 0; i < 8; ++i)
	{
		if ( _knight(chess_board, row + next_row[i], col + next_col[i], move_times+1) )
		{
			return 1;
		}
	}


	// printf("%d\n",move_times );
	// print_chessboard(chess_board);
	chess_board[row][col] = 0;
	return 0;
}

int knight(int row, int col)
{
	int i,j,flag;
	int chess_board[8][8];
	for ( i = 0; i < 8; ++i)
		for ( j = 0; j < 8; ++j)
			chess_board[i][j] = 0;
	flag = _knight(chess_board, row, col, 1);
	print_chessboard(chess_board);
	return flag;


}

int main(int argc, char const *argv[])
{
	printf("Enter starting row and col:\n");
	int row,col;
	scanf("%d", &row);
	scanf("%d", &col);
	knight(row-1, col-1);
	return 0;
}
