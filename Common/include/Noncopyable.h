/**
 * @brief 对象语义
 */

#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

class Noncopyable {
  Noncopyable(const Noncopyable&) = delete;
  const Noncopyable& operator=(const Noncopyable&) = delete;

 protected:
  Noncopyable() {}
  ~Noncopyable() {}
};

#endif  //_NONCOPYABLE_H