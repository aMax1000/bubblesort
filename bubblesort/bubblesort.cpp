// bubblesort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;
template<typename T>
void print(vector<T> arr) {
    for (T a : arr) {
        cout << a << ' ';
       }
    cout << endl;
}
template<bool EXEPTIONS=true>
class Timeget {
    steady_clock::time_point st;
    nanoseconds duration;
    bool running = true;
public:
    Timeget(bool run=true) {
        running = run;
        if(run){
            st = high_resolution_clock::now();
            duration = st - st;
        }
    }
    void start() {
        
        if constexpr (EXEPTIONS) {
            if (running) {
                throw new exception("start timer while running");
            }
        }
        if (!running) {
            running = true;
            st = high_resolution_clock::now();
        }
    }
    void stop() {
        if constexpr (EXEPTIONS) {
            if (!running) {
                throw new exception("stop timer while not running");
            }
        }
        if(running){
            duration += high_resolution_clock::now() - st;
            running = false;
        }
    }
    template<typename T>
    T gettime() {
        if (running) {
            this->stop();
        };
        return duration_cast<T>(duration);
    }
    template<typename T>
    void printtime() {
        cout <<"time: " << this->gettime<T>()<<"  ";
    }
};


template<typename T>
void bubblesort(vector<T>& arr) {
    int n = arr.size()-1;
    for (int i = 0;i < arr.size()-1;i++) {
        for (int j = 0;j < n;j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j],arr[j + 1]);
            }
        }
        --n;
        //print(arr);
    }
}
template<typename T>
void bubblesortopt(vector<T>& arr) {
    int n = arr.size() - 1;
    int noswap = 0;
    while (n) {
        for (int j = 0;j < n;j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                noswap = 1;
            }
            else {
                noswap++;
            }
        }
        //print(arr);
        n -= noswap;
        noswap = 0;
        //cout << n;
    }
}
void nsort(vector<int> arr, int sizeofbucket,int maxvalue,int multofbucket=2) {
    long long int avr = 0;
	avr /= arr.size();
	int amountofbuckets = arr.size() / sizeofbucket + 1;
	vector<vector<int>> buckets(amountofbuckets);
	for (int i = 0;i < buckets.size();i++){
        vector<int> temp(sizeofbucket * multofbucket);
		buckets[i]=temp;
	}
    for(int a:arr){
        buckets[((a-1) / maxvalue) * amountofbuckets].push_back(a);
    }
    
    for (vector<int> a : buckets) {
        bubblesortopt(a);
        
    }
    
}

int main()
{
    vector<int> arr;
    for (int i = 0;i < 10;i++) {
        arr.push_back(rand());
    }
    Timeget a;
    auto arr1 = arr;
    bubblesort(arr1);
    a.printtime<microseconds>();
    cout << endl << endl;

    Timeget b;
    auto arr2 = arr;
    bubblesortopt(arr2);
    b.printtime<microseconds>();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
