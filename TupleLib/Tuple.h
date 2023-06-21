#include <iostream>

template <typename Head, typename ...Tail>
struct tuple : tuple<Tail...> {
public:
    using Base = tuple<Tail...>;
public:
    Base* base = static_cast<tuple<Tail...>*>(this);
    Head value;
public:
    tuple() = default;

    tuple& operator=(const tuple& other) {
        if (this == &other)
            return *this;

        value = other.value;
        if (base != nullptr && other.base != nullptr) {
            (*base) = (*other.base);
        }

        return *this;
    }

};

template <typename Head>
struct tuple<Head>{
public:
    using Base = void*;
    Head value;
    Base* base = nullptr;
public:
    tuple() = default;
    tuple(Head&& value): value(value) {}
};

template <typename Head, typename ...Tail>
tuple<Head, Tail...> make_tuple(Head head, Tail...tail){
    tuple<Head, Tail...> temp;
    temp.value = head;

    if constexpr(sizeof...(tail) > 0) {
        tuple<Tail...> base_tuple = make_tuple(tail...);
        *temp.base = base_tuple;
    }
    return temp;
}

template <typename Head>
tuple<Head> make_tuple(Head head){
    return tuple<Head>(head);
}

template <typename Type, typename Head, typename...Tail>
Type get(tuple<Head, Tail...>& tuple) {
    if constexpr(std::is_same_v<Type, Head>)
        return tuple.value;
    if constexpr(sizeof...(Tail) > 0) {
        auto temp = *tuple.base;
        return get<Type>(temp);
    } else{
        throw std::exception();
    }
}