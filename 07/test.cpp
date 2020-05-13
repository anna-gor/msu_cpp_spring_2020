#include <chrono>
#include <iostream>

#include <deque>
#include <list>
#include <vector>

#include "vector.h"

template <class T>
int test(T& c)
{
    const int N = 1000000;

    int res = 0;

    for (int j = 0; j < 20; ++j)
    {
        for (int i = 0; i < N / 2; ++i)
        {
            c.push_back(i + j);
        }

        for (int i : c)
        {
            res += i;
        }

        c.resize(N / 4);

        for (int i : c)
        {
            res += i;
        }

        c.resize(N);

        for (int i : c)
        {
            res += i;
        }

        for (int i = 0; i < N / 2; ++i)
        {
            c.pop_back();
        }

        for (int i : c)
        {
            res += i;
        }

        for (int i = 0; i < N / 2; ++i)
        {
            c.push_back(i + j);
        }

        for (int i : c)
        {
            res += i;
        }

        c.clear();
    }

    return res;
}

template <class X, class Y>
void doCheckEqual(const X& actual, const Y& expected, size_t line)
{
    if (actual != expected)
    {
        std::cout << "at line " << line << ": " << actual << " != " << expected << '\n';
    }
}

#define checkEqual(x, y) do { doCheckEqual((x), (y), __LINE__); } while(0)
#define checkTrue(cond) do { if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; } while(0)

static int Counter = 0;

struct Some_struct
{
    Some_struct operator+(int k){
        return *this;
    }

};

struct Count
{
    Count()
    {
        ++Counter;
    }

    Count(const Count&)
    {
        ++Counter;
    }

    Count& operator=(const Count&)
    {
        ++Counter;
        return *this;
    }

    ~Count()
    {
        --Counter;
    }
};


int main()
{
    Vector<Some_struct>v;
    Some_struct r;
    v.push_back(r);
    {
        Vector<int> v;

        checkTrue(v.empty());
        checkEqual(v.size(), 0);

        v.push_back(1);

        checkTrue(!v.empty());
        checkEqual(v.size(), 1);
        checkEqual(v[0], 1);

        v.pop_back();

        checkTrue(v.empty());
        checkEqual(v.size(), 0);

        v.push_back(3);
        v.push_back(2);
        v.push_back(1);

        checkEqual(v.size(), 3);
        checkEqual(v[0], 3);
        checkEqual(v[1], 2);
        checkEqual(v[2], 1);

        auto f = v.begin();
        checkTrue(f != v.end());
        checkEqual(*f, 3);
        ++f;
        checkTrue(f != v.end());
        checkEqual(*f, 2);
        ++f;
        checkTrue(f != v.end());
        checkEqual(*f, 1);
        ++f;
        checkTrue(f == v.end());

        v.reserve(10000);
        checkEqual(v.size(), 3);
        checkTrue(v.capacity() >= 10000);

        const auto c = v.capacity();

        v.resize(2);
        checkEqual(v.size(), 2);
        checkEqual(v.capacity(), c);
        checkEqual(v[0], 3);
        checkEqual(v[1], 2);

        v.resize(3);
        checkEqual(v.size(), 3);
        checkEqual(v.capacity(), c);
        checkEqual(v[0], 3);
        checkEqual(v[1], 2);
        checkEqual(v[2], 0);
    }

    {

        Vector<Count> v;
        v.resize(50);
        checkEqual(Counter, 50);

       for (int i = 0; i < 100; ++i)
        {
            v.push_back(Count());
        }

        checkEqual(Counter, 150);

        v.resize(100);

        checkEqual(Counter, 100);

        for (int i = 0; i < 30; ++i)
        {
            v.pop_back();
        }

        checkEqual(Counter, 70);

        v.resize(20);

        checkEqual(Counter, 20);

        v.clear();

        checkEqual(Counter, 0);
    }

    checkEqual(Counter, 0);

    int result = 0;

    {
        std::vector<int> v;
        result += test(v);
    }
    printf("All tests are passed!\n");
    return result;


}