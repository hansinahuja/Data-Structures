#include <iostream>
#include <cstdlib>
#include <cmath>
#include <chrono>
using namespace std;

double get_pareto(double alpha, double beta){
    double r = ((double) rand() / (RAND_MAX));
    double inv = 1/alpha;
    double temp = pow((1-r), inv);
    double ans = beta/temp;
    return ans;
}

void generate_array(double a[], int n, double alpha, double beta){
    for(int i=0; i<n; i++) a[i] = i + 1 + get_pareto(alpha, beta);
    return;
}

void get_b(double a[], int b[], int n){
    for(int i=1; i<n; i++){
        for(int j=i-1; j>=0; j--){
            if(a[j+1]<a[j]){
                double temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
                int temp2 = b[j+1];
                b[j+1] = b[j];
                b[j] = temp2;
            }
            else break;
        }
    }
    return;
}

double insertion_sort(int* a, int n){
    std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
    for(int i=1; i<n; i++){
        for(int j=i-1; j>=0; j--){
            if(a[j+1]<a[j]){
                int temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
            else break;
        }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    return elapsed_seconds.count();
}


double average_case_analysis(int b[], int n){
    int a[n];
    double time = 0.0;
    for(int i=1; i<=100; i++){
        for(int i=0; i<n; i++) a[i] = b[i];
        time += insertion_sort(a, n);
    }
    time = time/100;
    return time;
}

int main(){
    int n;
    cout<<"N = ";
    cin>>n;
    double time[20];
    for(int i=0; i<5; i++){
        double a[n];
        int b[n];
        double alpha = i+1;
        generate_array(a, n, alpha, 1.0);
        for(int i=0; i<n; i++) b[i] = i+1;
        get_b(a, b, n);
        time[i] = average_case_analysis(b, n);
    }
    cout<<"Alpha | Avg time for P(alpha, 1)"<<endl;
    for(int i=0; i<5; i++){
        cout<<i+1<<" | "<<time[i]<<endl;
    }

    return 0;
}
