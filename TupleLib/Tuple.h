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


    friend tuple<Head, Tail...> make_tuple(Head head, Tail... tail);

    template <typename Type, typename...Types>
    friend Type get(const tuple<Types...>& tuple);
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
    friend tuple<Head> make_tuple(Head head);
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

template <typename Type, typename...Types>
Type get(const tuple<Types...>& tuple){

}