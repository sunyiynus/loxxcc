#ifndef VARIANT_H
#define VARIANT_H
#include <typeinfo>
#include <memory>
#include <iostream>
#include "mp.h"


class BaseVariant {
public:
    virtual ~BaseVariant() = default;
    virtual const std::type_info& getType() const  = 0;
    virtual void print() const = 0;
    virtual BaseVariant* clone() = 0;
};

template <typename T>
class VariantStorage: public BaseVariant {
public:
    T value;
    VariantStorage(const T& val) : value(val) {}
    VariantStorage(T&& val) : value(std::move(val)) {}
    const std::type_info& getType() const override {
        return typeid(T);
    }

    BaseVariant* clone() override {
        return new VariantStorage<std::decay_t<T>>(*this);
    }

    void print() const override {
        // print
    }

};

class Variant {
private:
    BaseVariant* storage;
public:
    Variant(): storage(nullptr) {}

    template <typename T>
    Variant(T&& val) : storage(new VariantStorage<std::decay_t<T>>(std::forward<T>(val))) {}
    ~Variant() {
        delete storage;
    }

    Variant(Variant&& other) noexcept : storage(other.storage) {
        other.storage = nullptr;
    }

    Variant& operator=(const Variant& other) {
        if (this != &other) {
            delete storage;
            storage = other.storage ? other.storage->clone() : nullptr;
        }
        return *this;
    }

    Variant& operator=(Variant&& other) noexcept {
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

        auto derived = dynamic_cast<VariantStorage<T>*>(storage);
        assert(derived != nullptr);
        return derived->value;
    }

    void print() const {
        if (storage) {
            storage->print();
        } else {
            // print
            std::cout << "Empty variant!" << std::endl;
        }
    }
};


#endif // VARIANT_H