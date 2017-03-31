#define MAX 10
//a
#define LL long long
#define FOR(i, a, b) for(LL i = a; i <= b; i++)
#define FO(i, a, b) for(LL i = a; i < b; i++)
#define FORR(i, a, b) for(LL i = a; i <= b; i--)

#include<iostream>
#include<algorithm>
#include<string>
#include<queue>

using namespace std;

class Pos {
	public:
		LL x, y;
	
		Pos(LL x, LL y) {
			this->x = x;
			this->y = y;
		}
		
		Pos() {
			this->x = 0;
			this->y = 0;
		}
		
		void set(LL x, LL y) {
			this->x = x;
			this->y = y;
		}
		
		void add(LL a, LL b) {
			x += a;
			y += b;
		}
		
		Pos operator+(Pos pos) {
			Pos sum(this->x + pos.x, this->y + pos.y);
			return sum;
		} 
		
		bool operator==(Pos pos) {
			return this->x == pos.x && this->y == pos.y;
		}
		
		bool operator!=(Pos pos) {
			return !(*this == pos);
		}
};

class Graph {
	public:
		LL G[MAX][MAX];
		
		LL at(Pos p)
			return G[p.x][p.y];
};
Pos d[4] = {Pos(1, 0), Pos(0, 1), Pos(-1, 0), Pos(0, -1)}; //direction
Pos prev[MAX][MAX], O(0, 0); 
LL val[MAX][MAX];
Graph g;

queue<Pos> q;

void BFS(Pos p) {
	FO(i, 0, MAX)
		FO(j, 0, MAX)
			prev[i][j] = O;
			
	q.push(p);
	prev[p.x][p.y].set(-1, -1);
	while (!q.empty()) {
		Pos cur = q.front();
		q.pop();
		FO(i, 0, 4) {
			Pos next = cur + d[i];
			prev[next.x][next.y] = cur;
			if (g.at(next) != '#' && prev[next.x][next.y] != O) {
				q.push(next);
			}
		}
	}
}

int main() {
	return 0;
}

