/**
 * @brief 通用工具
 */

#ifndef _COMMONTOOL_H
#define _COMMONTOOL_H

#include <string>

using std::string;

/**
 * @brief 计算字符所占字节数
 * @param ch 字符
 */
size_t nBytesCode(const char ch);

/**
 * @brief 计算字符串的字符长度
 * @param str 字符串
 */
std::size_t length(const std::string &str);
#endif  //_COMMONTOOL_H

/**
 * @brief 求取三个数的最小值
 */
int triple_min(const int &a, const int &b, const int &c);

/**
 * @brief 计算最小编辑距离-包括处理中英文
 * @param lhs 字符串1
 * @param rhs 字符串2
 */
int editDistance(const std::string &lhs, const std::string &rhs);