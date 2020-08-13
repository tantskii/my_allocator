#pragma once

#include <memory>

#include "pointer_controller.h"

template <typename T, size_t Capacity>
class LinearAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template <typename U>
    struct rebind;

    LinearAllocator()  = default;
    ~LinearAllocator();

    template <typename U, size_t OterCapacity>
    LinearAllocator(const LinearAllocator<U, OterCapacity>&);
    
    T* allocate(std::size_t n);
    void deallocate(T* p, size_t n);
    
    template <typename U, typename ...Args>
    void construct(U* p, Args &&...args);
    
    template <typename U>
    void destroy(U *p);
    
private:
    T* reserveMemory(std::size_t);
    
    T* m_start = nullptr; // указатель на начало аллоцированного блока памяти
    T* m_used  = nullptr; // указатель на конец  использованного блока памяти
    T* m_end   = nullptr; // указатель на конец  аллоцированного блока памяти
    
    PointerPool<T> m_pointer_pool;
};


template <typename T, size_t Capacity>
LinearAllocator<T, Capacity>::~LinearAllocator() {
    m_pointer_pool.clear();
    
    if (m_start != nullptr) {
        // deallocate(m_start, Capacity);
        free(m_start);
    }
}


template <typename T, size_t Capacity>
template <typename U, size_t OterCapacity>
LinearAllocator<T, Capacity>::LinearAllocator(const LinearAllocator<U, OterCapacity>&) {
    /* пустой копирующий конструктор */
}


template <typename T, size_t Capacity>
T* LinearAllocator<T, Capacity>::allocate(std::size_t n) {
    // в первый вызов метода allocate() происходит выделение памяти
    if (m_start == nullptr && n <= Capacity) {
        // сохраняем указатель в мембер т.к. аллокатор должен
        // самостоятельно освобождать память
        m_start = reserveMemory(sizeof(T) * Capacity);
        m_used  = m_start + n;
        m_end   = m_start + Capacity;
        
        m_pointer_pool.addRange(m_start, n);
        return m_start; 
    }
    // в последющие вызовы используем уже выделенную память
    else if (m_used + n <= m_end) {
        m_pointer_pool.addRange(m_used, n);
        m_used += n;
        return m_used - n;
    }
    // при попытке выделить большее число элементов выбрасывается исключение
    else {
        throw std::bad_alloc();
    }
}


template <typename T, size_t Capacity>
void LinearAllocator<T, Capacity>::deallocate(T* p, size_t n) {
//    for (size_t i = 0; i < n; i++) {
//        m_pointer_pool.remove(p + i);
//    }
    m_pointer_pool.removeRange(p, n);
    
    if (m_pointer_pool.empty()) {
        m_used = m_start;
    }
}


template <typename T, size_t Capacity>
template <typename U, typename ...Args>
void LinearAllocator<T, Capacity>::construct(U* p, Args &&...args) {
    new(p) U(std::forward<Args>(args)...);
};


template <typename T, size_t Capacity>
template <typename U>
void LinearAllocator<T, Capacity>::destroy(U *p) {
    p->~U();
}


template <typename T, size_t Capacity>
template <typename U>
struct LinearAllocator<T, Capacity>::rebind {
    using other = LinearAllocator<U, Capacity>;
};


template <typename T, size_t Capacity>
T* LinearAllocator<T, Capacity>::reserveMemory(std::size_t dataSize) {
    void* tempPtr = std::malloc(dataSize);
    if (tempPtr == nullptr) {
        throw std::bad_alloc();
    }
    return reinterpret_cast<T*>(tempPtr);
}


