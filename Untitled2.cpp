#include<iostream>
#include<list>
#include<fstream>
#include<iomanip>
#include<stack>
using namespace std;
struct canh{//bieu dien 1 canh cua do thi
	int dau;
	int cuoi;
};
class Graph{
	private:
		int V;// so dinh cua do thi
		list<int> *adj;//con tro den mang cac danh sach ke
		bool *chuaxet; // mang chua xet
		canh *T; //tap canh cua cay khung
		int sc; //so canh cua cay khung
	public:
		printGraph(int V); //constructor cua lop
		void addEdge(int v,int w);
		void Tree_DFS(int u);//		
		
};
Graph::printGraph(int V){
	this->V=V;//thiet lap tap dinh
	adj=new list<int>[V];//thiet lap V danh sach ke
	T=new canh[V]; sc=1;
	chuaxet=new bool[V];
	for(int u=0; u<V; u++) 
		chuaxet[u]=true;
}
void Graph::addEdge(int v,int w){//them mot canh vao danh sach ke
	adj[v].push_back(w);//them w vao list(v)
	adj[w].push_back(v);//them v vao list(w)
}
void Graph::Tree_DFS(int u){
	stack<int>Stack;//tao Stack rong
	Stack.push(u);//dua u vao ngan xep
	chuaxet[u]=false;//xac nhan u da xet
	list<int>::iterator t;//i la iterator cua list
	while(!Stack.empty()){//Lap den khi stack rong
		int s=Stack.top();//lay s la dinh dau ngan xep
		Stack.top();//loai s ra khoi ngan xep
		for(t=adj[s].begin();t!=adj[s].end();++t){//duyet tren list(s)
			if(chuaxet[*t]){
			Stack.push(s);//dua s vao stack truoc
			Stack.push(*t);//dua t vao stack sau
			chuaxet[*t]=false;//ghi nhan t da xet
			T[sc].dau=s; T[sc].cuoi=*t;//them (s,t) vao cay 
			sc++;//tang so canh len 1
			break;//chi lay dinh dau tien 
			}
		}
	}
	if(sc<V-1){//neu |T| <n-1
		cout<<"/n Do thi khong lien thong";
	}
	else{
		cout<<"/n Tap canh cau khung:"<<endl;
		for(int i=1; i<sc;i++){
			cout<<T[i].dau<<setw(3)<<T[i].cuoi<<endl;
		}
	}
}
int main(void){
	ifstream fp("Graph.in");//mo file doc
	int n,m,dau,cuoi;
	fp>>n>>m;//doc so dinh va so canh cua do thi
	Graph gh;
	for(int i=1; i<=m;i++){// chuyen do thi sang danh sach ke
		fp>>dau>>cuoi;
		gh.addEdge(dau,cuoi);
	}
	fp.close();
	gh.printGraph();
	gh.Tree_DFS(1);
}
