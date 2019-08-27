#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

double get_pareto(double alpha, double beta){
	double r = ((double) rand() / (RAND_MAX));
	double inv = 1/alpha;
	double temp = pow((1-r), inv);
	double ans = beta/temp;
	return ans;
}

void generate_array(double a[], int n){
	for(int i=0; i<n; i++) a[i] = i + 1 + get_pareto(2.0, 1.0);
	return;
}

void insertion_sort(double a[], int b[], int n){
	for(int i=1; i<n; i++){
		for(int j=i-1; j>=0; j--){
			if(a[j]>a[i]){
				double temp = a[j];
				a[j] = a[i];
				a[i] = temp;
				int temp2 = b[j];
				b[j] = b[i];
				b[i] = temp2;
			}
			else break;
		}
	}
	return;
}

int main(){
	int n;
	cout<<"N = ";
	cin>>n;
	double a[n];
	int b[n];
	generate_array(a, n);
	for(int i=0; i<n; i++) b[i] = i+1;
	insertion_sort(a, b, n);
	for(int i=0; i<n; i++) cout<<b[i]<<" ";
	return 0;
}
