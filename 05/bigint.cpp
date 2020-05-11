#include "bigint.h"

BigInt::BigInt():
    size(1), sign(1) {
    data = new uint8_t[1];
    data[0] = 0;
}

BigInt::BigInt(const char* x):sign(1) {
    if (x[0] == '-'){
        sign = -1;
    }
    size = strlen(x);
    data = new uint8_t[size];
    for (int i = 0; i < size; ++i){
        data[i] = x[i] - '0';
    }
}

BigInt::BigInt(int64_t x):sign(1){
    int tmpsize = 0;
    int64_t tmpx = x;

    if (x == 0) {
        size = 1;
        sign = 1;
        data = new uint8_t[1];
        data[0] = 0;
    }
    else{
        if (x < 0){
        x = (-1)*x;
        sign = -1;
        }

        while(tmpx){
            ++tmpsize;
            tmpx = tmpx/10;
        }

        size = tmpsize;
        data = new uint8_t[size];
        for (int i = size-1; i >= 0 ; --i){
            data[i] = x%10;
            x = x/10;
        }

    }
}

BigInt::~BigInt(){
    delete[] data;
}

BigInt::BigInt(const BigInt& copied): size(copied.size), sign(copied.sign){
    data = new uint8_t[size];
    for (int i=0; i < size; ++i) {
        data[i] = copied.data[i];
    }
}

BigInt& BigInt::operator=(const BigInt& copied){
    if (this == &copied)
        return *this;
    uint8_t* ptr = new uint8_t[copied.size];
    delete[] data;
    data = ptr;
    size = copied.size;
    sign = copied.sign;
    std::copy(copied.data, copied.data + size, data);
    return *this;
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (sign + other.sign == 0) {
        if (sign == -1) {
            BigInt x(*this);
            x.sign = 1;
            BigInt y(other);
            BigInt tmp = y - x;
            return tmp;
        } else {
            BigInt x(*this);
            BigInt y(other);
            y.sign = 1;
            BigInt tmp = x - y;
            return tmp;
        }
    }
    int max_size, min_size, sum;
    uint8_t *max_num;
    BigInt tmp;
    if (size >= other.size) {
        max_size = size;
        min_size = other.size;
        max_num = data;
    } else {
        max_size = other.size;
        min_size = size;
        max_num = other.data;
      }
    tmp.size = max_size + 1;
    uint8_t* tmpptr = tmp.data;
    tmp.data = new uint8_t[max_size+1];
    delete[] tmpptr;
    tmp.sign = sign;
    for (int i=0; i < tmp.size; ++i) {
        tmp.data[i] = 0;
    }
    for (int i=0; i < min_size; ++i) {
        sum = data[size-1-i] + other.data[other.size-1-i]
                                + tmp.data[max_size-i];
        tmp.data[max_size-i] = sum % 10;
        tmp.data[max_size-1-i] += sum / 10;
    }
    for (int i=min_size; i < max_size; ++i) {
        sum = tmp.data[max_size-i] + max_num[max_size-1-i];
        tmp.data[max_size-i] = sum % 10;
        tmp.data[max_size-1-i] = sum / 10;
    }
    if (tmp.data[0] == 0) {
        uint8_t *res = new uint8_t[max_size];
        for (int i=max_size; i > 0; --i) {
            res[i-1] = tmp.data[i];
        }
        delete[] tmp.data;
        tmp.data = res;
        tmp.size = max_size;
    }
    return tmp;
}

BigInt BigInt::operator-(const BigInt& other) const {
    if (sign + other.sign == 0) {
        if (sign == -1) {
            BigInt x(*this);
            BigInt y(other);
            y.sign = -1;
            BigInt tmp = x + y;
            return tmp;
        } else {
            BigInt x(*this);
            BigInt y(other);
            y.sign = 1;
            BigInt tmp = x + y;
            return tmp;
        }
    }
    int max_size, min_size, sum, equal = 1;
    uint8_t *max_num, *min_num;
    BigInt tmp;
    if (size > other.size) {
        max_size = size;
        min_size = other.size;
        max_num = data;
        min_num = other.data;
        tmp.sign = sign;
    } else if (size < other.size) {
        max_size = other.size;
        min_size = size;
        max_num = other.data;
        min_num = data;
        tmp.sign = -1 * other.sign;
    } else {
        max_size = min_size = size;
        for (int i=0; i < size; ++i) {
            if (data[i] > other.data[i]) {
                max_num = data;
                min_num = other.data;
                tmp.sign = sign;
                equal = 0;
                break;
            } else if (data[i] < other.data[i]) {
                max_num = other.data;
                min_num = data;
                tmp.sign = -1 * other.sign;
                equal = 0;
                break;
            }
        }
        if (equal == 1) {
            tmp.size = 1;
            tmp.sign = 1;
            uint8_t* tmpptr = tmp.data;
            tmp.data = new uint8_t[1];
            delete[] tmpptr;
            tmp.data[0] = 0;
            return tmp;
        }
    }
    tmp.size = max_size;
    uint8_t* tmpptr = tmp.data;
    tmp.data = new uint8_t[max_size];
    delete[] tmpptr;
    for (int i=0; i < tmp.size; ++i) {
        tmp.data[i] = 0;
    }
    for (int i=0; i < min_size; ++i) {
        sum = max_num[max_size-1-i] - min_num[min_size-1-i] + 10;
        tmp.data[max_size-1-i] += sum % 10;
        if (sum / 10 == 0) {
            tmp.data[max_size-2-i] = -1;
        }
        if (tmp.data[max_size-1-i] == -1) {
            tmp.data[max_size-1-i] = 9;
            tmp.data[max_size-2-i] = -1;
        }
    }
    for (int i=min_size; i < max_size; ++i) {
        tmp.data[max_size-1-i] += max_num[max_size-1-i];
        if (tmp.data[max_size-i-1] == -1) {
            tmp.data[max_size-i-1] = 9;
            tmp.data[max_size-i-2] = -1;
        }
    }
    int size_ = tmp.size;
    for (int i=0; i < tmp.size; ++i) {
        if (tmp.data[i] == 0) {
            size_--;
        } else {
            break;
        }
    }
    uint8_t *ptr = new uint8_t[size_];
    for (int i=0; i < size_; ++i) {
        ptr[size_-1-i] = tmp.data[tmp.size-1-i];
    }
    delete[] tmp.data;
    tmp.size = size_;
    tmp.data = ptr;
    return tmp;
}

BigInt BigInt::operator-() const {
    BigInt tmp(*this);
    tmp.sign = -1;
    return tmp;
}

bool BigInt::operator==(const BigInt& other) const {
    if (this == &other) {
        return true;
    }
    if (size != other.size) {
        return false;
    }
    for (int i=0; i < size; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator>(const BigInt& other) const {
    if (this == &other) {
        return false;
    }
    if (sign * size > other.sign * other.size) {
        return true;
    } else if (sign * size < other.sign * other.size) {
        return false;
    }
    if (sign == 1 && other.sign == -1) {
        return true;
    } else if (sign == -1 && other.sign == 1) {
        return false;
    }
    for (int i=0; i < size; ++i) {
        if (data[i] > other.data[i]) {
            if (sign == 1)
                return true;
            else
                return false;
        } else if (data[i] < other.data[i]) {
            if (sign == 1)
                return false;
            else
                return true;
        }
    }
    return false;
}

bool BigInt::operator<(const BigInt& other) const {
    if (*this == other) {
        return false;
    }
    if (*this > other) {
        return false;
    }
    return true;
}

bool BigInt::operator>=(const BigInt& other) const {
    if (*this == other) {
          return true;
    }
    if (*this > other) {
        return true;
    }
    return false;
}

bool BigInt::operator<=(const BigInt& other) const {
    if (*this == other) {
        return true;
    }
    if (*this < other) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const BigInt& value) {
    if (value.sign == -1) {
        out << '-';
    }
    for (int i=0; i < value.size; ++i) {
        out << unsigned(value.data[i]);
    }
    return out;
}