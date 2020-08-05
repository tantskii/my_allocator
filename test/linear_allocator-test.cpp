#include "linear_allocator.h"
#include "factorial.h"

#include "gtest/gtest.h"

#include <stdexcept>
#include <map>


const int MaxSize = 10;
using MapAlloc = LinearAllocator<std::pair<const int, int>, MaxSize>;


TEST(MyAllocatorTest, Map) {
    std::map<int, int, std::less<int>, MapAlloc> m;
    
    for (int i = 0; i < 10; i++) {
        m[i] = factorial(i);
    }
    
    ASSERT_EQ(m.at(0), 1);
    ASSERT_EQ(m.at(1), 1);
    ASSERT_EQ(m.at(2), 2);
    ASSERT_EQ(m.at(3), 6);
    ASSERT_EQ(m.at(4), 24);
    ASSERT_EQ(m.at(5), 120);
    ASSERT_EQ(m.at(6), 720);
    ASSERT_EQ(m.at(7), 5'040);
    ASSERT_EQ(m.at(8), 40'320);
    ASSERT_EQ(m.at(9), 362'880);
}


TEST(MyAllocatorTest, AllocateMoreThanMax) {
    LinearAllocator<int, 10> alloc;
    
    ASSERT_THROW(alloc.allocate(11), std::bad_alloc);
}


TEST(MyAllocatorTest, AllDataInTheRow) {
    LinearAllocator<int, 10> alloc;
    
    int* buf_1 = alloc.allocate(4);
    int* buf_2 = alloc.allocate(5);
    int* buf_3 = alloc.allocate(1);
    
    ASSERT_EQ(buf_1 + 4, buf_2);
    ASSERT_EQ(buf_2 + 5, buf_3);
}
