#include <iostream>
// #define m 5
using namespace std;

template <typename T>
class HashTable{
	private:
		T *H;
		int m;
		int delete_spots;
		
	public:
		
		HashTable(int m_){
		    m = m_;
		    H = new T[m];
			for(int i=0; i<m; i++) H[i] = -1;
			delete_spots = 0;
		}
		
// 		void c(){
// 		    cout<<delete_spots<<endl;
// 		    print_table();
// 		}

		int h(T x){
			return x%m;
		}

		int search(T key){
			int pos = h(key);
			int starting_pos = pos;
			do{
				if(H[pos]==-1) return 0;
				if(H[pos]==key) return 1;
				pos = (pos+1)%m;
			}while(pos!=starting_pos);
		}

		int insert(T key){
			if(search(key)) return 0;
			int pos = h(key);
			int starting_pos = pos;
			do{
				if(H[pos]==-1 || H[pos]==-2){
					if(H[pos]==-2) delete_spots--;
					H[pos] = key;
					return 1;
				}
				pos = (pos+1)%m;
			}while(pos!=starting_pos);
		}
		
		void remake_table(){
			T table_copy[m];
			for(int i=0; i<m; i++){
				table_copy[i] = H[i];
				H[i] = -1;
			}
			for(int i=0; i<m; i++){
				if(table_copy[i]>=0) insert(table_copy[i]);
			}
			delete_spots = 0;
			return;
		}

		int remove(T key){
			if(!search(key)) return 0;
			int pos = h(key);
			int starting_pos = pos;
			do{
				if(H[pos]==key){
					delete_spots++;
					H[pos] = -2;
					int threshold = (3*m)/10;
					if(delete_spots > threshold) remake_table();
					return 1;
				}
				pos = (pos+1)%m;
			}while(pos!=starting_pos);
		}
		
		void print_table(){
			for(int i=0; i<m; i++) cout<<H[i]<<" ";
			cout<<endl;
		}
};

int main(){
	HashTable<int> h(5);
	h.insert(1);
	h.insert(2);
	h.insert(3);
	h.remove(1);
	h.insert(7);
	h.remove(3);
	h.insert(3);
	h.print_table();
	h.remove(7);
	h.print_table();
	cout<<h.search(3);
}
