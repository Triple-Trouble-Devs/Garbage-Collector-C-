//
// Created by 김민규 on 2024. 12. 1..
//

#ifndef GCBASE_HPP
#define GCBASE_HPP

#include <unordered_set>

class GCBase {
  public:
  virtual ~GCBase() = default;
  virtual const std::unordered_set<GCBase*>& getReferences() const = 0;
  virtual void addReference(GCBase* ref) = 0;
  virtual void removeReference(GCBase* ref) = 0;
};

#endif