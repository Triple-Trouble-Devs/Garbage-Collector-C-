//
// Created by 김민규 on 2024. 12. 1..
//

#include "GargabeCollector.hpp"

GarbageCollector::GarbageCollector(size_t threshold)
    : allocation_count(0), GC_THRESHOLD(threshold) {}

GarbageCollector::~GarbageCollector() {
  for (auto obj : allocated_set) {
    delete obj->get_ptr();
    delete obj;
  }
}

void GarbageCollector::markRecursive(GCObject* obj) {
  if (!obj || obj->is_marked()) return;

  obj->mark();
  auto refs = obj->get_ptr()->getReferences();
  for (GCBase* ref : refs) {
    if (auto refObj = findObject(ref)) {
      markRecursive(refObj);
    }
  }
}

GCObject* GarbageCollector::findObject(GCBase* ptr) {
  for (auto obj : allocated_set) {
    if (obj->get_ptr() == ptr) return obj;
  }
  return nullptr;
}

void GarbageCollector::removeFromRootSet(GCObject* obj) {
  std::lock_guard<std::mutex> lock(gc_mutex);
  root_set.erase(obj);
}

void GarbageCollector::collect() {
  std::lock_guard<std::mutex> lock(gc_mutex);

  // Mark phase
  for (auto root : root_set) {
    markRecursive(root);
  }

  // Sweep phase
  auto it = allocated_set.begin();
  while (it != allocated_set.end()) {
    GCObject* obj = *it;
    if (!obj->is_marked()) {
      delete obj->get_ptr();
      delete obj;
      it = allocated_set.erase(it);
    } else {
      obj->unmark();
      ++it;
    }
  }
}