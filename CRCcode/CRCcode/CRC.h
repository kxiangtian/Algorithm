#ifndef _CRC_H_
#define _CRC_H_

#include <vector>
#include <string>

std::string CRC(const std::string &dividend, const std::string &divisor);
void division(std::vector<int> &d1, const std::vector<int> &d2, std::vector<int> &f3);
void XORfunc(const std::vector<int> &eachBeiChuShu, const std::vector<int> &d2, std::vector<int> &eachYuShu);

#endif