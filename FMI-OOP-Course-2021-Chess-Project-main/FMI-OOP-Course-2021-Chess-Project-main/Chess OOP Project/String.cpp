#include "String.h"

void String::concat(const String& other) {
    if (size == capacity) {
        resize();
    }
    if (capacity - size >= other.size) {
        size_t temp = size;
        for (int i = 0; i < other.size; i++) {
            chars[temp] = other.chars[i];
            ++temp;
        }
        size = size + other.size;
        chars[size] = '\0';
    }
    else {
        resize();
        concat(other);
    }
}

void String::copy(const String& other) {
    capacity = other.capacity;
    size = other.size;
    chars = new char[capacity + 1];

    for (int i = 0; i < size; i++) {
        chars[i] = other.chars[i];
    }
    chars[size] = '\0';
}

void String::resize() {
    capacity = capacity * 2;
    char* temp = new char[capacity + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = chars[i];
    }
    delete[] chars;
    chars = temp;
}

void String::destroy() {
    delete[] this->chars;
    // this->str = nullptr;
}

String::String() :chars(nullptr), size(0), capacity(8) {}

String::String(const String& other) {
    copy(other);
}

String& String::operator=(const String& other) {
    if (this != &other) {
        destroy();
        copy(other);
    }
    return *this;
}

String::~String() {
    destroy();
}

String::String(const char* _str) {
    size = strlen(_str);
    capacity = size * 2;
    chars = new char[capacity + 1];
    strcpy_s(chars, capacity + 1, _str);
    chars[size] = '\0';
}

size_t String::getLenght() const {
    return size;
}

const bool String::isEmpty() const {
    return size == 0;
}

bool String::contains(String infix)
{
    bool result = false;
    for (int i = 0; i < infix.size; i++) {
        if (chars[i] == infix[i]) {
            for (int j = i; j < infix.size + i; j++) {
                if (chars[j] != infix[j - i]) break;
                if (infix.size - 1 == j - i) {
                    result = true;
                    break;
                }
            }

        }
    }

    return result;

}

char String::operator[](const size_t index) const {

    if (index >= this->size) {
        exit(-1);
    }
    return this->chars[index];
}

void String::addChar(const char& add) {
    if (size == capacity - 1) {
        resize();
    }
    chars[size] = add;
    ++size;
    chars[size] = '\0';
}

void String::removeChar() {
    size--;
    chars[size] = '\0';
}

String& String::operator+(const String& other) {
    concat(other);
    return*this;
}

String& String::operator+=(const String& other) {
    concat(other);
    return*this;
}

bool String::operator==(const String& other) {
    return strcmp(chars, other.chars) == 0 ? true : false;
}

std::ostream& operator<<(std::ostream& os, const String& _string) {
    for (int i = 0;i < _string.size;i++) {
        os << _string.chars[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, String& _string) {
    char* buffer = new char[128];
    is.getline(buffer, 128);
    _string = String(buffer);
    delete[] buffer;

    return is;
}