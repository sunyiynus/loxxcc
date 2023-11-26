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




#endif // ERRORS_H