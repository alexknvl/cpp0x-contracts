#include "contracts.hpp"

#include <sstream>

void __assertionFailed(const char* desc, const char* expr, const char* file, unsigned int line, const char* function) {
    std::stringstream ss;
    ss << desc << std::endl
       << "in expression " << expr << std::endl
       << "in file " << file << " on line " << line << std::endl
       << "in function " << function << std::endl;
    throw AssertionFailed(ss.str());
}
