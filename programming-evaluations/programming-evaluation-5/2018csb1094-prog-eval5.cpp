/*
Programming Evaluation - 5
Name:       Hansin Ahuja
Entry No:   2018csb1094

Notes and assumptions:
- This code works for valid inputs only.
- It has been assumed that at any given point during the execution, the heap doesn't contain more than
  3,00,000 elements. If this limit is crossed, my code will throw a segmentation fault. If more 
  memory is required, this limit can be changed by changing the macro SIZE defined at the beginning
  of the program.
- Time complexity analysis given at the end.
*/


#include <iostream>
#include <math.h>       // For log operations
#define SIZE 300000     // Maximum number of elements in heap
using namespace std;

// Class of nodes stored in the linked list
template <typename T>
class LinkedListNode{
    private:
        T val;                      // Value stored in node (or vertex stored)
        int colour;                 // Colour of edge joining current node and source node
        double priority;            // Priority associated with this edge
                                    // Note: priority = -log10(1 - failProb) throughout this code
        LinkedListNode<T> *next;    // Pointer to next node
    
    public:

        // Parameterized constructor
        LinkedListNode(T val_, int colour_, double priority_, LinkedListNode<T> *next_){
            val = val_;
            colour = colour_;
            priority = priority_;
            next = next_;
        }

        // Getter functions
        T get_val(){ return val; }
        int get_colour(){ return colour; }
        double get_priority(){ return priority; }
        LinkedListNode<T> *get_next(){ return next; }

        // Setter functions
        void set_val(T val_){ val = val_; }
        void set_colour(int colour_){ colour = colour_; }
        void set_priority(double priority_){ priority = priority_; }
        void set_next(LinkedListNode<T> *next_){ next = next_; }
};

// Class for nodes stored in the heap
template <typename T>
class HeapNode{
    private:
        T src;              // Index of source node
        T dest;             // Index of destination node
        int colour;         // Edge colour joining src and dest
        int redVisited;     // Number of red edges encountered
        double priority;    // Priority associated with this edge
    
    public:

        // Parameterized constructor
        HeapNode(T src_, T dest_, int colour_, int redVisited_, double priority_){
            src = src_;
            dest = dest_;
            colour = colour_;
            redVisited = redVisited_;
            priority = priority_;
        }

        // Getter functions
        T get_src(){ return src; }
        T get_dest(){ return dest; }
        int get_colour(){ return colour; }
        int get_redVisited(){ return redVisited; }
        double get_priority(){ return priority; }

        // Setter functions
        void set_src(T src_){ src = src_; }
        void set_dest(T dest_){ dest = dest_; }
        void set_colour(int colour_){ colour = colour_; }
        void set_redVisited(int redVisited_){ redVisited = redVisited_; }
        void set_priority(double priority_){ priority = priority_; }
};

// Class for heap
template <typename T>
class Heap{
    private:
        HeapNode<T> *arr[SIZE];     // Heap array
        int size;                   // Current size of heap

    public:

        // Constructor
        Heap(){
            size = 0;
        }

        // Getter function
        int get_size(){
            return size;
        }

        // Swap nodes at index i and index j
        void swapNodes(int l, int r){
            HeapNode<T> *h = arr[l];
            arr[l] = arr[r];
            arr[r] = h;
            return;
        }

        // Insert node with given parameters into the heap
        void insert(T src, T dest, int colour, int redVisited, double priority){
            HeapNode<T> *h = new HeapNode<T>(src, dest, colour, redVisited, priority);
            arr[size] = h;
            int curr = size;
            size++;
            while(1){
                int par = (curr-1)/2;
                if(curr==0) break;
                if(priority < arr[par]->get_priority()){
                    swapNodes(curr, par);
                    curr = par;
                }
                else break;
            }
            return;
        }

        // Delete node at the top of the heap and return deleted node
        HeapNode<T> *deleteMin(){
            HeapNode<T> *h = arr[0];
            size--;
            arr[0] = arr[size];
            int curr = 0;
            while(1){
                int left = (2*curr)+1;
                int right = (2*curr)+2;
                if(left>=size) break;
                if(right>=size){
                    if(arr[left]->get_priority() < arr[curr]->get_priority()) swapNodes(curr, left);
                    break;
                    
                }
                if(arr[left]->get_priority() < arr[curr]->get_priority() && arr[right]->get_priority() < arr[curr]->get_priority()){
                    if(arr[left]->get_priority() < arr[right]->get_priority()){
                        swapNodes(curr, left);
                        curr = left;
                    }
                    else{
                        swapNodes(curr, right);
                        curr = right;
                    }
                }
                else if(arr[left]->get_priority() < arr[curr]->get_priority() && arr[right]->get_priority() >= arr[curr]->get_priority()){
                    swapNodes(curr, left);
                    curr = left;
                }
                else if(arr[left]->get_priority() >= arr[curr]->get_priority() && arr[right]->get_priority() < arr[curr]->get_priority()){
                    swapNodes(curr, right);
                    curr = right;
                }
                else break;
            }
            return h;
        }
};

int main(){

    // Input section
    double g;
    int k, v, e;
    cin>>g>>k>>v>>e;
    double visited[v+1][k+1];

    // Initialize graph parameters
    LinkedListNode<int> *adjList[v+1];
    for(int i=1; i<=v; i++){
        adjList[i] = NULL;
        for(int j=0; j<=k; j++){
            visited[i][j] = -1;
        }
    }

    // Input edges and create adjacency list
    while(e--){
        int u, v, colour;
        double failProb, priority;
        cin>>u>>v>>failProb>>colour;
        priority = -log10(1-failProb);
        LinkedListNode<int> *p = new LinkedListNode<int>(u, colour, priority, adjList[v]);
        LinkedListNode<int> *q = new LinkedListNode<int>(v, colour, priority, adjList[u]);
        adjList[v] = p;
        adjList[u] = q;
    }
    
    // Insert neighbours of source node into the heap
    Heap<int> heap;
    visited[1][0] = 0;
    LinkedListNode<int> *neighbour = adjList[1];
    while(neighbour!=NULL){
        if(neighbour->get_colour()){
            if(k>=1)
                heap.insert(1, neighbour->get_val(), 1, 1, neighbour->get_priority());
        }
        else{
            heap.insert(1, neighbour->get_val(), 0, 0, neighbour->get_priority());
        }
        neighbour = neighbour->get_next();
    }

    // Execute modified Dijkstra's algorithm
    while(heap.get_size()!=0){
        HeapNode<int> *top = heap.deleteMin();
        if(visited[top->get_dest()][top->get_redVisited()] != -1) continue;
        visited[top->get_dest()][top->get_redVisited()] = top->get_priority();
        int src = top->get_dest();
        int redVisited = top->get_redVisited();
        LinkedListNode<int> *neighbour = adjList[src];
        while(neighbour!=NULL){
            if(neighbour->get_colour()){
                if(visited[neighbour->get_val()][redVisited+1] == -1 && redVisited+1<=k && (top->get_priority()+neighbour->get_priority() <= g)){
                    heap.insert(src, neighbour->get_val(), 1, redVisited+1, top->get_priority()+neighbour->get_priority());
                }
            }
            else{
                if(visited[neighbour->get_val()][redVisited] == -1 && redVisited<=k && (top->get_priority()+neighbour->get_priority() <= g)){
                    heap.insert(src, neighbour->get_val(), 0, redVisited, top->get_priority()+neighbour->get_priority());
                }
            }
            neighbour = neighbour->get_next();
        }
    }

    // Check reachability of destination node with (probSuccess >= g) and (#redEdges <= k)
    bool ans = false;
    for(int i=0; i<=k; i++){
        if(visited[v][i] != -1){
            if(visited[v][i] <= g){
                ans = true;
                break;
            }
        }
    }

    // Print output
    if(ans) cout<<"Yes\n";
    else cout<<"No\n";
}

/*
Time complexity analysis:
#vertices = v, #edges = e, k = as defined in problem statement
1) Input and initialization = O(v*k)
2) Inserting neighbours of source verttex into heap = O(e * log e) = O(e * log v)
   as e = O(v^2) => log e = O(log v)
3) Executing modified Dijkstra's:
   #inserts <= k*e
   #deleteMins <= k*e
   #times outer while loop executes <= k*e
   total time for deleteMins = O((k*e)log(k*e))
   #times inner for loop executes across all iterations <= 2*k*e
   => total time complexity = O((k*e)log(k*e))
                            = O((k*(v+e))(log e + log k))
                            = O((k*(v+e))*log e)             as k = O(e)   => log k = O(log e)
                            = O((k*(v+e))*log v)             as e = O(v^2) => log e = O(log v)


*/