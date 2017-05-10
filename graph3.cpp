#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>
#include<queue>
#include<sstream>
#include<iomanip>

using namespace std;

#define INF 100

struct Graph {
    int n, d[100];
    int A[100][100], D[100][100], p[100][100];
    bool checked[100];
    int previous[100];

    void readFile(const char* name);
    void print();
    void printStep();
    void Dijkstra(int, int);
    void Bellman_Ford(int, int);
    void Floyd();
};

void Graph::readFile(const char* name) {
    ifstream fd(name);
    fd >> n;
    fd.ignore();
    for (int i = 1; i <= n; i++) {
        checked[i] = false;
        for (int j = 1; j <= n; j++) {
            if (i == j)
                A[i][j] = 0;
            else
                A[i][j] = INF;
        }
    }
    string s;
    int i, j, w;
    while (!fd.eof()) {
        getline(fd, s);
        istringstream strStream(s);
        strStream >> i >> j >> w;
        A[i][j] = w;
    }
    fd.close();
}

void Graph::print() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
            if (A[i][j] == INF)
                cout << setw(3) << "oo" << " ";
			else
                cout << setw(3) << A[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void Graph::printStep() {
    for (int i = 1; i <= n; i++) {
        if (d[i] == INF)
            cout << "<oo, " << previous[i] << "> ";
        else
            cout << "<" << d[i] << ", " << previous[i] << "> ";
    }
    cout << endl;
}

void Graph::Dijkstra(int s, int t) {
    d[s] = 0;
    checked[s] = true;
    for (int v = 1; v <= n; v++) {
            d[v] = A[s][v];
            previous[v] = s;
    }

    for (int i = 1; i <= n - 1; i++) {
        int minp = INF, u;
        for (int j = 1; j <= n; j++) {
            if (!checked[j] && d[j] != INF && d[j] < minp) {
                minp = d[j];
                u = j;
            }
        }
        checked[u] = true;
        for (int v = 1; v <= n; v++) {
            if (!checked[v] && d[v] > d[u] + A[u][v]) {
                d[v] = d[u] + A[u][v];
                previous[v] = u;
            }
        }
        printStep();
    }

    cout << endl << "Duong di ngan nhat tu " << s << " den " << t << " la :" << endl;
    cout << t << " <= ";
    int i = previous[t];
    while (i != s) {
        cout << i << " <= ";
        i = previous[i];
    }
    cout << s << endl;
    cout << "Do dai duong di: " << d[t];
}

void Graph::Bellman_Ford(int s, int t) {
    d[s] = 0;
    checked[s] = true;
    for (int v = 1; v <= n; v++) {
            d[v] = A[s][v];
            previous[v] = s;
    }
    printStep();
    for (int k = 1; k <= n - 2; k++) {
        for (int v = 1; v <= n; v++) {
            if (v != s)
                for (int u = 1; u <= n; u++) {
                    if (d[v] > d[u] + A[u][v]) {
                        d[v] = d[u] + A[u][v];
                        previous[v] = u;
                    }
                }
        }
        printStep();
    }
}

void Graph::Floyd() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            D[i][j] = A[i][j];
            p[i][j] = i;
        }
    for (int k = 1; k <= n; k++) {
        cout << "k = " << k << endl;
        for (int i = 1; i <= n; i++) {
            cout << "   i = " << i << endl;
            for (int j = 1; j <= n; j++)
                if (D[i][k] != INF && D[k][j] != INF && D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    p[i][j] = p[k][j];
                    cout << "       "
                        << "D[" << i << "][" << j << "] = "
                        << "D[" << i << "][" << k << "] + "
                        << "D[" << k << "][" << j << "] = "
                        << D[i][k] << " + " << D[k][j] << " = "
                        << D[i][j] << endl;
                }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            if (D[i][j] == INF)
                cout << "oo ";
            else
                cout << setw(2) << D[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << p[i][j] << " ";
        cout << endl;
    }
}

int main() {
    Graph g;
	//g.readFile("graph3.txt"); g.print(); g.Dijkstra(1, 10);
	//g.readFile("graph4.txt"); g.print(); g.Bellman_Ford(1, 10);
	g.readFile("graph5.txt"); g.print(); g.Floyd();
}
