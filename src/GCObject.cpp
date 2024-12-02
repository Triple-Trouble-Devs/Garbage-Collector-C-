//
// Created by 김민규 on 2024. 12. 1..
//

#include "GCObject.hpp"

#include "GCObject.hpp"

GCObject::GCObject(GCBase* ptr) : ptr(ptr), marked(false) {}

GCObject::~GCObject() = default;

void GCObject::mark() {
  marked = true;
}

void GCObject::unmark() {
  marked = false;
}

bool GCObject::is_marked() const {
  return marked;
}

void GCObject::set_ptr(GCBase* p) {
  ptr = p;
}

GCBase* GCObject::get_ptr() const {
  return ptr;
}
