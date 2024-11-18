#include "Configuration.h"

Configuration* Configuration::_pInstance = getInstance();

Configuration* Configuration::getInstance() {
  if (_pInstance == nullptr) {
    atexit(destroy);
    _pInstance = new Configuration();
  }
  return _pInstance;
}

void Configuration::LoadConfig(const string& configFilePath) {
  ifstream ifs(configFilePath);
  if (!ifs) {
    throw std::runtime_error("ifstream open file error!");
  }
  json config;
  ifs >> config;
  ifs.close();
  for (auto& item : config.items()) {
    _configs[chooseCategory(item.key())] = item.value();
  }
}

json& Configuration::getConfigMap(const ConfigCategory category) {
  return _configs[category];
}

void Configuration::destroy() {
  if (_pInstance) {
    delete _pInstance;
    _pInstance = nullptr;
  }
}

ConfigCategory Configuration::chooseCategory(const string& category) {
  if (category == "SERVER") {
    return SERVER;
  } else if (category == "REDIS") {
    return REDIS;
  }else if (category == "SPLIT_TOOL") {
    return SPLIT_TOOL;
  } else if (category == "ASSETS") {
    return ASSETS;
  } else if (category == "DATA") {
    return DATA;
  }
  return OTHER;
}
