#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
int main(){
	double alpha, beta;
    cout<<"Alpha = ";
    cin>>alpha;
    cout<<"Beta = ";
    cin>>beta;
	double r = ((double) rand() / (RAND_MAX));
	double inv = 1/alpha;
	double temp = pow((1-r), inv);
	double ans = beta/temp;
	cout<<ans<<endl;
	return 0;
}
