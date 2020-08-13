#pragma once

#include <unordered_set>
#include <iostream>

template <typename T>
class PointerPool {
public:
    PointerPool() = default;
    void addRange(T* pointer, size_t n_pointers);
    void add(T* pointer);
    void remove(T* pointer);
    void removeRange(T* pointer, size_t n_pointers);
    bool empty();
    void clear();
    size_t size();
private:
    std::unordered_set<T*> m_pointers;
};


template <typename T>
void PointerPool<T>::addRange(T* pointer, size_t pointers_count) {
    for (size_t i = 0; i < pointers_count; i++) {
        m_pointers.insert(pointer + i);
    }
}


template <typename T>
void PointerPool<T>::add(T* pointer) {
    m_pointers.insert(pointer);
}


template <typename T>
void PointerPool<T>::remove(T* pointer) {
    auto iter = m_pointers.find(pointer);
    
    if (iter != m_pointers.end()) {
        m_pointers.erase(pointer);
    }
}


template <typename T>
void PointerPool<T>::removeRange(T* pointer, size_t n_pointers) {
    for (size_t i = 0; i < n_pointers; i++) {
        remove(pointer + i);
    }
}


template <typename T>
bool PointerPool<T>::empty() {
    return m_pointers.empty();
}


template <typename T>
void PointerPool<T>::clear() {
    m_pointers.clear();
}

template <typename T>
size_t PointerPool<T>::size() {
    return m_pointers.size();
}
