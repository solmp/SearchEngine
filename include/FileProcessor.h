/**
 * Project SearchEngine
 */

#ifndef _FILEPROCESSOR_H
#define _FILEPROCESSOR_H

class FileProcessor {
 public:
  /**
   * @param fileName
   */
  string process(string fileName);

 private:
  string _titleFeature;
};

#endif  //_FILEPROCESSOR_H