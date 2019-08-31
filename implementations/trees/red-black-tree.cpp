#include <iostream>
using namespace std;

template <typename T>
class Node{
    private:
        T x;
        Node<T> *left;
        Node<T> *right;
        Node<T> *parent;
        int colour;
    public:
        Node(){
            left = NULL;
            right = NULL;
            parent = NULL;
            colour = 0;
        }

        void set_x(T x_){ x = x_; };
        void set_left(Node<T> *left_){ left = left_; };
        void set_right(Node<T> *right_){ right = right_; };
        void set_parent(Node<T> *parent_){ parent = parent_; };
        void set_colour(int colour_){ colour = colour_; };
        T get_x(){ return x; };
        Node<T> *get_left(){ return left; };
        Node<T> *get_right(){ return right; };
        Node<T> *get_parent(){ return parent; };
        int get_colour(){ return colour; };

        Node<T> *search(T val, Node<T> *n){
            if(n==NULL || val == n->get_x()) return n;
            if(val < n->get_x()) return search(val, n->get_left());
            else return search(val, n->get_right());
        }

        Node<T> *restructure(Node<T> *child, Node<T> *parent, Node<T> *grandparent, Node<T> *toplink){
            Node<T> *a, *b, *c, *t1, *t2;
            if(child->get_x() < parent->get_x() && child->get_x() < grandparent->get_x()){
                a = child;
                b = parent;
                c = grandparent;
                t1 = a->get_right();
                t2 = b->get_right();

            }
            else if(parent->get_x() < grandparent->get_x() && parent->get_x() < child->get_x()){
                a = parent;
                b = child;
                c = grandparent;
                t1 = b->get_left();
                t2 = b->get_right();

            }
            else{
                a = grandparent;
                if(child->get_x() < parent->get_x()){
                    b = child;
                    c = parent;
                    t1 = b->get_left();
                    t2 = b->get_right();
                }
                else{
                    c = child;
                    b = parent;
                    t1 = b->get_left();
                    t2 = c->get_left();
                }
            }

            a->set_colour(1);
            b->set_colour(0);
            c->set_colour(0);
            a->set_right(t1);
            c->set_left(t2);
            if(t1!=NULL) t1->set_parent(a);
            if(t2!=NULL) t2->set_parent(c);
            a->set_parent(b);
            c->set_parent(b);
            b->set_left(a);
            b->set_right(c);
            b->set_parent(toplink);
            return b;
        }

        Node<T> *insert(T val, Node<T> *root){
            if(root==NULL){
                Node<T> *n = new Node();
                n->set_x(val);
                root = n;
                root->set_colour(1);
                return root;
            }

            Node *n = root;
            while(1){
                if(val < n->get_x()){
                    if(n->get_left()==NULL){
                        Node<T> *m = new Node();
                        m->set_x(val);
                        m->set_parent(n);
                        n->set_left(m);
                        break;
                    }
                    else n = n->get_left();
                }

                else if(val > n->get_x()){
                    if(n->get_right()==NULL){
                        Node<T> *m = new Node();
                        m->set_x(val);
                        m->set_parent(n);
                        n->set_right(m);
                        break;
                    }
                    else n = n->get_right();
                }

                else return root;

            }

            Node<T> *child = (val < n->get_x()) ? n->get_left() : n->get_right();

            while(1){
                if(child==root){
                    child->set_colour(1);
                    return root;
                }
                Node<T> *parent = child->get_parent();
                if(parent->get_colour()==1) return root;
                Node<T> *grandparent = parent->get_parent();
                Node<T> *uncle = (grandparent->get_left()==parent) ? grandparent->get_right() : grandparent->get_left();
                int uncle_colour = (uncle==NULL) ? 1 : uncle->get_colour();
                if(uncle_colour == 1){
                    Node<T> *subroot = child->restructure(child, parent, grandparent, grandparent->get_parent());
                    subroot->set_colour(1);
                    subroot->get_left()->set_colour(0);
                    subroot->get_right()->set_colour(0);
                    if(subroot->parent==NULL){
                        root = subroot;
                    }
                    else{
                        if(subroot->get_x() > subroot->get_parent()->get_x()) subroot->get_parent()->set_right(subroot);
                        else subroot->get_parent()->set_left(subroot);
                    }
                    return root;
                }
                else{
                    parent->set_colour(1);
                    uncle->set_colour(1);
                    grandparent->set_colour(0);
                    child = grandparent;
                }

            }
        }

        Node<T> *delete_node(T val, Node<T> *root){

            Node<T> *v = root->search(val, root);
            if(v==NULL) return root;
            if(v==root && v->get_left()==NULL && v->get_right()==NULL){
                root=NULL;
                free(v);
                return root;
            }
            if(v->get_left()!=NULL && v->get_right()!=NULL){
                Node<T> *replacement = v->get_right();
                while(replacement->get_left() != NULL) replacement = replacement->get_left();
                v->set_x(replacement->get_x());
                v = replacement;
            }
            Node<T> *u;
            if(v->get_left()==NULL && v->get_right()==NULL) u=NULL;
            else u = (v->get_left()==NULL) ? v->get_right() : v->get_left();
            int v_colour = v->get_colour();
            int u_colour = (u==NULL) ? 1 : 0;
            if(v_colour*u_colour == 0){
                if(u!=NULL){
                    u->set_parent(v->get_parent());
                    u->set_colour(1);
                }
                if(v!=root){
                    if(v->get_parent()->get_left() == v) v->get_parent()->set_left(u);
                    else v->get_parent()->set_right(u);
                }
                else{
                    root = u;
                    if(v->get_right()==u){
                        u->set_left(v->get_left());
                        if(v->get_left()!=NULL) v->get_left()->set_parent(u);
                    }
                    else{
                        u->set_right(v->get_right());
                        if(v->get_right()!=NULL) v->get_right()->set_parent(u);
                    }
                }
                free(v);
                return root;
            }
            if(u!=NULL){
                u->set_parent(v->get_parent());
                u->set_colour(1);
            }
            if(v!=root){
                if(v->get_parent()->get_left() == v) v->get_parent()->set_left(u);
                else v->get_parent()->set_right(u);
            }

            Node<T> *p = v->get_parent();
            free(v);

            while(u!=root){
                Node<T> *s;
                s = (p->get_left()==u) ? p->get_right() : p->get_left();
                int s_colour = (s==NULL) ? 1 : s->get_colour();
                if(s_colour==1){
                    Node<T> *s_right = (s==NULL) ? NULL : s->get_right();
                    Node<T> *s_left = (s==NULL) ? NULL : s->get_left();
                    int s_right_colour = (s_right == NULL) ? 1 : s_right->get_colour();
                    int s_left_colour = (s_left == NULL) ? 1 : s_left->get_colour();
                    if(s_right_colour * s_left_colour == 0){
                        Node<T> *r;
                        r = (s_right_colour==0) ? s_right : s_left;
                        int p_colour = p->get_colour();
                        Node<T> *subroot = r->restructure(r, s, p, p->get_parent());
                        subroot->set_colour(p_colour);
                        subroot->get_left()->set_colour(1);
                        subroot->get_right()->set_colour(1);

                        if(subroot->parent==NULL){
                            root = subroot;
                        }
                        else{
                            if(subroot->get_x() > subroot->get_parent()->get_x()) subroot->get_parent()->set_right(subroot);
                            else subroot->get_parent()->set_left(subroot);
                        }

                        return root;

                    }

                    else{
                        s->set_colour(0);
                        if(p->get_colour()==0){
                            p->set_colour(1);
                            return root;
                        }
                        Node<T> *temp = u->get_parent();
                        u = p;
                        p = temp;
                        return root;
                    }
                }
                else{
                    Node *z;
                    if(p->get_left()==s) z=s->get_left();
                    else z=s->get_right();
                    Node<T> *subroot = z->restructure(z, s, p, p->get_parent());
                    subroot->set_colour(1);
                    subroot->get_left()->set_colour(0);
                    subroot->get_right()->set_colour(1);
                    if(subroot->parent==NULL){
                        root = subroot;
                    }
                    else{
                        if(subroot->get_x() > subroot->get_parent()->get_x()) subroot->get_parent()->set_right(subroot);
                        else subroot->get_parent()->set_left(subroot);
                    }
                }

            }

            if(u==root){
                u->set_colour(1);
                return u;
            }
            return root;

        }

        void print_inorder(Node<T> *n){
            if(n==NULL) return;
            char c = (n->get_colour()) ? 'B' : 'R';
            cout<<n->get_x()<<c<<" ";
            print_inorder(n->get_left());
            print_inorder(n->get_right());
            return;
        }
};

int main(){
    Node<int> *root = NULL;
    root = root->insert(12, root);
    root = root->insert(15, root);
    root = root->insert(3, root);
    root = root->insert(18, root);
    root = root->insert(16, root);
    root = root->insert(17, root);
    root = root->delete_node(3, root);
    root = root->delete_node(12, root);
    root = root->delete_node(17, root);
    root->print_inorder(root);
}
