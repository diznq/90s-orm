# 90's ORM - a C++ JSON Library

This is a simple and easy-to-use C++ library for encoding and decoding JSON data. It supports the following features:

- Automatic mapping of C++ structs to JSON objects using the with_orm base class and the `WITH_ID` macro.
- Optional fields using the `orm::optional<T>` template class.
- Arrays using `std::vector<T>`
- Automatic validation on the fly

## Example

Suppose you have a C++ struct that represents a thread in a forum, with an id, a name, a list of tags, and a list of posts:

```cpp
struct post : public with_orm {
    WITH_ID;
    int id;
    std::string author;
    std::string text;
    optional<datetime> created_at;

    mapper get_orm() {
        return {
            {"id", id},
            {"author", author},
            {"text", text},
            {"created_at", created_at}
        };
    }
};

struct thread : public with_orm {
    WITH_ID;

    int id;
    std::string name;
    optional<std::vector<std::string>> tags;
    std::vector<post> posts;

    mapper get_orm() {
        return {
            {"id", id},
            {"name", name},
            {"tags", tags},
            {"posts", posts}
        };
    }
};
```

You can easily decode a JSON file that contains a thread object using the `json_decoder` class:

```cpp
json_decoder dec;
auto forum_thread = dec.decode<thread>(std::ifstream("file.json"));
```

The `json_decoder` class will automatically map the JSON fields to the corresponding C++ struct fields, using the `get_orm` method. If a field is missing or has a different type, an expected error is returned.

You can also encode a C++ struct to a JSON string using the json_encoder class:

```cpp
json_encoder enc;
std::string encoded = enc.encode(forum_thread);
```

The `json_encoder` class will automatically convert the C++ struct fields to JSON fields, using the `get_orm` method. You can also customize the encoding options, such as the indentation, the quotation mark, and the separator.

## Installation
To use this library, you need to include the header file `90s/orm/json.hpp` in your project and use the `s90::orm` namespace.

## License

This code is licensed under BSD 3-Clause License
