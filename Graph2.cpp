// C++ program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph
#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>
#include<queue>
#include<sstream>
using namespace std;
#define MAX 10000
#define INF 0x3f3f3f3f
int n = 9;
int M[100][100];
bool unTraversed[100];
int previous[100];

// Creating shortcut for an integer pair
typedef  pair<int, int> iPair;

// Structure to represent a graph
struct Graph{
    int V, E;
    vector< pair<int, iPair> > edges;
    list< pair<int, int> > *adj;

    // Constructor
    Graph(int V){
        this->V = V;
        adj = new list<iPair> [V];
        this->E = 0;
    }

    // Utility function to add an edge
    void addEdge(int u, int v, int w){
        edges.push_back({w, {u, v}});
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    void readFile(const char*);
    void readFile2(const char*);
    void print();
    // Function to find MST using Kruskal's
    // MST algorithm
    int kruskalMST();
    void kruskal();
    void prim();
};

// To represent Disjoint Sets
struct DisjointSets{
    int *parent, *rnk;
    int n;

    // Constructor.
    DisjointSets(int n){
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++){
            rnk[i] = 0;

            //every element is parent of itself
            parent[i] = i;
        }
    }

    // Find the parent of a node 'u'
    // Path Compression
    int find(int u){
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y){
        x = find(x), y = find(y);

        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

 /* Functions returns weight of the MST*/

int Graph::kruskalMST(){
    int mst_wt = 0; // Initialize result

    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
    cout << "After sort \n" << endl;
    print();
    // Create disjoint sets
    DisjointSets ds(V);

    cout << "Edges of MST are \n";
    // Iterate through all sorted edges
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++){
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v){
            int w = it->first;
            // Current edge will be in the MST
            // so print it
            cout << u + 1 << " - " << v + 1 << "   " << w << endl;

            // Update MST weight
            mst_wt += w;

            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
}

void Graph::kruskal() {
    int mst_wt = kruskalMST();
    cout << "\nWeight of MST is " << mst_wt;
}

void Graph::prim(){
    // Create a priority queue to store vertices that
    // are being preinMST. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

    int src = 0; // Taking vertex 0 as source

    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key(V, INF);

    // To store parent array which in turn store MST
    vector<int> parent(V, -1);

    // To keep track of vertices included in MST
    vector<bool> inMST(V, false);

    // Insert source itself in priority queue and initialize
    // its key as 0.
    pq.push(make_pair(0, src));
    key[src] = 0;

    /* Looping till priority queue becomes empty */
    while (!pq.empty()){
        // The first vertex in pair is the minimum key
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted key (key must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;  // Include vertex in MST

        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i){
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;

            //  If v is not in MST and weight of (u,v) is smaller
            // than current key of v
            if (inMST[v] == false && key[v] > weight){
                // Updating key of v
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // Print edges of MST using parent array
    cout << "Edges of MST are \n";
    for (int i = 1; i < V; ++i)
        cout << parent[i] << " - " << i << "   " << key[i] << endl;
}

void Graph::print() {
    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++) {
        int u = it->second.first;
        int v = it->second.second;
        int w = it->first;
        cout << u + 1 << " - " << v + 1 << "   " << w << endl;
    }
}
void Graph::readFile (const char* name) {
	ifstream fd(name);
	fd >> n;
    V = n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			fd >> M[i][j];
            addEdge(M[i][j], i, j);
            E++;
		}
    fd.close();
}

void Graph::readFile2 (const char* name) {
	ifstream fd(name);
	fd >> n;
	fd.ignore();
	string s;
	int w;
	while (!fd.eof()) {
        getline(fd, s);
        istringstream strStream(s);
        int i, j;
        strStream >> i >> j >> w;
        M[i][j] = w;
        addEdge(i, j, w);
        E++;
	}
    fd.close();
}

int main() {
    Graph g(9);
    g.readFile2("graph2.txt");
    cout << "List of edges: \n";
    g.print();
    //g.kruskal();
    g.prim();
}
