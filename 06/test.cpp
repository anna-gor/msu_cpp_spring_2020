#include <iostream>
#include <sstream>

#include "format.h"

#define checkEqual(x, y) \
    do { \
        if ((x) != (y)) \
        { \
            std::cout << "at line " << __LINE__ << ": " << (x) << " != " << (y) << '\n'; \
        }; \
    } while(0)

#define checkThrow(x) \
    do { \
        try { (x); } \
        catch (const std::runtime_error&) { break; } \
        catch (...) {} \
        std::cout << "expected runtime_error at line " << __LINE__ << '\n'; \
    } while(0)

struct Test
{
};

std::ostream& operator<<(std::ostream& out, const Test&)
{
    out << "test";
    return out;
}

int main()
{
    checkEqual(format(""), "");
    checkEqual(format("1"), "1");
    checkEqual(format("{1}", 1, 2), "2");
    checkEqual(format("{0}{0}", "a"), "aa");
    checkEqual(format("{0}", Test()), "test");
    const Test t;
    checkEqual(format("{0}", t), "test");
    checkEqual(format("{0}", const_cast<Test&>(t)), "test");
    checkEqual(format("{1} something {0}{2} {1}", 1, t, "text"), "test something 1text test");

    checkThrow(format("{", 1));
    checkThrow(format("{0", 1));
    checkThrow(format("}", 1));
    checkThrow(format("{0}{1}{4}", 1, 2));
    checkThrow(format("{0{}", 1));
    checkThrow(format("{0a}", 1));
    checkThrow(format("0}", 1));

    std::cout << "All tests are passed!\n";

    return 0;
}