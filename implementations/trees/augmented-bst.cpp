#include <iostream>
using namespace std;

struct node{
    int val;
    struct node *left;
    struct node *right;
    struct node *parent;
    int nleft;
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
    cout<<"Inserting "<<v<<" in the tree.\n";
    struct node *p;
    p = t->root;
    if(p==NULL){
        struct node *n;
        n = (struct node *)malloc(sizeof(struct node));
        n->val = v;
        n->left = NULL;
        n->right = NULL;
        n->parent = NULL;
        n->nleft = 0;
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
                n->nleft = 0;
                p->left = n;
                p->nleft += 1;
                cout<<"Value "<<v<<" successfully inserted.\n";
                return 1;
            }
            else{
                p->nleft += 1;
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
                n->nleft = 0;
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

int ksmallest(struct node *n, int k){
    if(n->nleft == k-1){
        return n->val;
    }
    else if(n->nleft > k-1){
        return ksmallest(n->left, k);
    }
    else{
        return ksmallest(n->right, k-(n->nleft)-1);
    }
}

int find_ksmallest(struct tree *t, int k){
    if(t==NULL){
        cout<<"Root node pointer is NULL.\n";
        return 0;
    }
    else{
        return ksmallest(t->root, k);
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
            struct node *curr = p;
            while(curr->parent!=NULL){
                if(curr->parent->left == curr){
                    curr->parent->nleft -=1;
                }
                curr = curr->parent;
            }
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
        struct node *curr = s;
        while(curr->parent!=NULL){
            if(curr->parent->left == curr){
                curr->parent->nleft -=1;
            }
            curr = curr->parent;
        }
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

int main(){
    struct tree *t;
    t = (struct tree *)malloc(sizeof(struct tree));
    int choice = 1;
    int number_of_nodes = 0;
    int val, success;
    struct node *n;
    cout<<"Available choices:\n";
    cout<<"1. Insert node\n";
    cout<<"2. Search for node\n";
    cout<<"3. Delete node\n";
    cout<<"4. Find k-smallest value\n";
    cout<<"5. Exit\n";
    do{
        cout<<"Enter choice: ";
        cin>>choice;
        if(choice==1){
            cout<<"Enter value to be inserted: ";
            cin>>val;
            success = insert(t, val);
            if(success){
                number_of_nodes += 1;
            }
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
            if(success){
                number_of_nodes -= 1;
            }
        }
        else if(choice==4){
            cout<<"Enter k: ";
            cin>>val;
            if(val > number_of_nodes){
                cout<<"Tree contains less than "<<val<<" nodes.\n";
                continue;
            }
            int kth = find_ksmallest(t, val);
            if(kth){
                cout<<"k-th smallest value = "<<kth<<"\n";
            }
        }

    }while(choice!=5);
    return 0;
}
