#include <regex>
// Write a regular expression to detect whether a binary number is divisible by 7
std::regex solution = std::regex("^(0|1((00|(01|101*0)(001*0)*1)(10|11(001*0)*1)*0)*(((00|(01|101*0)(001*0)*1)(10|11(001*0)*1)*11|01|101*0)(001*0)*01|11))+$");