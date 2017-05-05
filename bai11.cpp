#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include <cstdlib>
using namespace std;
struct node{
	int info;
	struct node *next;
};
class single_list {
	node *start;
	public :
		single_list() {
			start = NULL;
		}
		struct node *createnode(int value){
			node *temp;
			temp = new node;
			if (temp == NULL){
				return 0;
			}else{
				temp->info = value;
				temp->next = NULL;
				return temp;
			}
		}
		void insertlast(int value){
			node *temp,*s;
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
            struct node *temp, *p;
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
			struct node *temp;
			if (start == NULL){
				cout << "Noi dung danh sach rong" << endl;
				return;
			}
			temp = start;
			while (temp != NULL){
				cout << temp->info << "   "; 
				temp = temp->next;
			}
			cout << endl;
		}
};
void check(string s,single_list &T){
	int a;
	for (int i=0;i<s.size();i++){
		if (s[i] != ' '){
			a = s[i] - '0';
			T.insertlast(a);
		}
	}
}
void init(){
	ifstream fd ("dske11.txt");
	string s;
	int n;
	int i=0;
	fd >> n;
	single_list *T = new single_list[n];
	fd.ignore();
    for(int i=0;i<n;i++){
		getline(fd,s); 
		check(s,T[i]);
		T[i].display();
	}
}
int main(){
    init();
}
