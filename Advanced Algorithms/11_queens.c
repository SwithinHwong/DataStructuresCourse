#include "stdio.h"
#define DEBUG 0

void print_chessboard(int chess_board[8][8])
{
	int i,j;
	static int case_times = 1;
	printf("Case %d:\n",case_times++ );
	
	if (DEBUG)
	{
		for ( i = 0; i < 8; ++i)
		{
			for ( j = 0; j < 8; ++j)
				printf("%3d ",chess_board[i][j] );
			printf("\n\n");
		}

	}
	else
	{
		for ( i = 0; i < 8; ++i)
		{
			for ( j = 0; j < 8; ++j)
				printf("%3c ",chess_board[i][j] == -1 ? 'Q':'.' );
			printf("\n\n");
		}
	}

	printf("*****************\n");
}


int add_queen(int chess_board[8][8], int row, int col)
{
	/*往棋盘中坐标为grid的位置放入皇后（值从0变为-1）
	把这个皇后控制的区域值加1*/

	//如果要放入皇后的位置为0，就不可以放入
	if (chess_board[row][col])
		return 0;

	chess_board[row][col] = -1;//放入皇后

	int i;
	for ( i = 0; i < 8; ++i)
		if (i != row)
			++chess_board[i][col];	//	同列元素+1
	for ( i = 0; i < 8; ++i)
		if (i != col)
			++chess_board[row][i];	//同行元素+1


	int sum = row+col;
	int j=0;
	for ( i = 0; i < 8; ++i)
	{
		if (i == row)
			continue;
		j = sum - i;
		if (j>-1 && j<8)
			chess_board[i][j]++;	//45°对角线上所有元素+1
	}

	int difference = col-row;
	for ( i = 0; i < 8; ++i)
	{
		if (i == row)
			continue;
		j = i + difference;
		if (j>-1 && j<8)
			chess_board[i][j]++;	//135°对角线上所有元素+1
	}

	return 0;
}


int remove_queen(int chess_board[8][8], int row, int col)
{
	/*往棋盘中坐标为grid的位置移除皇后（值从-1变为0）
	把这个皇后控制的区域值减1*/

	//如果要移除皇后的位置不为-1，本来没有皇后
	if (chess_board[row][col] != -1)
		return 0;

	chess_board[row][col] = 0;//移除皇后

	int i;
	for ( i = 0; i < 8; ++i)
		if (i != row)
			--chess_board[i][col];	//	同列元素-1
	for ( i = 0; i < 8; ++i)
		if (i != col)
			--chess_board[row][i];	//同行元素-1


	int sum = row+col;
	int j=0;
	for ( i = 0; i < 8; ++i)
	{
		if (i == row)
			continue;
		j = sum - i;
		if (j>-1 && j<8)
			--chess_board[i][j];	//45°对角线上所有元素-1
	}

	int difference = col-row;
	for ( i = 0; i < 8; ++i)
	{
		if (i == row)
			continue;
		j = i + difference;
		if (j>-1 && j<8)
			--chess_board[i][j];	//135°对角线上所有元素-1
	}

	return 0;
}


void _queen(int chess_board[8][8], int col)
{
	/*
	chessboard里为0是可以放入旗子的位置
	运行本次迭代时，第col前所有列，每列应该都有一个不相互干涉的皇后
	向第col+1列内可以放入皇后的格子依次放入皇后，
	迭代寻找下一列可以放入皇后的格子
	*/
	

	int row;
	for ( row = 0; row < 8; ++row)
	{
		if (chess_board[row][col])
			continue;	//这个格子不能放入皇后

		add_queen(chess_board, row, col);
		if (col >= 7)
		{
			print_chessboard(chess_board);
		}
		else
			_queen(chess_board, col+1);

		remove_queen(chess_board, row, col);


	}



	return;

}


int queen()
{
	int i,j;
	int chess_board[8][8];
	for ( i = 0; i < 8; ++i)
		for ( j = 0; j < 8; ++j)
			chess_board[i][j] = 0;

	_queen(chess_board, 0);

	return 0;
}



int main(int argc, char const *argv[])
{
	queen();
	return 0;
}
