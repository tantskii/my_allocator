#pragma once

#include <stdexcept>
#include <string>


template <typename U>
struct Node {
    Node(const U& obj) : object(obj) {}
    U object;
    Node<U> * next = nullptr;
};


template<typename I>
class Iterator: public std::iterator<std::input_iterator_tag, Node<I>> {
public:
    Iterator(const Iterator &it);
    bool operator!=(Iterator const& other) const;
    bool operator==(Iterator const& other) const;
    I& operator*() const;
    Iterator& operator++();
    Iterator(Node<I>* m_nodePtr);
private:
    Node<I>* m_nodePtr;
};


template <typename T, typename Allocator = std::allocator<Node<T>>>
class ForwardList {
public:
    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
    
    ForwardList() = default;
    ~ForwardList();
    void addElement(const T& elem);
    
    iterator begin();
    iterator end();
    
    T& at (size_t index);
    const T& at (size_t index) const;
    
    size_t size() const;
    bool empty() const;
    void clear();
    
private:
    Allocator m_allocator;
    Node<T> * m_head = nullptr;
    Node<T> * m_tail = nullptr;
    size_t m_size = 0;
};

template <typename T, typename Allocator>
void ForwardList<T, Allocator>::addElement(const T& elem) {
    if (empty()) {
        m_head = m_tail = m_allocator.allocate(1);
    } else {
        m_tail->next = m_allocator.allocate(1);
        m_tail = m_tail->next;
    }
    
    m_allocator.construct(m_tail, elem);

    m_size++;
}


template <typename T, typename Allocator>
bool ForwardList<T, Allocator>::empty() const {
    return m_size == 0;
}


template <typename T, typename Allocator>
size_t ForwardList<T, Allocator>::size() const {
    return m_size;
}

template <typename T, typename Allocator>
void ForwardList<T, Allocator>::clear() {
    Node<T> * next_node = nullptr;
    for (Node<T> * node = m_head; node != nullptr;) {
        next_node = node->next;
        m_allocator.destroy(node);
        m_allocator.deallocate(node, 1);
        node = next_node;
    }
    m_size = 0;
    m_tail = m_head = nullptr;
}


template <typename T, typename Allocator>
typename ForwardList<T, Allocator>::iterator ForwardList<T, Allocator>::begin() {
    return iterator(m_head);
}


template <typename T, typename Allocator>
typename ForwardList<T, Allocator>::iterator ForwardList<T, Allocator>::end() {
    return iterator(m_tail->next);
}


template <typename T, typename Allocator>
T& ForwardList<T, Allocator>::at(size_t index) {
    if (index >= size()) {
        std::string message = "index " + std::to_string(index) + " is out of range";
        throw std::out_of_range(message);
    }
    
    Node<T> * node = m_head;
    for (size_t i = 0; i != index; i++) {
        node = node->next;
    }
    
    return node->object;
}


template <typename T, typename Allocator>
const T& ForwardList<T, Allocator>::at(size_t index) const {
    if (index >= size()) {
        std::string message = "index " + std::to_string(index) + " is out of range";
        throw std::out_of_range(message);
    }
    
    Node<T> * node = m_head;
    for (size_t i = 0; i != index; i++) {
        node = node->next;
    }
    
    return node->object;
}


template <typename T, typename Allocator>
ForwardList<T, Allocator>::~ForwardList() {
    clear();
}


// Iterator
template <typename I>
Iterator<I>::Iterator(Node<I>* nodePtr) : m_nodePtr(nodePtr)
{ }


template <typename I>
Iterator<I>::Iterator(const Iterator<I>& it) : m_nodePtr(it.m_nodePtr)
{ }


template <typename I>
bool Iterator<I>::operator!=(Iterator const& other) const {
    return m_nodePtr != other.m_nodePtr;
}


template <typename I>
bool Iterator<I>::operator==(Iterator const& other) const {
    return m_nodePtr == other.m_nodePtr;
}


template <typename I>
I& Iterator<I>::operator*() const {
    return m_nodePtr->object;
}


template <typename I>
Iterator<I>& Iterator<I>::operator++() {
    m_nodePtr = m_nodePtr->next;
    return *this;
}
