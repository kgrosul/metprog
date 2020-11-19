#pragma once

#include "iomanip"

class NullType {};

template <typename ...Args>
struct TypeList
{
    using Head = NullType;
    using Tail = NullType;
};

template <typename H, typename ...T>
struct TypeList<H, T...>
{
    using Head = H;
    using Tail = TypeList<T...>;
};

typedef TypeList<> EmptyTypeList;

template <typename H>
struct TypeList<H>
{
    using Head = H;
    using Tail = EmptyTypeList;
};



//...................................................................//

template <size_t ind, typename ...T>
struct TypeAt {
    using res = NullType;
};

template <size_t ind, typename ...T>
struct TypeAt<ind, TypeList<T...>>
{
    using res = typename TypeAt<ind - 1, typename TypeList<T...>::Tail>::res;
};

template <size_t ind>
struct TypeAt<ind, NullType>
{
    using res = NullType;
};

template <typename ...T>
struct TypeAt<0, TypeList<T...>>
{
    using res = typename TypeList<T...>::Head;
};

//...................................................................//
