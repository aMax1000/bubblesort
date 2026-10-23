// bubblesort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <array>
#include <functional>
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
bool issort(vector<T> arr, bool(*fun)(T, T)) {
    try {
        if (arr.size() == 0) throw 0;
        if (arr.size() < 2) throw 1;
        for (int i = 0;i < arr.size() - 1;i++) {
            if (!fun(arr[i], arr[i + 1])) {
                return false;
            }
        }
        return true;
    }
    catch (int errorcode) {
        switch (errorcode) {
        case 0: cout << "empty array"; break;
        case 1: cout << "array less than 2"; break;
        default: cout << "uknown exeption"; break;
        }
    }
}
template<typename T>
bool issort(vector<T> arr) {
    try {
        if (arr.size() == 0) throw 0;
        if (arr.size() < 2) throw 1;
        for (int i = 0;i < arr.size() - 1;i++) {
            if (arr[i] >arr[i + 1]) {
                return false;
            }
        }
        return true;
    }
    catch (int errorcode) {
        switch (errorcode) {
        case 0: cout << "empty array"; break;
        case 1: cout << "array less than 2"; break;
        default: cout << "uknown exeption"; break;
        }
    }
}


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
void nsort(vector<int>& arr, int sizeofbucket,double maxvalue,int multofbucket=2) {
	int amountofbuckets = ceil((double)arr.size() / (double)sizeofbucket);
	vector<vector<int>> buckets(amountofbuckets);
	for (int i = 0;i < buckets.size();i++){
        //vector<int> temp;
		buckets[i].reserve(sizeofbucket * multofbucket);
	}
    for(int a:arr){
        //cout << (a - 1.0) / maxvalue << endl;
        //cout << (((a - 1.0) / maxvalue) * amountofbuckets) << endl;
        buckets[floor(((a-1) / maxvalue) * amountofbuckets)].push_back(a);
    }
    int i = 0;
    for (vector<int> a : buckets) {
		if (a.empty()) continue;
        a.shrink_to_fit();
        bubblesortopt(a);
        //print(a);
        for (int b : a) {
            arr[i++] = b;
        }
    }
}

int main()
{
    vector<int> arr;
    for (int i = 0;i < 10000000;i++) {
        arr.push_back(rand()+rand()*pow(2,16));
    }
    //print(arr);
/*    Timeget a;
    auto arr1 = arr;
    bubblesort(arr1);
    a.printtime<microseconds>();
    cout << endl << endl;

    Timeget b;
    auto arr2 = arr;
    bubblesortopt(arr2);
    b.printtime<microseconds>();*/

    Timeget c;
    //auto arr3 = arr;
    nsort(arr,100, pow(2, 31));
    c.printtime<milliseconds>();
    cout << issort(arr);
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
