#include <iostream>
using namespace std;

template <typename T>
class Node{
    public:
        T val;
        Node<T>* left;
        Node<T>* right;
        Node(){
            left = NULL;
            right = NULL;
        }
};

template <typename T>
class linkedList{
    public:
        Node<T> *head;
        linkedList(){
            head = NULL;
        }
        
        void insert(T key){
            Node<T> *n = new Node<T>();
            n->val = key;
            if(head==NULL){
                n->left = n;
                n->right = n;
                head = n;
                return;
            }
            n->left = head->left;
            n->right = head;
            head->left->right = n;
            head->left = n;
            head = n;
            return;
        }
        
};

int main(void){
    int n;
    cin>>n;
    int a[n];
    linkedList<int> h[n];
    for(int i=0; i<n; i++) cin>>a[i];
    for(int i=0; i<n; i++) h[a[i]%n].insert(a[i]);
    int curr = 0;
    for(int i=0; i<n; i++){
        Node<int> *c = h[i].head;
        if(h[i].head == NULL) continue;
        do{
            a[curr] = c->val;
            c = c->right;
            curr++;
        }while(h[i].head != c);
        h[i].head = NULL;
    }
    
    for(int i=0; i<n; i++) h[a[i]/n].insert(a[i]);
    curr = 0;
    for(int i=0; i<n; i++){
        if(h[i].head == NULL) continue;
        Node<int> *c = h[i].head->left;
        do{
            a[curr] = c->val;
            c = c->left;
            curr++;
        }while(h[i].head->left != c);
    }
   
    for(int i=0; i<n; i++) cout<<a[i]<<" ";
   
}
