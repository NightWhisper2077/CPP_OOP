#include "gtest/gtest.h"
#include "../LabOne.cpp"

TEST(ConstructEmpty, ConstructFromSize) {
    BitArray a = BitArray();
    BitArray b = BitArray(0,0);
    EXPECT_EQ(a, b);
}

TEST(ConstructEmptyFromOther, ConstructFromOther) {
    BitArray a = BitArray();
    BitArray b = BitArray(a);
    EXPECT_EQ(a, b);
}

TEST(Swap, 2BitArray) {
    BitArray a = BitArray(3, 2);
    BitArray c = BitArray(a);
    BitArray b = BitArray(2, 3);
    a.swap(b);
    EXPECT_EQ(b, c);
}

TEST(Resize, BitArray) {
    BitArray a = BitArray(3, 2);
    a.resize(6, true);
    EXPECT_TRUE(a.size() == 6 & a[4] == true);
}

TEST(Clear, BitArray) {
    BitArray a = BitArray(3, 2);
    a.resize(6, true);
    a.clear();
    EXPECT_TRUE(a.size() == 6 & a[0] == false);
}

TEST(PushBack, BitArray) {
    BitArray a = BitArray(3, 2);
    a.push_back(true);
    EXPECT_TRUE(a.size() == 4 & a[3] == true);
}

TEST(PushBack2, BitArray) {
    BitArray a = BitArray(32, 2);
    a.push_back(true);
    EXPECT_TRUE(a.size() == 33 & a[32] == true);
}

TEST(AND, BitArray) {
    BitArray a = BitArray(3, 2);
    BitArray b = BitArray(3, 3);
    a &= b;
    EXPECT_TRUE(a[0] == false & a[1] == true);
}

TEST(AND2, BitArray) {
    BitArray a = BitArray(3, 2);
    BitArray b = BitArray(4, 3);
    a &= b;
    EXPECT_TRUE(a[0] == false & a[1] == true);
}

TEST(OR, BitArray) {
    BitArray a = BitArray(3, 2);
    BitArray b = BitArray(3, 3);
    a |= b;
    EXPECT_TRUE(a[0] == true & a[1] == true);
}

TEST(OR2, BitArray) {
    BitArray a = BitArray(3, 2);
    BitArray b = BitArray(4, 3);
    a |= b;
    EXPECT_TRUE(a[0] == true & a[1] == true);
}

TEST(SHIFT_LEFT, BitArray) {
    BitArray a = BitArray(3, 5);
    a <<= 2;
    EXPECT_TRUE(a[0] == true);
}

TEST(SHIFT_LEFT2, BitArray) {
    BitArray a = BitArray(3, 5);
    BitArray b = a << 2;
    EXPECT_TRUE(b[0] == true);
}

TEST(SHIFT_RIGHT, BitArray) {
    BitArray a = BitArray(3, 5);
    a >>= 2;
    EXPECT_TRUE(a[2] == true);
}

TEST(SHIFT_RIGHT2, BitArray) {
    BitArray a = BitArray(3, 5);
    BitArray b = a >> 2;
    EXPECT_TRUE(b[2] == true);
}

TEST(NEG, BitArray) {
    BitArray a = BitArray(3, 5);
    BitArray b = (~a);
    EXPECT_TRUE(b[1] == true);
}

TEST(SET_FALSE, BitArray) {
    BitArray a = BitArray(3, 5);
    a.set(0, false);
    EXPECT_TRUE(a[0] == false);
}

TEST(SET_TRUE, BitArray) {
    BitArray a = BitArray(3, 5);
    a.set(0, true);
    EXPECT_TRUE(a[0] == true);
}

TEST(SET, BitArray) {
    BitArray a = BitArray(3, 5);
    a.set();
    EXPECT_TRUE(a[0] == true);
}

TEST(RESET, BitArray) {
    BitArray a = BitArray(3, 5);
    a.reset(0);
    EXPECT_TRUE(a[0] == false);
}

TEST(RESET_EMPTY, BitArray) {
    BitArray a = BitArray(3, 5);
    a.reset();
    EXPECT_TRUE(a[0] == false);
}

TEST(ANY, BitArray) {
    BitArray a = BitArray(3, 5);
    EXPECT_TRUE(a.any() == true);
}

TEST(ANY_EMPTY, BitArray) {
    BitArray a = BitArray(3, 0);
    EXPECT_TRUE(a.any() == false);
}

TEST(NONE, BitArray) {
    BitArray a = BitArray(3, 5);
    EXPECT_TRUE(a.none() == false);
}

TEST(NONE_EMPTY, BitArray) {
    BitArray a = BitArray(3, 0);
    EXPECT_TRUE(a.none() == true);
}

TEST(COUNT, BitArray) {
    BitArray a = BitArray(3, 7);
    EXPECT_TRUE(a.count() == 3);
}

TEST(SIZE, BitArray) {
    BitArray a = BitArray(3, 5);
    EXPECT_TRUE(a.size() == 3);
}

TEST(EMPTY, BitArray) {
    BitArray a = BitArray(0, 0);
    EXPECT_TRUE(a.empty() == true);
}

TEST(STRING, BitArray) {
    BitArray a = BitArray(33, 1);
    EXPECT_EQ(a.to_string(), "100000000000000000000000000000000");
}

TEST(EQUAL, BitArray) {
    BitArray a = BitArray(33, 1);
    BitArray b = BitArray(33, 2);
    EXPECT_TRUE(a == b);
}

TEST(NOT_EQUAL, BitArray) {
    BitArray a = BitArray(33, 1);
    BitArray b = BitArray(33, 2);
    EXPECT_TRUE(a != b);
}

TEST(AND_BINARY, BitArray) {
    BitArray a = BitArray(4, 1);
    BitArray b = BitArray(4, 3);
    EXPECT_TRUE((a & b).to_string() == "1000");
}

TEST(AND_BINARY_EXC, BitArray) {
    BitArray a = BitArray(4, 1);
    BitArray b = BitArray(5, 3);
    EXPECT_TRUE((a & b).to_string() == "1000");
}

TEST(OR_BINARY, BitArray) {
    BitArray a = BitArray(4, 1);
    BitArray b = BitArray(4, 4);
    EXPECT_TRUE((a | b).to_string() == "1010");
}

TEST(OR_BINARY_EXC, BitArray) {
    BitArray a = BitArray(4, 1);
    BitArray b = BitArray(5, 4);
    EXPECT_TRUE((a | b).to_string() == "1010");
}


TEST(XOR_BINARY, BitArray) {
    BitArray a = BitArray(4, 1);
    BitArray b = BitArray(4, 4);
    EXPECT_TRUE((a ^ b).to_string() == "1010");
}

TEST(XOR_BINARY_EXC, BitArray) {
    BitArray a = BitArray(4, 1);
    BitArray b = BitArray(5, 4);
    EXPECT_TRUE((a ^ b).to_string() == "1010");
}