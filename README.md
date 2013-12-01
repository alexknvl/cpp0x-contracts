C++0x Contracts
===============

## Introduction

Contract Programming (CP) allows to specify preconditions, postconditions, and class invariants that are automatically checked when functions are executed at run-time. These conditions assert program specifications within the source code itself, allowing to find bugs more quickly during testing, making the code self-documenting, and increasing overall software quality.

Contract Programming is also known as Design by Contract (DbC) and it was first introduced by the Eiffel programming language.

## Library

This library supports the **simplest features** of Eiffel Contract programming, preconditions and postconditions, with no inheritance. It requires C++0x or newer versions of the C++ programming language.


## Features

### `requires(expression)`

A function/object/namespace precondition. Will test the `expression` upon entering the scope.

    #include <CppContracts/contracts.hpp>

    float MySqrt(float x) {
      // Can not take the square root of a negative number.
      requires(x > 0);
      return ::sqrt(x);
    }

### `ensures(expression)`

A function/object/namespace postcondition. Will test the `expression` on scope exit.

    #include <CppContracts/contracts.hpp>

    class PositiveNumber {
    public:
      ...
      void BlahBlah() {
        // Value must be greater than zero.
        requires(value > 0);
        // And it shall remain greater than zero.
        ensures(value > 0);
        ...
      }
      ...

    private:
      int value;
    };

### `invariant()`

An object or module invariant condition. Will invoke the `__invariant` function upon entering or exiting the scope.

    #include <CppContracts/contracts.hpp>

    class PositiveNumber {
    public:
      ...
      void BlahBlah() {
        // Will make sure that invariant is not broken in this method.
        invariant();
        ...
      }
      ...

    private:
      void __invariant() {
        // Make sure there won't be null-pointer dereference.
        assert(this != NULL);
        // Value must be greater than zero at all times.
        assert(value > 0);
      }

      int value;
    };

### Custom asserts

The `requires` and `ensures` macroses use `assert` macros internally. However you can easily provide them with your own implementation of assertions, for instance one throwing exceptions instead of aborting the execution.

    #include <MyFunkyAsserts.hpp>
    #include <CppContracts/contracts.hpp>

    int main() {
      try {
        // Will use the assert implementation you provided.
        requires(1 == 0);
      } catch(...) { }
    }