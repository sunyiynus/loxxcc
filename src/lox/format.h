#ifndef FORMAT_H
#define FORMAT_H

#include <stack>
#include <list>
#include <vector>

constexpr std::string::value_type LEFT_PAREN = '{';
constexpr std::string::value_type RIGHT_PAREN = '}';

enum {Se = 0, S1, S2, S3, S4};
enum {Ce = 0, C1, C2, C3, C4};








template<typename T = std::string::value_type>
class basic_format {
public: 
    static basic_format format(const char* formatStr)
    {
        return basic_format(formatStr);
    }

    basic_format(const char* str): formatStr(str), state(S1) {}


    template<typename ArgT>
    basic_format& operator%(const ArgT value)
    {
        args.emplace_back(std::to_string(value));
        return *this;
    }


    enum PlaceType {STRING, PLACE_HOLDER};
    struct Field
    {
        Field(const PlaceType t, const std::size_t b, const std::size_t l): type(t), begin(b), len(l) {}
        Field(const PlaceType t): type(t), begin(0), len(0) {}
        PlaceType type;
        std::size_t begin;
        std::size_t len;
    };

    void convert2StringList()
    {
        std::stack<std::string::size_type> stk;
        const static int stateMap[4][5] = {
        {Se, Se, Se, Se, Se},
        {Se, S2, S1, S1, S1},
        {Se, S2, S3, S2, S1},
        {Se, S2, S1, S1, S1}};

        auto predC1 = [](std::string::value_type c) -> bool { return c == LEFT_PAREN; };
        auto predC2 = [](std::string::value_type c) -> bool { return c == RIGHT_PAREN; };
        auto predC3 = [](std::string::value_type c) -> bool { return isdigit(c);};
        auto predC4 = [&](std::string::value_type c) -> bool { return isprint(c) && !predC1(c) && !predC2(c) && !predC3(c);};

        auto classify = [&](std::string::value_type c) -> int {
            if (predC1(c)) {
                return C1;
            } else if (predC2(c)) {
                return C2;
            } else if (predC3(c)) {
                return C3;
            } else if (predC4(c)) {
                return C4;
            } else {
                return Ce;
            }
        };

        std::string::size_type preEdge = 0;
        for (std::string::size_type i = 0; i < formatStr.size(); ++i) {
            auto c = classify(formatStr[i]);
            state = stateMap[state][c];

            if (state == S2) {
                stk.push(i);
            } else if (state == S3) {
                if (stk.empty()) {
                    throw std::out_of_range("error");
                }
                auto leftParenIdx = stk.top();
                stk.pop();
                Field strField {PlaceType::STRING, preEdge, leftParenIdx - preEdge};
                fieldsList.push_back(strField);
                Field placeField {PlaceType::PLACE_HOLDER};
                fieldsList.push_back(placeField);
                preEdge = i + 1;
            }
        }

        if (preEdge < formatStr.size()) {
            Field strField {PlaceType::STRING, preEdge, formatStr.size() - preEdge};
            fieldsList.push_back(strField);
        }
    }




    std::string toString()
    {
        convert2StringList();
        return {};
    }

    std::list<Field>& getFieldList() {
        return fieldsList;
    }
    

private:
    using value_type = T;

    std::string formatStr;
    std::list<Field> fieldsList;
    std::vector<std::string> args;
    int state;

};


template<typename T>
std::ostream& operator<<(std::ostream& out, const basic_format<T> formatStr)
{
    return out << formatStr.toString();    
}



using Format = basic_format<std::string::value_type>;



#endif // FORMAT_H