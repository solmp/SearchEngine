/**
 * Project SearchEngine
 */

#ifndef _SPLITTOOLCPPJIEBA_H
#define _SPLITTOOLCPPJIEBA_H

#include "SplitTool.h"

class SplitToolCppJieba : public SplitTool {
 public:
  vector<string> cut();
};

#endif  //_SPLITTOOLCPPJIEBA_H