/**
 * @brief 对象语义
 */

#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

class NonCopyable {
  NonCopyable(const NonCopyable&) = delete;
  const NonCopyable& operator=(const NonCopyable&) = delete;

 protected:
  NonCopyable() = default;
  ~NonCopyable() = default;
};

#endif  //_NONCOPYABLE_H