#include <iostream>
#define full_true 4294967295
#define full_false 0
typedef unsigned long bit;

using namespace std;
//Class that represent the bit set
class BitArray {
public:
    //Basic class constructor
    BitArray() {
        count_bit = 0;
        count_long = 1;
        array = new bit(count_long);
        array[0] = 0;
    };

    //Basic class destructor
    ~BitArray() {};

    //Class constructor with initial initialization of the size and setting the first sizeof(long) bits
    explicit BitArray(int num_bits, unsigned long value = 0) {
        count_bit = num_bits;
        count_long = (num_bits-1)/32+1;
        array = new bit(count_long);

        array[0] = value;
    }

    //Class constructor with initial initialization by other instance
    BitArray(const BitArray& b) {
        count_bit = b.count_bit;
        count_long = b.count_long;

        array = new bit(b.count_long);

        for (int i = 0; i < count_long; i++) {
            array[i] = b.array[i];
        }
    }

    //Swap two BitArrays among themselves
    void swap(BitArray& b) {
        bit *temp_arr = this->array;

        this->array = b.array;
        b.array = temp_arr;

        int count_l = this->count_long;

        this->count_long = b.count_long;
        b.count_long = count_l;

        int count_b = this->count_bit;

        this->count_bit = b.count_bit;
        b.count_bit = count_b;
    }

    //Change size of BitArray and when you increase it fills with the value value)
    void resize(int num_bits, bool value = false) {
        int new_size = (num_bits-1)/32+1, min_count = min(this->count_long, new_size);
        bit* temp = new bit(new_size);

        for (int i = 0; i < min_count; i++) {
            temp[i] = this->array[i];
        }

        if (this->count_long < new_size) {
            temp[this->count_long - 1] <<= (32 - this->count_bit % 32);
            temp[this->count_long - 1] >>= (32 - this->count_bit % 32);

            if (value) {
                temp[this->count_long - 1] |= (full_true << num_bits % 32);
            }

            for (int i = this->count_long; i < new_size; i++) {
                if (value) {
                    temp[i] = full_true;
                }
                else temp[i] = full_false;
            }

            temp[new_size - 1] <<= (32 - num_bits % 32);
            temp[new_size - 1] >>= (32 - num_bits % 32);
        }
        else {
            for (int i = new_size; i < this->count_long; i++) {
                if (value) {
                    temp[i] = full_true;
                }
                else temp[i] = full_false;
            }
            temp[new_size - 1] <<= (32 - this->count_bit % 32);
            temp[new_size - 1] >>= (32 - this->count_bit % 32);

            if (value) {
                temp[new_size - 1] |= (full_true << this->count_bit % 32);
            }
        }

        this->array = temp;
        this->count_long = new_size;
        this->count_bit = num_bits;
    }

    //Fill array by zero
    void clear() {
        delete [] this->array;
        this->array = new bit[this->count_long];

        for (int i = 0; i < this->count_long; i++) {
            array[i] = full_false;
        }
    }

    //add new bit to BitArray
    void push_back(bool bit) {
        if (count_bit + 1 > count_long * 32) {
            resize(count_bit + 1, bit);
        }
        else {
            array[(count_bit)/32] |= (int)bit << count_bit;
            this->count_bit = count_bit + 1;
            this->count_long = (this->count_bit - 1)/32 + 1;
        }
    }

    //operator overloading &=, |=, ^=, <<, >>, <<=, >>=, ~ and =
    BitArray& operator&=(const BitArray& b) {
        if (this->count_bit == b.count_bit) {
            for (int i = 0; i < this->count_long; i++) {
                this->array[i] &= b.array[i];
            }
        }
        else {
            cout << "Different size of arrays" << endl;
            throw exception();
        }
    }
    BitArray& operator|=(const BitArray& b) {
        if (this->count_bit == b.count_bit) {
            for (int i = 0; i < this->count_long; i++) {
                this->array[i] |= b.array[i];
            }
        }
        else {
            cout << "Different size of arrays" << endl;
            throw exception();
        }
    }
    BitArray& operator^=(const BitArray& b) {
        if (this->count_bit == b.count_bit) {
            for (int i = 0; i < this->count_long; i++) {
                this->array[i] ^= b.array[i];
            }
        }
        else {
            cout << "Different size of arrays" << endl;
            throw exception();
        }
    }

    BitArray& operator<<=(int n) {
        int count_b = n % 32, count_l = n / 32;

        this->array[0] >>= count_b;
        long a;
        for (int i = 1; i < this->count_long; i++) {
            a = this->array[i];
            this->array[i] >>= count_b;
            a <<= 32 - count_b;
            this->array[i-1] |= a;
        }

        for (int i = 0; i < count_long-count_l; i++) {
            this->array[i] = this->array[i+count_l];
        }

        for (int i = count_long-count_l; i < count_long; i++) {
            this->array[i] = 0;
        }

        return *this;
    }

    BitArray& operator>>=(int n) {
        int count_b = n % 32, count_l = n / 32;

        this->array[count_l-1] <<= count_b;
        long a;
        for (int i = this->count_long-2; i >= 0; i--) {
            a = this->array[i];
            this->array[i] <<= count_b;
            a >>= 32 - count_b;
            this->array[i+1] |= a;
        }

        for (int i = 0; i < count_l; i++) {
            this->array[i] = 0;
        }

        for (int i = count_long-count_l; i < count_long; i++) {
            this->array[i] = this->array[i+count_l];
        }

        return *this;
    }
    BitArray operator<<(int n) const{
        BitArray a = BitArray(this->count_bit, 0);

        for (int i = 0; i < this->count_long; i++) {
            a.array[i] = this->array[i];
        }
        a <<= n;
        return a;
    }
    BitArray operator>>(int n) const {
        BitArray a = BitArray(this->count_bit, 0);

        for (int i = 0; i < this->count_long; i++) {
            a.array[i] = this->array[i];
        }
        a >>= n;
        return a;
    }

    BitArray operator~() const {
        BitArray a = BitArray(*this);

        for (int i = 0; i < a.count_long; i++) {
            a.array[i] = ~a.array[i];
        }

        a.array[a.count_long-1] &= (~((unsigned int)full_true << (a.count_bit % 32)));
        return a;
    }

    BitArray& operator=(const BitArray& b) {
        BitArray a = BitArray(b);

        return a;
    }

    //set the value to bit number n
    BitArray& set(int n, bool val = true) {
        int count_l = n / 32, count_b = n % 32;

        if (val) {
            this->array[count_l] |= (val << count_b);
        }
        else this->array[count_l] &= ~(1 << count_b);
        return *this;
    }

    //set 1 to all bits
    BitArray& set() {
        for (int i = 0; i < this->count_long; i++) {
            this->array[i] = full_true;
        }
        this->array[count_long-1] >>= (32 - count_bit % 32);

        return *this;
    }

    //set 0 to bit number n
    BitArray& reset(int n) {
        return set(n, false);
    }

    //set 0 to all bits
    BitArray& reset() {
        for (int i = 0; i < this->count_long; i++) {
            this->array[i] = 0;
        }

        return *this;
    }

    //return true if array have single bits
    bool any() const {
        for (int i = 0; i < this->count_long; i++) {
            if (this->array[i]) {
                return true;
            }
        }

        return false;
    }

    //return true if array have only zero bits
    bool none() const {
        return !this->any();
    }

    //return count of positive bits
    int count() const {
        int count = 0;
        bit a;

        for (int i = 0; i < this->count_long-1; i++) {
            a = this->array[i];
            for (int j = 0; j < this->count_bit; j++) {
                count += (a >> j) && 1;
            }
        }

        a = this->array[this->count_long - 1];
        for (int i = 0; i < this->count_bit % 32; i++) {
            count += (a >> i) & 1;
        }

        return count;
    }

    //operator overloading []
    bool operator[](int i) const {
        return (this->array[i/32] >> (i % 32)) & 1;
    }

    //return size of BitArray
    int size() const {
        return this->count_bit;
    }

    //return true if array have size 0
    bool empty() const {
        if (this->count_bit == 0) {
            return true;
        }
        else return false;
    }

    //return representation of an array as a string
    string to_string() const {
        string str;

        for (int i = 0; i < this->count_long - 1; i++) {
            for (int j = 0; j < 32; j++) {
                str.push_back(48 + ((this->array[i/32] >> (j % 32)) & 1));
            }
        }
        for (int i = 0; i < count_bit % 32; i++) {
            str.push_back(48 + ((this->array[this->count_long-1] >> (i % 32)) & 1));
        }

        if (str.empty()) {
            str.push_back('0');
        }
        return str;
    }
private:
    //Bit array)
    bit* array;

    //Stores the number of groups of bits of length 32, which are represented by the type unsigned long
    int count_long = 0;

    //Stores the number of bits in array
    int count_bit = 0;
};

//operator overloading ==, !=, &, |, ^
bool operator==(const BitArray & a, const BitArray & b) {
    if (a.size() == b.size()) {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }

        return true;
    }
    else return false;
}
bool operator!=(const BitArray & a, const BitArray & b) {
    return !(a == b);
}

BitArray operator&(const BitArray& a, const BitArray& b) {
    if (a.size() == b.size()) {
        BitArray res = BitArray(a.size(), 0);

        for (int i = 0; i < a.size(); i++) {
            res.set(i, a[i] & b[i]);
        }

        return res;
    }
    else {
        cout << "Different size of arrays" << endl;
        throw exception();
    }
}
BitArray operator|(const BitArray& a, const BitArray& b) {
    if (a.size() == b.size()) {
        BitArray res = BitArray(a.size(), 0);

        for (int i = 0; i < a.size(); i++) {
            res.set(i, a[i] | b[i]);
        }

        return res;
    }
    else {
        cout << "Different size of arrays" << endl;
        throw exception();
    }
}
BitArray operator^(const BitArray& a, const BitArray& b) {
    if (a.size() == b.size()) {
        BitArray res = BitArray(a.size(), 0);

        for (int i = 0; i < a.size(); i++) {
            res.set(i, a[i] ^ b[i]);
        }

        return res;
    }
    else {
        cout << "Different size of arrays" << endl;
        throw exception();
    }
}