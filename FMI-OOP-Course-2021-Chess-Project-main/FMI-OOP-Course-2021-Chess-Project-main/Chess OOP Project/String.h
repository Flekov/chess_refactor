#pragma once
#include <iostream>
#include <cstring>
class String {

private:

    char* chars;
    size_t size;
    size_t capacity;

    void concat(const String& other);
    void copy(const String& other);
    void resize();
    void destroy();

public:

    String();
    String(const String& other);
    String& operator=(const String& other);
    ~String();

    String(const char* str);

    size_t getLenght() const;

    const bool isEmpty() const;
    bool contains(String toFind);
    void addChar(const char& charToAdd);
    void removeChar();

    String& operator+(const String& other);
    String& operator+=(const String& other);
    char operator[](const size_t) const;
    bool operator==(const String& other);

    friend std::ostream& operator<<(std::ostream& os, const String& _string);
    friend std::istream& operator>>(std::istream& is, String& _string);
};

