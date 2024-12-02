//
// Created by 김민규 on 2024. 12. 1..
//

#ifndef GCPOINTER_HPP
#define GCPOINTER_HPP

#include <unordered_set>
#include "GCBase.hpp"

class GarbageCollector;  // Forward declaration

template<typename T>
class GCPointer : public GCBase {
  private:
  T* object;
  std::unordered_set<GCBase*> references;
  GarbageCollector& gc;

  public:
  GCPointer(T* obj, GarbageCollector& collector);
  ~GCPointer() override;

  T* operator->();
  T& operator*();
  const T* operator->() const;
  const T& operator*() const;

  void addReference(GCBase* ref) override;
  void removeReference(GCBase* ref) override;
  const std::unordered_set<GCBase*>& getReferences() const override;

  T* get();
  const T* get() const;
};

#endif
