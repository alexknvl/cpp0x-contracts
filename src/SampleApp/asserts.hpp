#ifndef SAMPLAAPP_ASSERTS_HPP_
#define SAMPLAAPP_ASSERTS_HPP_

#include <exception>
#include <string>

/******************************************************************************
 * Assertions
 *****************************************************************************/
class AssertionFailed : public std::exception {
private:
    std::string message;
public:
    AssertionFailed(const std::string& message) : message(message) { }
    ~AssertionFailed() throw() { }
    const char* what() const throw() { return message.c_str(); }
};

void __assertionFailed(const char* desc, const char* expr, const char* file, unsigned int line, const char* function);

#ifdef assert
    #undef assert
#endif

#define assert(expr) \
  do {\
    bool __fail = false; \
    try { \
      if (!(expr)) {\
        __fail = true;\
      }\
    } catch (...) { \
      __assertionFailed("Assertion failed : expression has thrown an exception", PP_STRING(expr), __FILE__, __LINE__, __PRETTY_FUNCTION__); \
    } \
    if (__fail) { \
      __assertionFailed("Assertion failed", PP_STRING(expr), __FILE__, __LINE__, __PRETTY_FUNCTION__); \
    } \
  } while(0)
  
#define assertThrows(expr, type) \
  do {\
    bool success = false; \
    try {\
        expr; \
    } catch(type& e) { \
        success = true; \
    } catch(...) { } \
    \
    if (!success) { \
        __assertionFailed("Assertion failed : expression did not throw an exception of type " PP_STRING(type), PP_STRING(expr), __FILE__, __LINE__, __PRETTY_FUNCTION__); \
    } \
  } while(0)
  
  
#endif//SAMPLAAPP_ASSERTS_HPP_
