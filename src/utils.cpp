#include "utils.h"


std::string strip(const std::string& s, const std::string& left, const std::string& right) {
    unsigned int i;
    unsigned int j;
    for(i = 0; left.find(s[i]) != std::string::npos && i < s.size(); i++) {}

    for(j = s.size() - 1; left.find(s[j]) != std::string::npos && j > i; j--) {}
    return s.substr(i, j - i + 1);
}
