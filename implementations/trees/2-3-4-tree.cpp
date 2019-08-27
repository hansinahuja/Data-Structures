#include <iostream>
using namespace std;

class Node{
    public:
    int nkeys;
    int keys[4];
    Node *parent;
    Node *children[5];
};

class Tree{
    public:
    Node *root;
};

Node *search(Tree *t, int val){
    if(t==NULL){
        cout<<"Root node pointer is NULL.\n";
        return NULL;
    }
    Node *p;
    p = t->root;
    while(p!=NULL){
        for(int i=0; i<p->nkeys; i++){
            if(p->keys[i] == val){
                cout<<val<<" found in the tree.\n";
                return p;
            }
            if(i==p->nkeys-1){
                if(p->keys[i]<val){
                    p = p->children[i+1];
                    break;
                }
                else{
                    p = p->children[i];
                    break;
                }
            }
            else{
                if(p->keys[i]>val){
                    p = p->children[i];
                    break;
                }
            }
        }
    }
    cout<<val<<" not found in tree.\n";
    return NULL;
}

void split_node(Tree *t, Node *p){
    if(p->nkeys<4){
        return;
    }
    if(p == t->root){
        Node *n;
        Node *new_root;
        n = (Node *)malloc(sizeof(Node));
        new_root = (Node *)malloc(sizeof(Node));
        n->nkeys =  2;
        n->keys[0] = p->keys[2];
        n->keys[1] = p->keys[3];
        n->children[0] = p->children[2];
        n->children[1] = p->children[3];
        n->children[2] = p->children[4];
        n->parent = new_root;
        p->nkeys = 1;
        p->parent = new_root;
        new_root->nkeys = 1;
        new_root->keys[0] = p->keys[1];
        new_root->children[0] = p;
        new_root->children[1] = n;
        new_root->parent = NULL;
        t->root = new_root;
        return;
    }
    else{
        Node *n;
        n = (Node *)malloc(sizeof(Node));
        n->nkeys =  2;
        n->keys[0] = p->keys[2];
        n->keys[1] = p->keys[3];
        n->children[0] = p->children[2];
        n->children[1] = p->children[3];
        n->children[2] = p->children[4];
        n->parent = p->parent;
        p->nkeys = 1;
        int insert_pos;
        for(int i=0; i<=p->parent->nkeys; i++){
            if(p->parent->children[i] == p){
                insert_pos = i;
                break;
            }
        }
        for(int i=p->parent->nkeys; i>insert_pos; i--){
            p->parent->keys[i] = p->parent->keys[i-1];
        }
        p->parent->keys[insert_pos] = p->keys[1];
        for(int i=p->parent->nkeys+1; i>insert_pos+1; i--){
            p->parent->children[i] = p->parent->children[i-1];
        }
        p->parent->children[insert_pos+1] = n;
        split_node(t, p->parent);
        return;
    }
}

int insert(Tree *t, int val){
    Node *q;
    q = search(t, val);
    if(q != NULL){
        cout<<val<<" already exists in the tree.\n";
        return 0;
    }
    Node *p;
    p = t->root;
    if(p==NULL){
        Node *n;
        n = (Node *)malloc(sizeof(Node));
        n->nkeys = 1;
        n->keys[0] = val;
        n->parent = NULL;
        n->children[0] = NULL;
        n->children[1] = NULL;
        t->root = n;
        cout<<val<<" successfully inserted in the tree.\n";
        return 1;
    }
    while(1){
        for(int i=0; i<p->nkeys; i++){
            if(p->keys[i]>val){
                if(p->children[i]==NULL){
                    for(int j=p->nkeys; j>i; j--){
                        p->keys[j] = p->keys[j-1];
                    }
                    p->keys[i] = val;
                    for(int j=p->nkeys+1; j>i; j--){
                        p->children[j] = p->children[j-1];
                    }
                    p->children[i] = NULL;
                    p->nkeys++;
                    split_node(t, p);
                    cout<<val<<" successfully inserted in the tree.\n";
                    return 1;
                }
                else{
                    p = p->children[i];
                    break;
                }
            }
            else{
                if(i==p->nkeys-1){
                    if(p->children[p->nkeys] == NULL){
                        p->keys[p->nkeys] = val;
                        p->children[p->nkeys+1] = NULL;
                        p->nkeys++;
                        split_node(t, p);
                        cout<<val<<" successfully inserted in the tree.\n";
                        return 1;
                    }
                    else{
                        p = p->children[i+1];
                        break;
                    }
                }
            }
        }
    }
}

void print_node(Node *n){
    if(n==NULL){
        return;
    }
    cout<<"( ";
    for(int i=0; i<n->nkeys; i++){
        print_node(n->children[i]);
        cout<<n->keys[i]<<" ";
    }
    print_node(n->children[n->nkeys]);
    cout<<") ";
    return;
}

void inorder_traversal(Tree *t){
    if(t==NULL){
        cout<<"Root node pointer is NULL.\n";
    }
    else{
        print_node(t->root);
        cout<<"\n";
    }
    return;
}

int main(){
    Tree *t;
    t = (Tree *)malloc(sizeof(Tree));
    int choice = 1;
    int val, success;
    Node *n;
    cout<<"Available choices:\n";
    cout<<"1. Insert node\n";
    cout<<"2. Search for node\n";
    cout<<"3. Delete node\n";
    cout<<"4. Print tree\n";
    cout<<"5. Exit\n";
    do{
        cout<<"Enter choice: ";
        cin>>choice;
        if(choice==1){
            cout<<"Enter value to be inserted: ";
            cin>>val;
            success = insert(t, val);
        }
        else if(choice==2){
            cout<<"Enter value to be searched: ";
            cin>>val;
            n = search(t, val);
        }
        else if(choice==3){
            cout<<"Enter value to be deleted: ";
            cin>>val;
            // success = delete_node(t, val);
        }
        else if(choice==4){
            inorder_traversal(t);
        }
        else if(choice!=5){
            cout<<"Invalid choice.\n";
        }
    }while(choice!=5);
}
