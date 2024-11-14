/**
 * Project SearchEngine
 */

#ifndef _PAGELIB_H
#define _PAGELIB_H

class PageLib {
 public:
  void PageLib();

  void create();

  void store();

 private:
  DirScanner _dirScanner;
  vector<string> _pages;
  void _offsetLib : map<int, pair<int, int>>;
};

#endif  //_PAGELIB_H