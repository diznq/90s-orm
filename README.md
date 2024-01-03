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

`to_native` converts from string form to native C++ form, i.e. `string -> int`
`from_native` converts from native C++ form to string form, i.e. `int -> string`

There are also some helper methods for converting between `any` and `dict<string, string>` which is quite useful for SQL adapters, as SQL queries can be converted from `data = vector<dict<string, string>>` to `result vector<T>` using `result = transform<T>(data);` and vice versa.

### Examples

See `examples/` folder of the project with `coder.cpp` example that both decodes and encodes a JSON.

To compile, use `g++ -std=c++23 -Isrc/ examples/coder.cpp -o ./decoder`

## TODO

- Missing support for `map<std::string, T>` encoding
