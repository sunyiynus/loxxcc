#ifndef Any_H
#define Any_H
#include <typeinfo>
#include <type_traits>
#include <memory>
#include <iostream>
#include <cassert>
#include "mp.h"


class BaseAny {
public:
    virtual ~BaseAny() = default;
    virtual const std::type_info& getType() const  = 0;
    virtual void print() const = 0;
    virtual BaseAny* clone() = 0;
};

template <typename T>
class AnyStorage: public BaseAny {
public:
    T value;
    AnyStorage(const T& val) : value(val) {}
    AnyStorage(T&& val) : value(std::move(val)) {}
    const std::type_info& getType() const override {
        return typeid(T);
    }

    BaseAny* clone() override {
        return new AnyStorage<std::decay_t<T>>(*this);
    }

    void print() const override {
        // print
    }

};

class Any {
private:
    BaseAny* storage;
public:
    Any(): storage(nullptr) {}

    template <typename T>
    Any(T&& val) : storage(new AnyStorage<std::decay_t<T>>(std::forward<T>(val))) {}
    ~Any() {
        delete storage;
    }

    Any(Any&& other) noexcept : storage(other.storage) {
        other.storage = nullptr;
    }

    Any& operator=(const Any& other) {
        if (this != &other) {
            delete storage;
            storage = other.storage ? other.storage->clone() : nullptr;
        }
        return *this;
    }

    Any& operator=(Any&& other) noexcept {
        if (this != &other) {
            delete storage;
            storage = other.storage;
            other.storage = nullptr;
        }
        return *this;
    }

    template<typename T>
    bool holdsAlternative() const {
        return storage && storage->getType()  ==  typeid(T);
    }

    template <typename T>
    T& get() {
        if (!holdsAlternative<T>()) {
            throw std::bad_cast();
        }

        auto derived = dynamic_cast<AnyStorage<T>*>(storage);
        assert(derived != nullptr);
        return derived->value;
    }

    void print() const {
        if (storage) {
            storage->print();
        } else {
            // print
            std::cout << "Empty Any!" << std::endl;
        }
    }

    operator bool() const {
        return !(storage == nullptr);
    }
};


#endif // Any_H