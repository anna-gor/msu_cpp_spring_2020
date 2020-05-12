#include <iostream>
#include <sstream>
#include <future>
#include <thread>
#include <deque>
#include "pool.h" 
#include <assert.h>



int string_len(std::string str){
    return str.length();
}

void print_a(int a) {
    std::cout << a << '\n';
}

int ten_times(int a) {
    return a*10;
}

int main()
{
    ThreadPool pool(4);
   
    auto task1 = pool.exec(string_len,"dff");
    int res = task1.get();
    assert(res==3);
    auto task2 = pool.exec(print_a, 257);
    task2.get();
    auto task3 = pool.exec(ten_times,5);
    int res3 = task3.get();
    assert(res3==50);
    fprintf(stderr,"All tests are passed!\n");
    return 0;
}