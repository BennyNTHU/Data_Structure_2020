//EECS2040 Data Structure Hw #2 (Chapter 3 of textbook)
//due date 4/17/2021
//106061218, Cheng-En Lee
//Part 2, problem 3

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <stack>
#include <fstream>
using namespace::std;

struct offsets{
    int a, b;
};

enum directions{
    N, NE, E, SE, S, SW, W, NW 
};

struct Items{
	int x;
	int y;
	int dir;
};

void Path(const int, const int, bool**);

int main(int argc, char *argv[])
{
    int length = 9;
    int width = 9;
    char ch;
    string FilenameIn = argv[1];
    ifstream FileInput;
    
    FileInput.open(FilenameIn, ios::in);
    if (!FileInput)
    {
        cout << "File does not exist!";
        exit(1);
    }
    FileInput >> length;
    FileInput >> width;
    cout << "The length of this maze = " << length << endl;
    cout << "The width of this maze = " << width << endl;
    
    bool maze[length+2][width+2] = {0};
    for (int i=0; i<length+2; i++)
        for (int j=0; j<width+2; j++)
            maze[i][j]=true;

    for (int i=1; i<=length; i++)
        for (int j=1; j<=width; j++)
            FileInput >> maze[i][j];

    bool* M[length+2];
    for(int k = 0; k < length+2; k++)
        M[k]=maze[k];
    
    Path(length,width, M);

    return 0;
}


void Path(const int m, const int p, bool **maze)
{
    bool mark[m+2][p+2];
    for (int i=0; i<m+2; i++)
        for (int j=0; j<p+2; j++)
            mark[i][j]=false;

    mark[1][1] = 1;
    std::stack<Items> s;
    Items temp;    // 設定 temp.x、temp.y、與temp.dir
    temp.x = 1; 
    temp.y = 1; 
    temp.dir = E;

    offsets move[8] = {};
    move[0].a = -1;
    move[0].b = 0;
    move[1].a = -1;
    move[1].b = 1;
    move[2].a = 0;
    move[2].b = 1;
    move[3].a = 1;
    move[3].b = 1;
    move[4].a = 1;
    move[4].b = 0;
    move[5].a = 1;
    move[5].b = -1;
    move[6].a = 0;
    move[6].b = -1;
    move[7].a = -1;
    move[7].b = -1;

    s.push(temp);
    
    while (!s.empty())  // When stack is not empty
    {
        
        temp = s.top();
        s.pop();  // 彈出
        int i = temp.x;
        int j = temp.y; 
        int d = temp.dir; 

	    while (d<8)  // 往前移動
		{
            
		    int g = i + move[d].a; 
            int h = j + move[d].b;
		    if ((g==m) && (h==p)) // 抵達出口
            {
                cout << "find path!" << endl;
                int reverse_index = 0;
                Items path[s.size()];

                while(!s.empty())
                {
                    path[reverse_index] = s.top();
                    s.pop();
                    reverse_index++;
                }
                reverse(path, path + reverse_index);
                for (int index=0; index<reverse_index; index++)
                    cout << '(' << path[index].x << ',' << path[index].y << ')' << endl;

                cout << '(' << i << ',' << j << ')' << endl; // 路徑上的上兩個方塊
                cout << '(' << m << ',' << p << ')' << endl;
                return;
            }
            if ((!maze[g][h]) && (!mark[g][h]))   // 新位置
		    {	
                mark[g][h] = 1;
                temp.x = i;
                temp.y = j;
                temp.dir = d+1; //try new direction
                s.push(temp); // 加入堆疊
                i = g;
                j = h;
                d = N; // 移到 (g, h)
		    }
            else d++; // 試下一個方向
		}
	}
    cout << "No path in maze." << endl;
}
