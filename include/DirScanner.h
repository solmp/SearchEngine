/**
 * Project SearchEngine
 */

#ifndef _DIRSCANNER_H
#define _DIRSCANNER_H

class DirScanner {
 public:
  vector<string>& getFiles();

  /**
   * @param dir
   */
  void traverse(string dir);

 private:
  vector<string> _files;
};

#endif  //_DIRSCANNER_H