//
// Created by 김민규 on 2024. 12. 1..
//

#ifndef GARBAGECOLLECTOR_HPP
#define GARBAGECOLLECTOR_HPP

#include <unordered_set>
#include <mutex>
#include "GCObject.hpp"
#include "GCPointer.hpp"

class GarbageCollector {
    private:
    std::unordered_set<GCObject*> allocated_set;
    std::unordered_set<GCObject*> root_set;
    std::mutex gc_mutex;
    size_t allocation_count;
    const size_t GC_THRESHOLD;

    void markRecursive(GCObject* obj);

    public:
    GarbageCollector(size_t threshold = 1000);
    ~GarbageCollector();

    template<typename T, typename... Args>
    GCPointer<T> allocate(Args&&... args);

    void removeFromRootSet(GCObject* obj);
    GCObject* findObject(GCBase* ptr);
    void collect();
};

template<typename T, typename... Args>
GCPointer<T> GarbageCollector::allocate(Args&&... args) {
    std::lock_guard<std::mutex> lock(gc_mutex);

    T* obj = new T(std::forward<Args>(args)...);
    auto ptr = new GCPointer<T>(obj, *this);
    auto gcobj = new GCObject(ptr);

    allocated_set.insert(gcobj);
    root_set.insert(gcobj);

    if (++allocation_count >= GC_THRESHOLD) {
        collect();
        allocation_count = 0;
    }

    return *ptr;
}

#endif
