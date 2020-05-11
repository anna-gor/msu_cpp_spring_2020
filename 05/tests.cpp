#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdint.h>
#include <sstream>
#include "bigint.h"
#include <cstring>
#include <string>
using namespace std;

int main(){

    BigInt x = "878787657";
    BigInt y = x;
    assert(x == y);
    BigInt h = 878787657;
    assert(h == y);

    assert(BigInt(89) >= BigInt(-15));

    assert(BigInt(28) <= BigInt(28));

    assert(BigInt(11) < BigInt(12));

    assert(BigInt(25) - BigInt(12) + 13 + 25 == BigInt(51));

    cout << "All tests are passed!\n";

    return 0;
}