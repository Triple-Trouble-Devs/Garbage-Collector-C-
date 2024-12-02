//
// Created by 김민규 on 2024. 12. 1..
//

#ifndef GCOBJECT_HPP
#define GCOBJECT_HPP

#include "GCBase.hpp"

class GCObject {
  private:
  GCBase* ptr;
  bool marked;

  public:
  explicit GCObject(GCBase* ptr);
  ~GCObject();

  void mark();
  void unmark();
  bool is_marked() const;

  void set_ptr(GCBase* p);
  GCBase* get_ptr() const;
};

#endif