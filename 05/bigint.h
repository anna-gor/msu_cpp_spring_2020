#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <stdio.h>
#include <iostream>
#include <ctype.h>

class BigInt{
public:

    int size;
    int8_t sign;
    uint8_t* data;

    BigInt();

    BigInt(const char* x);

    BigInt(int64_t x);

    ~BigInt();

    BigInt(const BigInt& copied);

    BigInt& operator=(const BigInt& copied);

    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;

    BigInt operator-() const;

    bool operator==(const BigInt& other) const;

    bool operator!=(const BigInt& other) const;

    bool operator>(const BigInt& other) const;

    bool operator<(const BigInt& other) const;

    bool operator>=(const BigInt& other) const;


    bool operator<=(const BigInt& other) const;
};

std::ostream& operator<<(std::ostream& out, const BigInt& value);