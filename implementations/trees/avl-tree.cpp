#include <iostream>
using namespace std;

template <typename T>
class Node{
    private:
        T x;
        Node<T> *left;
        Node<T> *right;
        int height;
    public:
        Node(T x_){
            x = x_;
            left = NULL;
            right = NULL;
            height = 1;
        }

        T get_x(){ return x; }
        Node<T> *get_left(){ return left; }
        Node<T> *get_right(){ return right; }
        int get_height(){ return height; }
        void set_x(T x_){ x=x_; }
        void set_left(Node<T> *left_){ left=left_; }
        void set_right(Node<T> *right_){ right=right_; }
        void set_height(int height_){ height=height_; }

        Node<T> *right_rotate(Node<T> *n){
            Node<T> *t1 = n->get_left();
            Node<T> *t2 = t1->get_right();
            t1->set_right(n);
            n->set_left(t2);
            int h1 = (n->get_left()==NULL ? 0 : n->get_left()->get_height());
            int h2 = (n->get_right()==NULL ? 0 : n->get_right()->get_height());
            n->set_height(1 + (h1 > h2 ? h1 : h2));
            int h3 = (t1->get_left()==NULL ? 0 : t1->get_left()->get_height());
            int h4 = (t1->get_right()==NULL ? 0 : t1->get_right()->get_height());
            t1->set_height(1 + (h3 > h4 ? h3 : h4));
            return t1;
        }

        Node<T> *left_rotate(Node <T> *n){
            Node<T> *t1 = n->get_right();
            Node<T> *t2 = t1->get_left();
            n->set_right(t2);
            t1->set_left(n);
            int h1 = (n->get_left()==NULL ? 0 : n->get_left()->get_height());
            int h2 = (n->get_right()==NULL ? 0 : n->get_right()->get_height());
            n->set_height(1 + (h1 > h2 ? h1 : h2));
            int h3 = (t1->get_left()==NULL ? 0 : t1->get_left()->get_height());
            int h4 = (t1->get_right()==NULL ? 0 : t1->get_right()->get_height());
            t1->set_height(1 + (h3 > h4 ? h3 : h4));
            return t1;
        }

        void print_tree(Node<T> *n){
            if(n==NULL) return;
            cout<<n->get_x()<<" ";
            print_tree(n->get_left());
            print_tree(n->get_right());
            return;
        }

        Node<T> *search(Node<T> *n, T val){
            if(n==NULL || val == n->get_x()) return n;
            if(val < n->get_x()) return search(n->get_left(), val);
            if(val > n->get_x()) return search(n->get_right(), val);
        }

        Node<T> *insert(Node<T> *n, T val){
            if(n==NULL) return (new Node(val));
            if(val < n->get_x()) n->set_left(insert(n->get_left(), val));
            else if(val > n->get_x()) n->set_right(insert(n->get_right(), val));
            else return n;

            int h1 = (n->get_left()==NULL ? 0 : n->get_left()->get_height());
            int h2 = (n->get_right()==NULL ? 0 : n->get_right()->get_height());
            n->set_height(1 + (h1 > h2 ? h1 : h2));
            int bal = h1-h2;
            if(bal > 1){
                if(val < n->get_left()->get_x()) return n->right_rotate(n);
                else{
                    n->set_left(n->left_rotate(n->get_left()));
                    return n->right_rotate(n);
                }
            }
            if(bal < -1){
                if(val > n->get_right()->get_x()) return n->left_rotate(n);
                else{
                    n->set_right(n->right_rotate(n->get_right()));
                    return n->left_rotate(n);
                }
            }

            return n;
        }

        Node<T> *delete_node(Node<T> *n, T val){
            if(n==NULL) return n;
            if(val < n->get_x()) n->set_left(delete_node(n->get_left(), val));
            else if(val > n->get_x()) n->set_right(delete_node(n->get_right(), val));
            else{
                if(n->get_left()==NULL || n->get_right()==NULL){
                    Node<T> *t;
                    if(n->get_left()==NULL && n->get_right()==NULL){
                        t = n;
                        n = NULL;
                    }
                    else{
                        if(n->get_left()==NULL) t = n->get_right();
                        else t = n->get_left();
                        *n = *t;
                    }
                    free(t);
                }
                else{
                    Node<T> *t;
                    t = n->get_right();
                    while(t->get_left()!=NULL) t = t->get_left();
                    n->set_x(t->get_x());
                    n->set_right(delete_node(n->get_right(), t->get_x()));
                }
            }

            if(n==NULL) return n;
            int h1 = (n->get_left()==NULL ? 0 : n->get_left()->get_height());
            int h2 = (n->get_right()==NULL ? 0 : n->get_right()->get_height());
            n->set_height(1 + (h1 > h2 ? h1 : h2));
            int bal = h1-h2;

            if(bal > 1){
                int h3 = (n->get_left()->get_left()==NULL ? 0 : n->get_left()->get_left()->get_height());
                int h4 = (n->get_left()->get_right()==NULL ? 0 : n->get_left()->get_right()->get_height());
                if(h3-h4 >= 0) return n->right_rotate(n);
                else{
                    n->set_left(left_rotate(n->get_left()));
                    return right_rotate(n);
                }
            }
            if(bal < -1){
                int h5 = (n->get_right()->get_left()==NULL ? 0 : n->get_right()->get_left()->get_height());
                int h6 = (n->get_right()->get_right()==NULL ? 0 : n->get_right()->get_right()->get_height());
                if(h5-h6 <= 0) return n->left_rotate(n);
                else{
                    n->set_right(right_rotate(n->get_right()));
                    return left_rotate(n);
                }
            }
            return n;
        }
};

int main(){
    Node<int> *root = NULL;
    root = root->insert(root, 4);
    root = root->insert(root, 5);
    root = root->insert(root, 3);
    root = root->insert(root, 6);
    root = root->insert(root, 7);
    root = root->delete_node(root, 3);
    root->print_tree(root);

}
