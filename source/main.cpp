#include "linear_allocator.h"
#include "my_list.h"
#include "factorial.h"

#include <iostream>
#include <memory>
#include <map>
#include <vector>

int main() {
    const int MaxIndex = 10;
    
    // 1. map<int, int>
    {
        std::map<int, int> m;
        for (int i = 0; i < MaxIndex; i++) {
            m[i] = factorial(i);
        }
    }
    
    // 2. map<int, int> and custom allocator
    {
        std::map<int, int, std::less<int>,
                LinearAllocator<std::pair<const int, int>, MaxIndex>> m;

        for (int i = 0; i < MaxIndex; i++) {
            m[i] = factorial(i);
        }

        for (const auto& [key, value]: m) {
            std::cout << key << ' ' << value << std::endl;
        }
    }
    
    // 3. custom container and std::allocator
    {
        ForwardList<int, std::allocator<Node<int>>> myList;
        for (int i = 0; i < MaxIndex; i++) {
            myList.addElement(i);
        }
    }

    // 4. custom container and custom allocator
    {
        ForwardList<int, LinearAllocator<Node<int>, 10>> myList;
        for (int i = 0; i < MaxIndex; i++) {
            myList.addElement(i);
        }

        for (const auto& elem: myList) {
            std::cout << elem << std::endl;
        }
    }

    return 0;
}
