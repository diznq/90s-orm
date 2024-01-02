# 90's ORM

This repository contains ORM source code of [90's](https://github.com/diznq/80s/tree/main/src/90s)

## Abstract

Dealing with serialization / deserialization and also validation in C++ is often times pretty cumberesome and annoying. 

90's ORM tries to solve this issue by providing `any` type that can hold native types, strings, optionals, vectors and other objects that implement `with_orm` trait.

This makes it a flexible alternative that also comes with validation out of the box, since type of the underlying object is always known.

## Usage

Library consists of just a few header files, so to use it, simply include it and use `s90::orm` namespace.

### Basic concepts

Every ORM object must implement `with_orm` trait and optionally also have `WITH_ID;` or implement `static uintptr_t get_orm_id() { ... }` that returns unique value for each class. 

The reason `ORM ID` is mainly optimization, when if working in loops, `get_orm()` can be called just once with `NULL` object to retrieve relative offsets of the attributes.

### Examples

See `examples/` folder of the project with `coder.cpp` example that both decodes and encodes a JSON.

To compile, use `g++ -std=c++23 -Isrc/ examples/coder.cpp -o ./decoder`