/**
 * Project SearchEngine
 */

#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

struct SplitToolConfig {
  const char* const DICT_PATH = "../include/cppjieba/dict/jieba.dict.utf8";
  const char* const HMM_PATH = "../include/cppjieba/dict/hmm_model.utf8";
  const char* const USER_DICT_PATH = "../include/cppjieba/dict/user.dict.utf8";
  const char* const IDF_PATH = "../include/cppjieba/dict/idf.utf8";
  const char* const STOP_WORD_PATH = "../include/cppjieba/dict/stop_words.utf8";
};

class Configuration {};

#endif  //_CONFIGURATION_H