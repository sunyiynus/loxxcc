#ifndef MP_H
#define MP_H


template <typename T,  typename M>
struct is_equal_t {
    constexpr static bool value = false;
};

template<typename T>
struct is_equal_t<T,T> {
    constexpr static bool value = true;
};


template<int T, int M>
struct is_greater {
    constexpr static bool value = T > M;
};


template<typename ... Args>
struct count_t_if;

template<typename T>
struct count_t_if<T> {
    constexpr static int value = 0;
};

template<typename T, typename M>
struct count_t_if<T, M> {
    constexpr static int value = static_cast<int>(is_equal_t<T,M>::value);
};

template<typename T, typename M, typename ... Args>
struct count_t_if<T, M, Args ...> : public count_t_if<T, Args ...> {
    constexpr static int value = is_equal_t<T, M>::value + count_t_if<T, Args ...>::value;
};


template<typename ... Args>
struct count_t;

template<typename T>
struct count_t<T> {
    constexpr static int value = 1;
};

template<typename T, typename ... Args>
struct count_t<T, Args ...> : public count_t<Args ...> {
    constexpr static int value = count_t<Args ...>::value + 1;
};


template <int CNT, int LIMIT, bool RCOND, typename ...Args>
struct is_unique_all_imp;

template <int CNT, int LIMIT, typename ...Args>
struct is_unique_all_imp<CNT, LIMIT, false, Args...> {
    constexpr static bool value = true;
};

template <int CNT, int LIMIT, typename T, typename ...Args>
struct is_unique_all_imp<CNT, LIMIT, true, T, Args ...>: public is_unique_all_imp<CNT - 1, LIMIT, is_greater<CNT - 1, LIMIT>::value, Args ..., T>{
    constexpr static bool value = is_unique_all_imp<CNT, LIMIT, is_greater<CNT - 1, LIMIT>::value, Args ..., T>::value && (count_t_if<T, Args ...>::value == 0);
};

template <typename ...Args>
struct is_unique_args {
    constexpr static bool value = is_unique_all_imp<count_t<Args ...>::value, count_t<Args ...>::value, true, Args ...>::value;
};


#endif // MP_H
