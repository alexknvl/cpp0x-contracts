C++0x Contracts
===============

## Introduction

Contract Programming (CP) allows to specify preconditions, postconditions, and class invariants that are automatically checked when functions are executed at run-time. These conditions assert program specifications within the source code itself, allowing to find bugs more quickly during testing, making the code self-documenting, and increasing overall software quality.

Contract Programming is also known as Design by Contract (DbC) and it was first introduced by the Eiffel programming language.

## Library

This library supports the **simplest features** of Eiffel Contract programming, preconditions and postconditions, with no inheritance. It requires C++0x or newer versions of the C++ programming language.


## Features

### `requires(<expr>)`

A function/object/namespace [[http://en.wikipedia.org/wiki/Precondition|precondition]]. Will test the {{{<expr>}}} upon entering the scope.

    #include <CppContracts/contracts.hpp>

    float MySqrt(float x) {
      // Can not take the square root of a negative number.
      requires(x > 0);
      return ::sqrt(x);
    }