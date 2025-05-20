#pragma once

#include <string>

constexpr const char* HELLO_STR = "Hello from Singleton!";

class Singleton
{
    // Private constructor to prevent external instantiation
    Singleton();

    ~Singleton();

public:

    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    // Static method to access the single instance
    static const Singleton& getInstance();

    // Example method
    std::string getHelloString() const;
};