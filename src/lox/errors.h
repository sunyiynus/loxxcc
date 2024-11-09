#ifndef ERRORS_H
#define ERRORS_H

#include <functional>
#include <iostream>



struct ErrorInfo
{
    static ErrorInfo info()
    {
        return ErrorInfo();
    }
    std::string errorLv;
    std::string lineText;
    std::string fileName;
    std::string lineNo;
    std::string errorMsg;
};




class Error
{
public:
    static void lexingError(const ErrorInfo& info);

private:
    static std::reference_wrapper<std::ostream> output;
    Error() = default;
};

class bad_grammar: public std::exception {
public:
    // 构造函数，接收错误消息
    explicit bad_grammar(const std::string& message) : message_(message) {}

    // 重写 what() 函数，返回错误消息
    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_; // 错误消息的存储
};

class bad_oprand: public std::exception {
public:
    // 构造函数，接收错误消息
    explicit bad_oprand(const std::string& message) : message_(message) {}

    // 重写 what() 函数，返回错误消息
    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_; // 错误消息的存储
};

class bad_operator: public std::exception {
public:
    // 构造函数，接收错误消息
    // explicit bad_operator(const std::string& message) : message_(message) {}
    explicit bad_operator(std::string message) : message_(std::move(message)) {}

    // 重写 what() 函数，返回错误消息
    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_; // 错误消息的存储
};




#endif // ERRORS_H