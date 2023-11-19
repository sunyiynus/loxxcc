#include "errors.h"
#include "format.h"

std::reference_wrapper<std::ostream> Error::output = std::cout;

void Error::lexingError(const ErrorInfo& info)
{

}