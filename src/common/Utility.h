#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <list>
#include <fstream>
#include <iterator>

namespace Utility {

inline static std::string ReadFile(const std::string filepath)
{
    std::ifstream fs(filepath);
    if (fs.is_open()) {
        std::string res((std::istreambuf_iterator<char>(fs)),
                            std::istreambuf_iterator<char>());
        return res;
    }
    return {};
}


inline static std::string ReadFile(const char* filepath)
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
#ifdef _WIN32
        res += "\\";
#elif defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
        res += "/";
#endif
        res += path;
    }
    return  res;
}


template<typename T>
std::ostream& print(std::ostream &out, T const &val) { 
  return (out << val << " ");
}

template<typename T1, typename T2>
std::ostream& print(std::ostream &out, std::pair<T1, T2> const &val) { 
  return (out << "{" << val.first << " " << val.second << "} ");
}

template<template<typename, typename...> class TT, typename... Args>
std::ostream& operator<<(std::ostream &out, TT<Args...> const &cont) {
  for(auto&& elem : cont) print(out, elem);
  return out;
}

template<typename T>
static bool match(std::initializer_list<T> cc, const T& type)
{
    for (const auto tt: cc) {
        if (type == tt) {
            return true;
        }
    }
    return false;
}

}  // namespace Utility

#endif  // UTILITY_H