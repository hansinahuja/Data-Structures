// THIS CODE ONLY WORKS FOR VALID INPUTS //

#include <iostream>
using namespace std;

template <typename T>
class Node{
    private:
        T key;          //The value by which the tree is constructed
        int reg;        //Car registration number
        double x0;      //Position of car at t = 0
        int d;          //Direction in which the car is moving
        Node *left;     //Pointer to left child
        Node *right;    //Pointer to right child
        Node *parent;   //Pointer to parent node
        int height;     //Height of subtree
        int size;       //Size of subtree

    public:

        //Constructor
        Node(int reg_, double x, double t, int d_, int tree_type){
            reg = reg_;
            x0 = x;
            if(d_) x0 = (double)(x0 - t);
            else x0 = (double)(x0 + t);
            d = d_;
            if(tree_type == 1) key = reg;
            else key = x0;
            height = 1;
            left = NULL;
            right = NULL;
            size = 1;
        }

        //Getter functions
        T get_key(){ return key; }
        Node<T> *get_left(){ return left; }
        Node<T> *get_right(){ return right; }
        Node<T> *get_parent(){ return parent; }
        int get_height(){ return height; }
        int get_reg(){ return reg; }
        int get_d(){ return d; }
        double get_x0(){ return x0; }
        int get_size(){ return size; }

        //Setter functions
        void set_key(T key_){ key=key_; }
        void set_size(int size_){ size=size_; }
        void set_reg(int reg_){ reg=reg_; }
        void set_d(int d_){ d=d_; }
        void set_x0(double x0_){ x0=x0_; }
        void set_left(Node<T> *left_){ left=left_; }
        void set_right(Node<T> *right_){ right=right_; }
        void set_parent(Node<T> *parent_){ parent=parent_; }
        void set_height(int height_){ height=height_; }

        //Update height of Node object
        void update_node_height(){
            int l, r, m;
            l = (left==NULL) ? 0 : left->get_height();
            r = (right==NULL) ? 0 : right->get_height();
            m = (l > r) ? l : r;
            height = m+1;
            return;
        }

        //Update size of Node object
        void update_node_size(){
            int l, r;
            l = (left==NULL) ? 0 : left->get_size();
            r = (right==NULL) ? 0 : right->get_size();
            size = l + r + 1;
            return;
        }

        //Get difference between heights of left child and right child of current node
        int get_balance_factor(){
            int l = (left==NULL) ? 0 : left->get_height();
            int r = (right==NULL) ? 0 : right->get_height();
            int balance_factor = l-r;
            return balance_factor;
        }
};

template <typename T>
class Tree{
    private:
        Node<T> *root;      //Pointer to root of tree object

    public:

        //Constructor
        Tree(){
            root = NULL;
        }

        //Getter and setter functions
        Node<T> *get_root(){ return root; }
        void set_root(Node<T> *n){ root = n; }

        //Search for val in tree
        Node<T> *search(T val){
            if(root==NULL) return NULL;
            Node<T> *n = root;
            while(n!=NULL){
                if(val < n->get_key()) n = n->get_left();
                else if(val > n->get_key()) n = n->get_right();
                else return n;
            }
            return NULL;
        }

        //Update node heights from Node p upwards to the root
        void update_heights(Node<T> *p){
            while(p != root){
                p->update_node_height();
                p = p->get_parent();
            }
            p->update_node_height();
            return;
        }

        //Update node sizes from Node p upwards to the root
        void update_sizes(Node<T> *p){
            while(p != root){
                p->update_node_size();
                p = p->get_parent();
            }
            p->update_node_size();
            return;
        }

        //Perform restructuring of Node z after inserting some value in the tree
        void restructure(Node<T> *z){
            int l, r;
            Node<T> *y, *x, *a, *b, *c, *t1, *t2, *par;
            int pos = -1;
            par = z->get_parent();
            if(z != root){
                if(z->get_parent()->get_left() == z) pos = 0;
                else pos = 1;
            }
            l = (z->get_left()==NULL) ? 0 : z->get_left()->get_height();
            r = (z->get_right()==NULL) ? 0 : z->get_right()->get_height();
            y = (l > r) ? z->get_left() : z->get_right();
            l = (y->get_left()==NULL) ? 0 : y->get_left()->get_height();
            r = (y->get_right()==NULL) ? 0 : y->get_right()->get_height();
            x = (l > r) ? y->get_left() : y->get_right();

            if(z->get_key() < y->get_key() && z->get_key() < x->get_key()){
                if(y->get_key() < x->get_key()){
                    a = z;
                    b = y;
                    c = x;
                    t1 = b->get_left();
                    t2 = c->get_left();
                }
                else{
                    a = z;
                    b = x;
                    c = y;
                    t1 = b->get_left();
                    t2 = b->get_right();
                }
            }

            else if(y->get_key() < z->get_key() && y->get_key() < x->get_key()){
                a = y;
                b = x;
                c = z;
                t1 = b->get_left();
                t2 = b->get_right();
            }

            else{
                a = x;
                b = y;
                c = z;
                t1 = a->get_right();
                t2 = b->get_right();
            }

            b->set_left(a);
            b->set_right(c);
            b->set_parent(par);
            a->set_right(t1);
            a->set_parent(b);
            if(t1 != NULL) t1->set_parent(a);
            c->set_left(t2);
            c->set_parent(b);
            if(t2 != NULL) t2->set_parent(c);

            a->update_node_height();
            c->update_node_height();
            b->update_node_height();
            a->update_node_size();
            c->update_node_size();
            b->update_node_size();

            if(pos == -1) root = b;
            else{
                if(pos==0) par->set_left(b);
                else par->set_right(b);
                par->update_node_height();
                par->update_node_size();
            }

            return;
        }

        //Perform restructuring of Node z after deleting some value from the tree
        Node<T> *restructure2(Node<T> *z){
            int l, r;
            Node<T> *y, *x, *a, *b, *c, *t1, *t2, *par;
            int pos = -1;
            par = z->get_parent();
            if(z != root){
                if(z->get_parent()->get_left() == z) pos = 0;
                else pos = 1;
            }
            l = (z->get_left()==NULL) ? 0 : z->get_left()->get_height();
            r = (z->get_right()==NULL) ? 0 : z->get_right()->get_height();
            y = (l > r) ? z->get_left() : z->get_right();
            l = (y->get_left()==NULL) ? 0 : y->get_left()->get_height();
            r = (y->get_right()==NULL) ? 0 : y->get_right()->get_height();
            if(l==r){
                if(z->get_left()==y) x = y->get_left();
                else x = y->get_right();
            }
            else{
                x = (l > r) ? y->get_left() : y->get_right();
            }

            if(z->get_key() < y->get_key() && z->get_key() < x->get_key()){
                if(y->get_key() < x->get_key()){
                    a = z;
                    b = y;
                    c = x;
                    t1 = b->get_left();
                    t2 = c->get_left();
                }
                else{
                    a = z;
                    b = x;
                    c = y;
                    t1 = b->get_left();
                    t2 = b->get_right();
                }
            }

            else if(y->get_key() < z->get_key() && y->get_key() < x->get_key()){
                a = y;
                b = x;
                c = z;
                t1 = b->get_left();
                t2 = b->get_right();
            }

            else{
                a = x;
                b = y;
                c = z;
                t1 = a->get_right();
                t2 = b->get_right();
            }

            b->set_left(a);
            b->set_right(c);
            b->set_parent(par);
            a->set_right(t1);
            a->set_parent(b);
            if(t1 != NULL) t1->set_parent(a);
            c->set_left(t2);
            c->set_parent(b);
            if(t2 != NULL) t2->set_parent(c);

            a->update_node_height();
            c->update_node_height();
            b->update_node_height();
            a->update_node_size();
            c->update_node_size();
            b->update_node_size();

            if(pos == -1) root = b;
            else{
                if(pos==0) par->set_left(b);
                else par->set_right(b);
                par->update_node_height();
                par->update_node_size();
            }

            return b;

        }

        //Insert Node n in the tree
        int insert(Node<T> *n, T val){
            if(root==NULL){
                n->set_parent(NULL);
                root = n;
                return 1;
            }
            Node<T> *p = root;
            while(1){
                if(val < p->get_key()){
                    if(p->get_left()==NULL){
                        n->set_parent(p);
                        p->set_left(n);
                        break;
                    }
                    else{
                        p = p->get_left();
                    }
                }
                else{
                    if(p->get_right()==NULL){
                        n->set_parent(p);
                        p->set_right(n);
                        break;
                    }
                    else{
                        p = p->get_right();
                    }
                }
            }

            update_heights(p);
            update_sizes(p);
            while(p != root){
                int balance_factor = p->get_balance_factor();
                if(balance_factor <= 1 && balance_factor >= -1){
                    p = p->get_parent();
                }
                else{
                    restructure(p);
                    return 1;
                }
            }
            int balance_factor = p->get_balance_factor();
            if(balance_factor < -1 || balance_factor > 1){
                restructure(p);
            }
            return 1;
        }

        //Delete Node p from the tree
        int remove(Node<T> *p){
            Node<T> *s;
            if(p->get_right()==NULL){
                if(p == root){


                    root = p->get_left();
                    if(p->get_left()!=NULL) p->get_left()->set_parent(NULL);
                    s = p->get_parent();
                    free(p);
                }
                else{
                    if(p->get_parent()->get_right() == p){
                        p->get_parent()->set_right(p->get_left());
                        if(p->get_left()!=NULL) p->get_left()->set_parent(p->get_parent());
                        s = p->get_parent();
                        free(p);
                    }
                    else{
                        p->get_parent()->set_left(p->get_left());
                        if(p->get_left()!=NULL) p->get_left()->set_parent(p->get_parent());
                        s = p->get_parent();
                        free(p);
                    }
                }
            }
            else{
                Node<T> *rem = p->get_right();
                while(rem->get_left() != NULL) rem = rem->get_left();
                p->set_key(rem->get_key());
                p->set_reg(rem->get_reg());
                p->set_x0(rem->get_x0());
                p->set_d(rem->get_d());
                if(rem->get_parent()->get_left() == rem){
                    rem->get_parent()->set_left(rem->get_right());
                    if(rem->get_right() != NULL) rem->get_right()->set_parent(rem->get_parent());
                    s = rem->get_parent();
                    free(rem);
                }
                else{
                    rem->get_parent()->set_right(rem->get_right());
                    if(rem->get_right() != NULL) rem->get_right()->set_parent(rem->get_parent());
                    s = rem->get_parent();
                    free(rem);
                }

            }
            if(s==NULL) return 1;
            update_heights(s);
            update_sizes(s);
            while(s != root){
                int balance_factor = s->get_balance_factor();
                if(balance_factor <= 1 && balance_factor >= -1){
                    s = s->get_parent();
                }
                else{
                    s = restructure2(s);
                    s = s->get_parent();
                }
            }

            int balance_factor = s->get_balance_factor();
            if(balance_factor < -1 || balance_factor > 1){
                restructure2(s);
            }

            return 1;
        }

        //Get greatest key less than x in the tree (keys shifted by a factor of t)
        Node<T> *get_max_less_than_x(double x, double f, double t){
            Node<T> *c = root;
            Node<T> *m = NULL;
            while(c!=NULL){
                double curr_x = c->get_x0() + (f * t);
                if(curr_x < x){
                    m = c;
                    c = c->get_right();
                }
                else c = c->get_left();
            }
            return m;

        }

        //Get minimum key greater than x in the tree (keys shifted by a factor of t)
        Node<T> *get_min_greater_than_x(double x, double f, double t){
            Node<T> *c = root;
            Node<T> *m = NULL;
            while(c!=NULL){
                double curr_x = c->get_x0() + (f * t);
                if(curr_x > x){
                    m = c;
                    c = c->get_left();
                }
                else{
                    c = c->get_right();
                }
            }
            return m;
        }

        //Count number of keys lesser than pos in the tree
        int count_tree_left(double pos, double f, double t){
            Node<T> *p = root;
            if(root==NULL) return 0;
            int count = 0;
            while(p!=NULL){
                double curr_x = p->get_x0() + (f * t);
                if(curr_x < pos){
                    count += 1;
                    if(p->get_left()!=NULL) count += p->get_left()->get_size();
                    p = p->get_right();
                }
                else if(curr_x > pos){
                    p = p->get_left();
                }
                else{
                    if(p->get_left()!=NULL) count += p->get_left()->get_size();
                    return count;
                }
            }
            return count;
        }

        //Count number of keys greater than pos in the tree
        int count_tree_right(double pos, double f, double t){
            Node<T> *p = root;
            if(root==NULL) return 0;
            int count = 0;
            while(p!=NULL){
                double curr_x = p->get_x0() + (f * t);
                if(curr_x > pos){
                    count += 1;
                    if(p->get_right() != NULL) count += p->get_right()->get_size();
                    p = p->get_left();
                }
                else if(curr_x < pos){
                    p = p->get_right();
                }
                else{
                    if(p->get_right() != NULL) count += p->get_right()->get_size();
                    return count;
                }
            }
            return count;
        }
};

class Highway{
    private:
        Tree<int> reg;           //Tree constructed on the basis of registration numbers
        Tree<double> dleft;      //Cars in the left-moving lane, constructed on the basis of x0
        Tree<double> dright;     //Cars in the right-moving lane, constructed on the basis of x0
        double curr;             //Current time

    public:

        //Constructor
        Highway(){
            curr = 0;
        }

        //Insert a car in the highway
        int insert(int r, double x, double t, int d){
            Node<int> *n = reg.search(r);
            if(n != NULL) return 0;
            if(d){
                Node<double> *m = dright.search(x-t);
                if(m != NULL){
                    // cout<<"Car with the same x-coordinate already exists in the same lane!"<<endl;
                    return 0;
                }
            }
            else{
                Node<double> *m = dleft.search(x+t);
                if(m != NULL){
                    // cout<<"Car with the same x-coordinate already exists in the same lane!"<<endl;
                    return 0;
                }
            }
            Node<int> *t1 = new Node<int>(r, x, t, d, 1);
            Node<double> *t2 = new Node<double>(r, x, t, d, 2);
            reg.insert(t1, r);
            if(d) dright.insert(t2, x - t);
            else dleft.insert(t2, x + t);
            curr = t;
            return 1;
        }

        //Delete a car from the highway
        int remove(int r, double t){
            Node<int> *n = reg.search(r);
            if(n==NULL) return 0;
            double pos = n->get_x0();
            int dir = n->get_d();
            reg.remove(n);
            Node<double> *m;
            if(dir){
                m = dright.search(pos);
                dright.remove(m);
            }
            else{
                m = dleft.search(pos);
                dleft.remove(m);
            }
            curr = t;
            return 1;
        }

        //Get registration number of the car to the immediate left of car with registration number r
        int find_immediate_left(int r, double t){
            Node<int> *car = reg.search(r);
            double f = (car->get_d() == 1) ? 1 : -1;
            double pos = car->get_x0() + (f * t);
            Node<double> *m = dleft.get_max_less_than_x(pos, -1.0, t);
            Node<double> *n = dright.get_max_less_than_x(pos, 1.0, t);
            if(m==NULL || n==NULL){
                if(m==NULL && n==NULL) return -1;
                if(m==NULL) return n->get_reg();
                else return m->get_reg();
            }
            double x1 = m->get_x0() + (-1.0 * t);
            double x2 = n->get_x0() + (1.0 * t);
            if(pos - x1 < pos - x2) return m->get_reg();
            else if(pos - x1 > pos - x2) return n->get_reg();
            else{
                int smaller_reg = (m->get_reg() < n->get_reg()) ? m->get_reg() : n->get_reg();
                int larger_reg = (m->get_reg() > n->get_reg()) ? m->get_reg() : n->get_reg();
                cout<<smaller_reg<<" ";
                return larger_reg;
            }
        }

        //Get registration number of the car to the immediate right of car with registration number r
        int find_immediate_right(int r, double t){
            Node<int> *car = reg.search(r);
            double f = (car->get_d() == 1) ? 1 : -1;
            double pos = car->get_x0() + (f * t);
            Node<double> *m = dleft.get_min_greater_than_x(pos, -1.0, t);
            Node<double> *n = dright.get_min_greater_than_x(pos, 1.0, t);
            if(m==NULL || n==NULL){
                if(m==NULL && n==NULL) return -1;
                if(m==NULL) return n->get_reg();
                else return m->get_reg();
            }
            double x1 = m->get_x0() + (-1.0 * t);
            double x2 = n->get_x0() + (1.0 * t);
            if(x1 - pos < x2 - pos) return m->get_reg();
            else if(x1 - pos > x2 - pos) return n->get_reg();
            else{
                int smaller_reg = (m->get_reg() < n->get_reg()) ? m->get_reg() : n->get_reg();
                int larger_reg = (m->get_reg() > n->get_reg()) ? m->get_reg() : n->get_reg();
                cout<<smaller_reg<<" ";
                return larger_reg;
            }
        }

        //Count number of cars to the left of car with registration number r
        int count_left(int r, double t){
            Node<int> *car = reg.search(r);
            if(car==NULL) return -1;
            double pos, dir;
            if(car->get_d()) dir = 1;
            else dir = -1;
            pos = car->get_x0() + (dir * t);
            int m = dleft.count_tree_left(pos, -1.0, t);
            int n = dright.count_tree_left(pos, 1.0, t);
            int ans = m + n;
            return ans;
        }

        //Count number of cars to the right of car with registration number r
        int count_right(int r, double t){
            Node<int> *car = reg.search(r);
            if(car==NULL) return -1;
            double pos, dir;
            if(car->get_d()) dir  = 1;
            else dir = -1;
            pos = car->get_x0() + (dir * t);
            int m = dleft.count_tree_right(pos, -1.0, t);
            int n = dright.count_tree_right(pos, 1.0, t);
            int ans = m + n;
            return ans;
        }

        //Count number of crossings of car with registration number r, from time = curr to time = t
        int number_of_crossings(int r, double t){
            Node<int> *car = reg.search(r);
            if(car == NULL) return -1;
            int ans;
            if(car->get_d()){
                int before = count_left(r, curr);
                int after = count_left(r, t);
                ans = after - before;
                int total_mismatch = before + count_right(r, curr);
                int total_cars = reg.get_root()->get_size();
                if(total_mismatch == total_cars - 2) ans = ans - 1;
                if(ans < 0) ans = 0;
            }
            else{
                int before = count_right(r, curr);
                int after = count_right(r, t);
                ans = after - before;
                int total_mismatch = before + count_left(r, curr);
                int total_cars = reg.get_root()->get_size();
                if(total_mismatch == total_cars - 2) ans = ans - 1;
                if(ans < 0) ans = 0;

            }
            return ans;
        }
};

int main(){
    Highway h;
    int n;
    cin>>n;
    while(n--){
        int r, type;
        double t;
        cin>>type;
        if(type==1){
            int d;
            double x;
            cin>>r>>x>>t>>d;
            h.insert(r, x, t, d);
        }
        else if(type==2){
            cin>>r>>t;
            h.remove(r, t);
        }
        else if(type==3){
            cin>>r>>t;
            cout<<h.find_immediate_left(r, t)<<endl;
        }
        else if(type==4){
            cin>>r>>t;
            cout<<h.find_immediate_right(r, t)<<endl;
        }
        else if(type==5){
            cin>>r>>t;
            cout<<h.count_left(r, t)<<endl;
        }
        else if(type==6){
            cin>>r>>t;
            cout<<h.count_right(r, t)<<endl;
        }
        else if(type==7){
            cin>>r>>t;
            cout<<h.number_of_crossings(r, t)<<endl;
        }
    }
}
