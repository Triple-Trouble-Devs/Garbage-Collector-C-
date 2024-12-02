//
// Created by 김민규 on 2024. 12. 1..
//

#include "GCPointer.hpp"
#include "GargabeCollector.hpp"

template<typename T>
GCPointer<T>::GCPointer(T* obj, GarbageCollector& collector)
    : object(obj), gc(collector) {}

template<typename T>
GCPointer<T>::~GCPointer() {
  if (object) {
    delete object;
  }
}

template<typename T>
T* GCPointer<T>::operator->() {
  return object;
}

template<typename T>
T& GCPointer<T>::operator*() {
  return *object;
}

template<typename T>
const T* GCPointer<T>::operator->() const {
  return object;
}

template<typename T>
const T& GCPointer<T>::operator*() const {
  return *object;
}

template<typename T>
void GCPointer<T>::addReference(GCBase* ref) {
  references.insert(ref);
  if (auto obj = gc.findObject(this)) {
    gc.removeFromRootSet(obj);
  }
}

template<typename T>
void GCPointer<T>::removeReference(GCBase* ref) {
  references.erase(ref);
}

template<typename T>
const std::unordered_set<GCBase*>& GCPointer<T>::getReferences() const {
  return references;
}

template<typename T>
T* GCPointer<T>::get() {
  return object;
}

template<typename T>
const T* GCPointer<T>::get() const {
  return object;
}