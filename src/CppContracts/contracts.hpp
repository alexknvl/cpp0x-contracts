#ifndef CPPCONTRACTS_CONTRACTS_HPP_
#define CPPCONTRACTS_CONTRACTS_HPP_

// Awesome contracts implementation (c) Konovalov Alexander
// No __result__ or __old__ yet =(
// I have an idea how to make __result__ work but it will 
// be very platform-specific, and will require a lot of
// assembly hackery.

#include <tr1/functional>
#include <exception>
#include <string>

/******************************************************************************
 * Preprocessor magic
 *****************************************************************************/

#define PP_STRING(a) #a
#define PP_CONCAT2(a,b)  a##b
#define PP_CONCAT3(a, b, c) a##b##c
#define PP_UNIQUE_LABEL_(prefix, suffix) PP_CONCAT2(prefix, suffix)
#define PP_UNIQUE_LABEL(prefix) PP_UNIQUE_LABEL_(prefix, __LINE__)

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

/******************************************************************************
 * on_scope_init and on_scope_exit macroses
 *****************************************************************************/
struct __call_on_constructor {
    template<class Func> inline __call_on_constructor(Func func) {
        func();
    }
};
#define on_scope_init(function) \
    __call_on_constructor PP_UNIQUE_LABEL(on_init) (function)

struct __call_on_destructor {
    std::tr1::function<void()> _function;
    template<class Func> inline __call_on_destructor(Func func) {
        _function = func;
    }
    inline ~__call_on_destructor() {
        _function();
    }
};
#define on_scope_exit(function) \
    __call_on_destructor PP_UNIQUE_LABEL(on_exit) (function)

/******************************************************************************
 * Contracts
 *****************************************************************************/
#define requires(expression) on_scope_init([&] () { assert(expression); })
#define ensures(expression) on_scope_exit([&] () { assert(expression); })
#define invariant() on_scope_init([&] () { __invariant(); }); on_scope_exit([&] () { __invariant(); return; })

#endif//CPPCONTRACTS_CONTRACTS_HPP_

