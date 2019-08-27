#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
class Node{

    private:
        T x;
        Node<T> *left;
        Node<T> *right;
        Node<T> *parent;
        int nleft;

    public:
        Node(){
            left = NULL;
            right = NULL;
            parent = NULL;
            nleft = 0;
        };

        Node(T v){
            x = v;
        };

        ~Node(){
        };

        T getx() { return x; }
        Node<T> *getleft() { return left; }
        Node<T> *getright() { return right; }
        Node<T> *getparent() { return parent; }
        int getnleft() { return nleft; }
        void setx(int x_) { x = x_; }
        void setleft(Node<T> *left_) { left = left_; }
        void setright(Node<T> *right_) { right = right_; }
        void setparent(Node<T> *parent_) { parent = parent_; }
        void setnleft(int nleft_) { nleft = nleft_; }

        void print_node(Node<T> *n){
            if(n==NULL){
                cout<<"( ) ";
                return;
            }
            cout<<"( ";
            print_node(n->getleft());
            cout<<n->getx()<<" ";
            print_node(n->getright());
            cout<<") ";
            return;
        };

        T ksmallest(Node<T> *n, int k){
            if(n->getnleft() == k-1) return n->getx();
            else if(n->getnleft() > k-1) return ksmallest(n->getleft(), k);
            else return ksmallest(n->getright(), k-1-(n->getnleft()));
        };

        int find_height(Node<T> *n){
            if(n==NULL) return 0;
            int height_left = 1 + find_height(n->left);
            int height_right = 1 + find_height(n->right);
            return ((height_left>height_right) ? height_left : height_right);
        }


};

template <typename T>
class Tree{

    private:
        Node<T> *root;
        int n;

    public:
        Tree(){
            root = NULL;
            n = 0;
        };

        ~Tree(){
        };

        int search(T val){
            Node<T> *p;
            p = root;
            while(p!=NULL){
                if(p->getx() == val){
                    // cout<<val<<" found in the tree.\n";
                    return 1;
                }
                else if(p->getx() > val) p = p->getleft();
                else p = p->getright();
            }
            // cout<<val<<" not found.\n";
            return 0;
        };

        int insert(T val){
            if(search(val)){
                // cout<<val<<" already exists in the tree.\n";
                return 0;
            }
            Node<T> *p = root;
            n++;
            if(n==1){
                Node<T> *n = new Node<T>();
                n->setx(val);
                root = n;
                // cout<<val<<" inserted.\n";
                return 1;
            }
            while(1){
                if(p->getx() > val){
                    p->setnleft(p->getnleft()+1);
                    if(p->getleft() == NULL){
                        Node<T> *n = new Node<T>();
                        n->setx(val);
                        n->setparent(p);
                        p->setleft(n);
                        // cout<<val<<" inserted.\n";
                        return 1;
                    }
                    else{
                        p = p->getleft();
                    }
                }
                else{
                    if(p->getright()==NULL){
                        Node<T> *n = new Node<T>();
                        n->setx(val);
                        n->setparent(p);
                        p->setright(n);
                        // cout<<val<<" inserted.\n";
                        return 1;
                    }
                    else{
                        p = p->getright();
                    }
                }
            }
        };

        int remove(T val){
            if(!search(val)) return 0;
            n--;
            Node<T> *p = root;
            while(1){
                if(p->getx() == val) break;
                else if(p->getx() > val){
                    p->setnleft(p->getnleft()-1);
                    p = p->getleft();
                }
                else p = p->getright();
            }
            if(p->getright() == NULL){
                if(p==root) root = p->getleft();
                else{
                    if(p->getparent()->getleft()==p) p->getparent()->setleft(p->getleft());
                    else p->getparent()->setright(p->getleft());
                }
                if(p->getleft()!=NULL) p->getleft()->setparent(p->getparent());
                delete p;
                cout<<val<<" deleted.\n";
                return 1;
            }
            else{
                Node<T> *s = p->getright();
                while(s->getleft() != NULL){
                    s->setnleft(s->getnleft()-1);
                    s = s->getleft();
                }
                p->setx(s->getx());
                if(s->getright()!=NULL) s->getright()->setparent(s->getparent());
                if(s->getparent()->getleft()==s) s->getparent()->setleft(s->getright());
                else s->getparent()->setright(s->getright());
                delete s;
                cout<<val<<" deleted.\n";
                return 1;
            }
        };

        void print_tree(){
            root->print_node(root);
            cout<<"\n";
        };

        T order_statistics(int k){
            if(k > n){
                cout<<"Tree has less than "<<k<<" elements.\n";
                return 0;
            }
            return root->ksmallest(root, k);
        };

        int get_height(){
            return root->find_height(root);
        };
};

int main(){
    int x[16];
    double h[16];
    int k=10000, j=0;
    cout<<"no. of nodes | avg. tree height\n";
    for(int n=2; n<=16; n=n*2){
        long long int height_sum = 0;
        for(int rep=1; rep<=k; rep++){
            Tree<int> *t = new Tree<int>();
            int a[n];
            for(int i=0; i<n; i++) a[i]=i+1;
            int range = n;
            int last = n-1;
            while(last!=1){
                double r = ((double) rand() / (RAND_MAX));
                r = r*range;
                int pred = floor(r);
                int temp = a[pred];
                a[pred] = a[last];
                a[last] = temp;
                last--;
                range--;
            }
            for(int i=n-1; i>=0; i--) t->insert(a[i]);
            height_sum += t->get_height();
        }
        x[j] = n;
        h[j] = (1.0 * height_sum)/k;
        height_sum = 0;
        cout<<x[j]<<" | "<<h[j]<<"\n";
        j++;

    }
    return 0;
}

