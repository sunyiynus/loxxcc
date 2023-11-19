#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <list>
#include <fstream>
#include <iterator>

namespace Utility {

inline std::string ReadFile(const std::string filepath)
{
    std::ifstream fs(filepath);
    if (fs.is_open()) {
        std::string res((std::istreambuf_iterator<char>(fs)),
                            std::istreambuf_iterator<char>());
        return res;
    }
    return {};
}


inline std::string ReadFile(const char* filepath)
{
    std::string filepathstring (filepath);
    return ReadFile(filepathstring);
}

inline std::string PathJoin(std::list<std::string> pathVec)
{
    if (pathVec.empty()) return {};
    std::string res = pathVec.front();
    pathVec.pop_front();
    for (const auto & path: pathVec) {
        res += "/";
        res += path;
    }
    return  res;
}

}  // namespace Utility

#endif  // UTILITY_H