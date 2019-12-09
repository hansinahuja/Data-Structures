/*
Programming Evaluation - 4
Name:       Hansin Ahuja
Entry no:   2018csb1094

Notes and assumptions:
1) This code is functional for valid inputs only.
2) It has been assumed that the functions return values within the range of int data type.
3) The number of RAM operations have been counted in accordance with what was taught in the lectures.
4) As mentioned in the class, the number of RAM operations should be within a constant factor of 3-4 
   as per the constraints given in the problem statement. My code takes advantage of this allowed 
   constant factor. In particular:
   a) insert() returns within a constant factor of 3-4
   b) remove() returns within a constant factor of 3-4
   c) search1() returns within a constant factor of 1-2
   d) search2() returns within a constant factor of 1-2
5) In accordance with what was discussed in the class, string functions have been used only for basic
   string operations, namely just to find out length of string.
*/

#include <iostream>
using namespace std;
#define len 32                  // length of input strings for insert and delete operations
#define ll long long int

// Class for nodes of the trie
template <typename T>
class Node{

    private:
        Node *left;            // Pointer to left child
        Node *right;           // Pointer to right child
        Node *parent;          // Pointer to parent node
        ll nstrings;           // Number of substrings in the node's subtree
        ll mainstrings;        // Number of non-proper substrings in the node's subtree
        
    public:

        // Parameterized constructor
        Node(Node<T> *parent_){
            left = NULL;
            right = NULL;
            parent = parent_;
            nstrings = 0;
            mainstrings = 0;
        }

        // Getter functions
        Node<T> *get_left(){ return left; }
        Node<T> *get_right(){ return right; }
        Node<T> *get_parent(){ return parent; }
        ll get_nstrings(){ return nstrings; }
        ll get_mainstrings(){ return mainstrings; }

        // Setter functions
        void set_left(Node<T> *left_){ left = left_; }
        void set_right(Node<T> *right_){ right = right_; }
        void set_parent(Node<T> *parent_){ parent = parent_; }
        void set_nstrings(ll nstrings_){ nstrings = nstrings_; }
        void set_mainstrings(ll mainstrings_){ mainstrings = mainstrings_; }
        
        // Functions to increment or decrement variables nstrings or mainstrings
        void increment_nstrings(){ nstrings++; }
        void decrement_nstrings(){ nstrings--; }
        void increment_mainstrings(){ mainstrings++; }
        void decrement_mainstrings(){ mainstrings--; }
        void increment_both(){
            mainstrings++;
            nstrings++;
        }
        void decrement_both(){
            mainstrings--;
            nstrings--;
        }
    
};

// Class to hold trie and its functions
template <typename T>
class Trie{
    private:
        Node<T> *root;                  // Pointer to root of trie

    public:
        
        // Constructor
        Trie(){
            root = new Node<T>(NULL);
        }

        // Getter and setter functions
        Node<T> *get_root(){ return root; }
        void set_root(Node<T> *root_){ root = root_; }

        // Search for string s in trie
        int search(string s){
            Node<T> *curr = root;
            for(int i=0; i<len; i++){
                if(curr == NULL) return 0;
                if(s[i]=='0') curr = curr->get_left();
                else curr = curr->get_right();
            }
            if(curr==NULL) return 0;
            return 1;
        }

        // Insert string s in trie
        // Preprocessing: insert all proper substrings of s in trie as well
        // Returns within a constant factor of 3-4 of the allowable number of RAM operations
        int insert(string s){
            if(search(s)) return 0;
            Node<T> *curr, *n, *curr_left, *curr_right;
            for(int j=0; j<len; j++){
                curr = root;
                for(int i=j; i<len; i++){
                    if(j==0) curr->increment_both();
                    else curr->increment_nstrings();
                    if(s[i]=='0'){
                        curr_left = curr->get_left();
                        if(curr_left==NULL){
                            n = new Node<T> (curr);
                            curr->set_left(n);
                            curr = n;
                        }
                        else curr = curr_left;    
                    }
                    else{
                        curr_right = curr->get_right();
                        if(curr_right==NULL){
                            n = new Node<T> (curr);
                            curr->set_right(n);
                            curr  = n;
                        }
                        else curr = curr_right;
                    }
                }
                if(j==0) curr->increment_both();
                else curr->increment_nstrings();
            }
            return 1;
        }
        
        // Remove string s from trie
        // Undo preprocessing done when s was inserted in trie
        // Returns within a constant factor of 3-4 of the allowable number of RAM operations
        int remove(string s){
            if(!search(s)) return 0;
            Node<T> *curr, *par;
            for(int j=0; j<len; j++){
                curr = root;
                for(int i=j; i<len+1; i++){
                    if(j==0) curr->decrement_both();
                    else curr->decrement_nstrings();
                    par = curr->get_parent();
                    if(curr->get_nstrings()==0){
                        if(par == NULL){
                            curr->set_left(NULL);
                            curr->set_right(NULL);
                        }
                        else if(par->get_left() == curr) par->set_left(NULL);
                        else par->set_right(NULL);
                        break;
                    }
                    else{
                        if(s[i]=='0') curr = curr->get_left();
                        else curr = curr->get_right();
                    }
                }
            }
            return 1;
        }
        
        // search1 as described in problem statement 
        // Returns within a constant factor of 1-2 of the allowable number of RAM operations
        int search1(string s){
            int pat_len = s.size();
            Node<T> *curr = root;
            for(int i=0; i<pat_len; i++){
                if(curr==NULL) return 0;
                if(s[i]=='0') curr = curr->get_left();
                else curr = curr->get_right();
            }
            if(curr==NULL) return 0;
            else return curr->get_nstrings();
        }
        
        // Utility function to assist search2
        int search2_util(Node<T> *node, string s, int pat_len, int curr){
            if(curr>pat_len || node==NULL) return 0;
            if(curr==pat_len) return node->get_mainstrings();
            if(s[curr]=='0') return node->get_mainstrings() + search2_util(node->get_left(), s, pat_len, curr+1);
            else if(s[curr]=='1') return node->get_mainstrings() + search2_util(node->get_right(), s, pat_len, curr+1);
            else return node->get_mainstrings() + search2_util(node->get_left(), s, pat_len, curr+1) + search2_util(node->get_right(), s, pat_len, curr+1);
            
        }
        
        // search2 as described in problem statement
        // Returns within a constant factor of 1-2 of the allowable number of RAM operations
        int search2(string s){
            int pat_len = s.size();
            if(s[0]=='0') return search2_util(root->get_left(), s, pat_len, 1);
            else if(s[0]=='1') return search2_util(root->get_right(), s, pat_len, 1);
            else return search2_util(root->get_left(), s, pat_len, 1) + search2_util(root->get_right(), s, pat_len, 1);
        }
        
};

int main(){
    Trie<int> trie;
    int t;
    cin>>t;
    while(t--){
        int task;
        string s;
        cin>>task>>s;
        if(task==1) trie.insert(s);
        if(task==2) trie.remove(s);
        if(task==3) cout<<trie.search1(s)<<endl;
        if(task==4) cout<<trie.search2(s)<<endl;
    }
}