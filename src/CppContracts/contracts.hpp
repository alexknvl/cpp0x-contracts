#ifndef CPPCONTRACTS_CONTRACTS_HPP_
#define CPPCONTRACTS_CONTRACTS_HPP_

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
    try { \
        if (!(expr)) {\
            __assertionFailed("Assertion failed", PP_STRING(expr), __FILE__, __LINE__, __PRETTY_FUNCTION__);\
        }\
    } catch (...) { \
    __assertionFailed("Assertion failed : expression has thrown an exception", PP_STRING(expr), __FILE__, __LINE__, __PRETTY_FUNCTION__); \
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
 * on_init and on_exit
 *****************************************************************************/
#define on_init(function) \
  struct PP_UNIQUE_LABEL(on_init_class) { \
    inline PP_UNIQUE_LABEL(on_init_class) function \
  }; \
  PP_UNIQUE_LABEL(on_init_class) PP_UNIQUE_LABEL(on_init);

#define on_exit(function) \
    struct PP_UNIQUE_LABEL(on_exit_class) { \
        inline PP_UNIQUE_LABEL(~on_exit_class) function \
    }; \
    PP_UNIQUE_LABEL(on_exit_class) PP_UNIQUE_LABEL(on_exit);

/******************************************************************************
 * Contracts
 *****************************************************************************/
#define requires(x) on_scope_init({ assert(expression); })
#define ensures(expression) on_scope_exit({ assert(expression); })

#endif//CPPCONTRACTS_CONTRACTS_HPP_