#include <iostream>
using namespace std;

struct node{
    int val;
    struct node *left;
    struct node *right;
    struct node *parent;
};

struct tree{
    struct node *root;
};

struct node *search(struct tree *t, int v){
    if(t==NULL){
        cout<<"Root node pointer is NULL.\n";
        return NULL;
    }
    struct node *p;
    p = t->root;
    while(p!=NULL){
        if(p->val == v){
            cout<<"Value "<<v<<" found in tree.\n";
            return p;
        }
        else if(p->val > v){
            p = p->left;
        }
        else{
            p = p->right;
        }
    }
    cout<<"Value "<<v<<" not found in tree.\n";
    return NULL;
}

int insert(struct tree *t, int v){
    struct node *s;
    s = search(t, v);
    if(s!=NULL){
        return 0;
    }
    cout<<"Inserting "<<v<<" in the tree.\n"
    struct node *p;
    p = t->root;
    if(p==NULL){
        struct node *n;
        n = (struct node *)malloc(sizeof(struct node));
        n->val = v;
        n->left = NULL;
        n->right = NULL;
        n->parent = NULL;
        t->root = n;
        cout<<"Value "<<v<<" successfully inserted.\n";
        return 1;
    }

    while(1){
        if(p->val > v){
            if(p->left == NULL){
                struct node *n;
                n = (struct node *)malloc(sizeof(struct node));
                n->val = v;
                n->left = NULL;
                n->right = NULL;
                n->parent = p;
                p->left = n;
                cout<<"Value "<<v<<" successfully inserted.\n";
                return 1;
            }
            else{
                p = p->left;
            }
        }
        else{
            if(p->right == NULL){
                struct node *n;
                n = (struct node *)malloc(sizeof(struct node));
                n->val = v;
                n->left = NULL;
                n->right = NULL;
                n->parent = p;
                p->right = n;
                cout<<"Value "<<v<<" successfully inserted.\n";
                return 1;
            }
            else{
                p = p->right;
            }
        }
    }
}

struct node *find_replacement(struct node *p){
    if(p->right == NULL){
        return NULL;
    }
    else{
        p = p->right;
        while(p->left != NULL){
            p = p->left;
        }
        return p;
    }
}

int delete_node(struct tree *t, int v){
    struct node *p;
    p = search(t, v);
    if(p==NULL){
        return 0;
    }
    struct node *s;
    s = find_replacement(p);
    if(s==NULL){
        if(p->parent == NULL){
            t->root = p->left;
            if(p->left != NULL){
                p->left->parent = NULL;
            }
            free(p);
            cout<<"Value "<<v<<" successfully deleted.\n";
            return 1;
        }
        else{
            if(p->parent->right == p){
                p->parent->right = p->left;
                if(p->left != NULL){
                    p->left->parent = p->parent;
                }
                free(p);
                cout<<"Value "<<v<<" successfully deleted.\n";
                return 1;
            }
            else{
                p->parent->left = p->left;
                if(p->left != NULL){
                    p->left->parent = p->parent;
                }
                free(p);
                cout<<"Value "<<v<<" successfully deleted.\n";
                return 1;
            }
        }
    }
    else{
        p->val = s->val;
        if(s->parent->left == s){
            s->parent->left = s->right;
            if(s->right != NULL){
                s->right->parent = s->parent;
            }
            free(s);
            cout<<"Value "<<v<<" successfully deleted.\n";
            return 1;
        }
        else{
            s->parent->right = s->right;
            if(s->right != NULL){
                s->right->parent = s->parent;
            }
            free(s);
            cout<<"Value "<<v<<" successfully deleted.\n";
            return 1;
        }
    }
}

print_tree_inorder(struct node *n){
    if(n==NULL){
        cout<<"( ) ";
        return;
    }
    else{
        cout<<"( ";
        print_tree_inorder(n->left);
        cout<<n->val<<" ";
        print_tree_inorder(n->right);
        cout<<") ";
        return;
    }
}

print_tree_preorder(struct node *n){
    if(n==NULL){
        cout<<"( ) ";
        return;
    }
    else{
        cout<<"( ";
        cout<<n->val<<" ";
        print_tree_preorder(n->left);
        print_tree_preorder(n->right);
        cout<<") ";
        return;
    }
}

print_tree_postorder(struct node *n){
    if(n==NULL){
        cout<<"( ) ";
        return;
    }
    else{
        cout<<"( ";
        print_tree_postorder(n->left);
        print_tree_postorder(n->right);
        cout<<n->val<<" ";
        cout<<") ";
        return;
    }
}

void print_tree(struct tree *t, int mode){
    if(t==NULL){
        cout<<"Root node pointer is NULL.\n";
        return;
    }
    else{
        if(mode==1){
            print_tree_inorder(t->root);
            cout<<"\n";
            return;
        }
        else if(mode==2){
            print_tree_preorder(t->root);
            cout<<"\n";
            return;
        }
        else if(mode==3){
            print_tree_postorder(t->root);
            cout<<"\n";
            return;
        }
        else{
            cout<<"Invalid choice.\n";
            return;
        }
    }
}

int main(){
    struct tree *t;
    t = (struct tree *)malloc(sizeof(struct tree));
    int choice = 1;
    int val, success;
    struct node *n;
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
            success = delete_node(t, val);
        }
        else if(choice==4){
            cout<<"Modes of traversal:\n";
            cout<<"1. Inorder\n";
            cout<<"2. Preorder\n";
            cout<<"3. Postorder\n";
            cout<<"Enter choice: ";
            cin>>val;
            print_tree(t, val);
        }
        else if(choice!=5){
            cout<<"Invalid choice.\n";
        }

    }while(choice!=5);
    return 0;
}
