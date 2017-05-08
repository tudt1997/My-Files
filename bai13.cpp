#include<iostream>
#include<fstream>
#include<cstring>
#include <iomanip>
using namespace std;
struct node{
	int info;
	struct node *link;
};
struct nodel{
	int info;
	struct nodel *next;
};
class list{
	public: nodel *start;
	public:
		list(){
			start = NULL;
		}
		struct nodel *createnode(int value){
			nodel *temp;
			temp = new nodel;
			if (temp == NULL){
				return 0;
			}else{
				temp->info = value;
				temp->next = NULL;
				return temp;
			}
		}
		void insertlast(int value){
			nodel *temp,*s;
			temp = createnode(value);
			if (start == NULL){
				start = temp;
				start->next = NULL;
				return;
			}
			s = start;
			while(s->next != NULL){
				s = s->next;
			}
			temp->next = NULL;
			s->next = temp;
		}
		void insertbegin(int value){
            struct nodel *temp, *p;
            temp = createnode(value);
            if (start == NULL){
                start = temp;
                start->next = NULL;          
            } 
            else {
                p = start;
                start = temp;
                start->next = p;
            }
		}
		void display(){
			nodel *s;
			if (start == NULL){
				cout << "Noi dung rong" << endl;
				return ;
			}else{
				s = start;
				while(s!=NULL){
					cout << s->info << "  ";
					s = s->next;
				}cout << endl;
			}
		}
		int deletepos(int a){
			nodel *temp,*s,*t,*prev;
			if (start == NULL){
				return 0;
			}else{
				s = start;
				if(s->info == a){
					start = start->next;
					delete(s);
					return 1;
				}
				while(s->next!=NULL){
					prev = s;
					s = s->next;
					if (s->info == a){
						prev->next = s->next;
						delete(s);
						return 1;
					}
				}
			}
			return 0;
		}
};
class stacklist{
	public :
		node *stack;
	    stacklist(){
	    	stack = NULL;
	    }
	    void *push(int value){
	    	node *temp;
	    	temp = new node;
	    	temp->info = value;
	    	temp->link = stack;
	    	stack = temp;
		}
		node *pop(){
			node *temp;
			if (stack == NULL){
				cout << "Stack rong" << endl;
			}else{
				temp = stack;
				stack = stack->link;
			}
			return temp;
		}
		int traverse(node *stack){
			node *pos;
			pos = stack;
			if (stack==NULL){
				cout << "Stack rong" << endl;
			}else{
				while(pos != NULL){
					cout << pos->link << "  ";
					pos = pos->link;
				}
			}
		}
	
};
void init(int a[10][10], int &n){
	ifstream fd ("dothi13.txt");
	fd >> n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			fd >> a[i][j];
		}
	}
}
void dske(list*T,int mt[10][10],int n){
	for(int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if (mt[i][j] == 1){
				T[i].insertlast(j);
			}
		}
	}
}
void path(list *T,int u,int n){
	list A;
	A.insertlast(3);
	A.insertlast(2);
	A.insertlast(2);
	A.insertlast(3);
	A.insertlast(2);
//	A.deletepos(2);
//	A.display();
    nodel *a=A.start;
	while (1){
		if (A.deletepos(2))
	    	cout <<	1 << endl;
	    else
	    	break;
	}
//	stacklist s;
//	int a,k=0;
//	int *CE = new int[n];
//    s.push(u);
//    while(s.stack != NULL){
//    	a = s.stack->info;
//    	if(T[a].start != NULL){
//    		int t = T[a].start->info;
//    		s.push(t);
//    		T[a].deletepos(t);
//    		T[t].deletepos(a);
//		}else{
//			s.pop();
//			CE[k] = a;
//			k++;
//		}
//	}
//	cout<<"\n Ket qua:";
//	for(int t=k-1;t>=0; t--){
//		cout<<CE[t]<<"-";
//	}
}
int degr(int mt[10][10],int u,int n){
	int dem=0;
	for(int i=1;i<=n;i++){
		if(mt[u][i] == 1){
			dem++;
		}
	}
	return dem;
}
int degv(int mt[10][10],int u,int n){
	int dem=0;
	for(int i=1;i<=n;i++){
		if(mt[i][u]==1){
			dem++;
		}
	}
	return dem;
}
void semieuler(int mt[10][10],int n){
	int s,t;
	int dem1=0,dem2=0;
	for(int i=1;i<=n;i++){
		if(degr(mt,i,n)-degv(mt,i,n) == 1){
			dem1++;
			s = i;
		}
		if(degv(mt,i,n)-degr(mt,i,n) == 1){
			dem2++;
		}
	}
	if (dem1==1 || dem2==1){
		cout << "YES" << endl;
		list *T = new list[n+1];
		dske(T,mt,n);
		path(T,s,n);
	}else{
		cout << "NO";
	}
}
int main(){
	int mt[10][10],n;
	init(mt,n);
	semieuler(mt,n);
	return 0;
}
