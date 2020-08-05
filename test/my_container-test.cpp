#include "my_list.h"
#include "linear_allocator.h"

#include "gtest/gtest.h"


TEST(MyContainerTest, Empty) {
    ForwardList<int, std::allocator<Node<int>>> cont;
    
    ASSERT_TRUE(cont.empty());
    ASSERT_EQ(cont.size(), 0);
}


TEST(MyContainerTest, Size) {
    ForwardList<int, std::allocator<Node<int>>> cont;
    
    cont.addElement(1);
    cont.addElement(110);
    
    ASSERT_EQ(cont.size(), 2);
}


TEST(MyContainerTest, Begin) {
    ForwardList<int, std::allocator<Node<int>>> cont;
    
    cont.addElement(1);
    cont.addElement(110);
    
    ASSERT_EQ(*cont.begin(), 1);
}


TEST(MyContainerTest, StdAllocator) {
    ForwardList<int, std::allocator<Node<int>>> cont;
    for (int i = 0; i < 4; i++) {
        cont.addElement(i);
    }

    ASSERT_EQ(cont.at(0), 0);
    ASSERT_EQ(cont.at(1), 1);
    ASSERT_EQ(cont.at(2), 2);
    ASSERT_EQ(cont.at(3), 3);
}


TEST(MyContainerTest, LinearAllocator) {
    ForwardList<int, LinearAllocator<Node<int>, 4>> cont;
    for (int i = 0; i < 4; i++) {
        cont.addElement(i);
    }

    ASSERT_EQ(cont.at(0), 0);
    ASSERT_EQ(cont.at(1), 1);
    ASSERT_EQ(cont.at(2), 2);
    ASSERT_EQ(cont.at(3), 3);
}
