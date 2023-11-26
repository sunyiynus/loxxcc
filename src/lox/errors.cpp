#include "errors.h"
#include "format.h"

#define ERROR_2_IO

#ifdef ERROR_2_IO
std::reference_wrapper<std::ostream> Error::output = std::cout;
#else
std::reference_wrapper<std::ostream> Error::output = std::cout;
#endif

void Error::lexingError(const ErrorInfo& info)
{

    // Error::output << Format::format("{1} : {2} :\n{3}:{4}\n{5}\n") % info.fileName 
    //                                                             % info.errorLv 
    //                                                             % info.lineNo 
    //                                                             % info.lineText 
    //                                                             % info.errorMsg;
}