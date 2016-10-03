#ifndef JNB_SFML_UTILS_H
#define JNB_SFML_UTILS_H

#include <string>

#define FOREACH(LIST_TYPE, ITEM_TYPE, LIST, code)                                   \
for (LIST_TYPE<ITEM_TYPE>::iterator it = LIST.begin(); it != LIST.end(); ++it) {    \
    ITEM_TYPE value = *it;                                                          \
    code                                                                            \
}

#define FOREACH_C(LIST_TYPE, ITEM_TYPE, LIST, code)                                     \
for (LIST_TYPE<ITEM_TYPE>::const_iterator it = LIST.begin(); it != LIST.end(); ++it) {  \
    ITEM_TYPE value = *it;                                                              \
    code                                                                                \
}

static const char* const WHITESPACE = " \t\r\n";

std::string strip(const std::string& s, const std::string& left=WHITESPACE, const std::string& right=WHITESPACE);


#endif //JNB_SFML_UTILS_H
