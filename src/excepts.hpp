#pragma once

#include <exception>
#include <string>

class FileExtensionException : public std::exception
{
private:
    std::string message;

public:
    FileExtensionException(std::string message) : message(message) {}
    const char *what() const noexcept override
    {
        return this->message.c_str();
    }
};

class CompilationException : public std::exception
{
private:
    std::string message;

public:
    CompilationException(std::string message) : message(message) {}
    const char *what() const noexcept override
    {
        return this->message.c_str();
    }
};