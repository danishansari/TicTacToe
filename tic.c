#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void disp_board();
void update_board(int, int);
void input();
int cpu(int);
int posswin();

int board[3][3], dir, ind;

int main()
{
	int i, j;
	char ch;
	while(1)
	{
		for(i=0;i<3;i++)
		    for(j=0;j<3;j++)
		        board[i][j] = 2;
		disp_board();
		input();
		fflush(stdin);
  		printf("\nPlay again(y/n)? ");
		scanf("%c", &ch);
		if(ch == 'y' || ch == 'Y')
		    main();
		else
		    break;;
	}
	return 0;
}

void disp_board()
{
    int i, j;
    system("cls");
	printf("Let's play Tic Tac Toe.\n\n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(board[i][j] == 2)
				printf("%c ", i*3+j+1+48);
			else if(board[i][j] == 4)
				printf("O ");
			else
				printf("x ");
		}
		printf("\n");
	}
}

void input()
{
	char p;
	int turn=1, pos, g;
	while(1)
	{
		if(turn%2)
		{
			printf("\nEnter your position('q' to abort): ");
			fflush(stdin);
			scanf("%c", &p);
			if(p == 'q' || p == 'Q')
			    exit(0);
			else
			{
				pos = p;
				pos -= 48;
			}
			if(pos < 1 && pos > 9)
			{
				printf("\nInavalid position.");
			}
			if(board[pos/3][pos%3-1] != 2)
			{
				printf("\nPossition already occupied.");
				continue;
			}
		}
		else
			pos = cpu(turn);
		update_board(pos, turn);
		g = game();
		if(g == 27)
		{
			printf("\nYou won.");
			return;
		}
		else if(g == 64)
		{
			printf("\nCpu won.");
			return;
		}
		else if(turn == 8)
		{
			printf("\nMatch draw.");
			return;
		}
		turn++;
	}
}

int cpu(int t)
{
	int a, i;
	if(t == 4 && board[1][1] == 3)
	{
	    if(board[2][2] == 3)
	    	return 7;
	}
	if(t == 2)
	{
		if(board[1][1] == 2)
	    	return 5;
	 	else if(board[0][0] == 2)
	 	    return 1;
	}
	else
	{
		a = posswin(t);
		if(a == 27 || a == 64)
		    return a;
		else
		{
			if(dir == 1)
			{
				for(i=0;i<3;i++)
					if(board[ind][i] == 2)
					    return ind*3+i+1;
			}
			else if(dir == 2)
			{
                for(i=0;i<3;i++)
					if(board[i][ind] == 2)
					    return i*3+ind+1;
			}
			else if(dir == 3)
			{
                for(i=0;i<3;i++)
					if(board[i][i] == 2)
					    return i*3+i+1;
			}
			else if(dir == 4)
			{
                for(i=0;i<3;i++)
					if(board[i][2-i] == 2)
					    return i*3+(2-i)+1;
			}
		}
	}
	
}

int posswin()
{
	int pro1, pro2, ans=8, i, j;
	for(i=0;i<3;i++)
	{
		pro1 = board[i][0]*board[i][1]*board[i][2];
		if(pro1 == 24 || pro1 == 36 || pro1 == 48)
		    pro1 = 1;
		pro2 = board[0][i]*board[1][i]*board[2][i];
		if(pro2 == 24 || pro2 == 36 || pro2 == 48)
		    pro2 = 1;
		if(pro1 > ans || pro2 > ans)
		{
			if(pro1 >= pro2)
			{
		    	ans = pro1;
		    	ind = i;
		    	dir = 1;
			}
			else
			{
		    	ans = pro2;
		    	ind = i;
		    	dir = 2;
			}
		}
	}
	pro1 = board[0][0]*board[1][1]*board[2][2];
	if(pro1 == 24 || pro1 == 36 || pro1 == 48)
		    pro1 = 1;
	pro2 = board[0][2]*board[1][1]*board[2][0];
	if(pro2 == 24 || pro2 == 36 || pro2 == 48)
		    pro2 = 1;
	if(pro1 > ans || pro2 > ans)
	{
		if(pro1 > pro2)
		{
	    	ans = pro1;
	    	ind = 0;
	    	dir = 3;
		}
		else
		{
	    	ans = pro2;
	    	ind = 0;
	    	dir = 4;
		}
	}
	return ans;
}

void update_board(int p, int q)
{
	int i, j;
	i = p/3;
	j =p%3-1;
	if(q%2)
		board[i][j] = 3;
	else
	    board[i][j] = 4;
	disp_board();
	return;
}

int game()
{
	int pro1, pro2, i;
	pro1 = board[0][0]*board[1][1]*board[2][2];
	pro2 = board[0][2]*board[1][1]*board[2][0];
    if(pro1 == 27 || pro1 == 64)
		return pro1;
	else if(pro2 == 27 || pro2 == 64)
		return pro2;
    for(i=0;i<3;i++)
	{
		pro1 = board[i][0]*board[i][1]*board[i][2];
		pro2 = board[0][i]*board[1][i]*board[2][i];
		if(pro1 == 27 || pro1 == 64)
		    return pro1;
		else if(pro2 == 27 || pro2 == 64)
		    return pro2;
	}
	return 0;
}
