#include <sstream>
#include <assert.h>

#include "serializer.h"


struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)// 
    {
        return serializer(a, b, c);
    }
};

int main()
{
    Data x { 1, true, 2 };

    std::stringstream str1;

    Serializer serializer(str1);
    assert(serializer.save(x) == Error::NoError);

    Data y { 0, false, 0 };

    Deserializer d1(str1);
    assert(d1.load(y) == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);

    auto str2 = std::stringstream("");
    Deserializer d2(str2);
    assert(d2.load(y) == Error::CorruptedArchive);

    auto str3 = std::stringstream("78 79 80");
    Deserializer d3(str3);
    assert(d3.load(y) == Error::CorruptedArchive);

    auto str4 = std::stringstream("10 true -30");
    Deserializer d4(str4);
    assert(d4.load(y) == Error::CorruptedArchive);

    auto str5 = std::stringstream("false 0");
    Deserializer d5(str5);
    assert(d5.load(y) == Error::CorruptedArchive);

    y = { 0, true, 0 };

    auto str6 = std::stringstream("8 false 5");
    Deserializer d6(str6);
    assert(d6.load(y) == Error::NoError);

    assert(y.a == 8);
    assert(y.b == false);
    assert(y.c == 5);

    auto str7 = std::stringstream("18 true 15");
    Deserializer d7(str7);
    assert(d7.load(y) == Error::NoError);

    assert(y.a == 18);
    assert(y.b == true);
    assert(y.c == 15);

    std::cout<<"All tests are passed\n"; 

    return 0;
}