#pragma once

#include "TypeList.h"
#include "iomanip"

template<typename T>
struct Holder {
    T value;
};


template<size_t Power>
struct Power3 {
    static const size_t res = 3 * Power3<Power - 1>::res;
};

template<>
struct Power3<0> {
    static const size_t res = 1;
};


template<size_t Position, size_t Level, size_t PositionInLevel>
struct NextPosition {
    static const size_t count_right = Power3<Level>::res - PositionInLevel;
    static const size_t count_left_up = 3 * (PositionInLevel - 1);
    static const size_t res = Position + count_right + count_left_up;
};

template<size_t PositionInLevel>
struct NextLevelPosition {
    static const size_t res = 3 * (PositionInLevel - 1);
};

template<
        typename CurrentType,
        typename Tlist,
        bool Linear,
        size_t Position,
        size_t Level,
        size_t PositionInLevel,
        template<class T> class Unit>
struct Hierarchy;

template<
        typename Tlist,
        size_t Position,
        size_t Level,
        size_t PositionInLevel,
        template<class T> class Unit>
struct Hierarchy<NullType, Tlist, true, Position, Level, PositionInLevel, Unit> {
};

template<
        typename Tlist,
        size_t Position,
        size_t Level,
        size_t PositionInLevel,
        template<class T> class Unit>
struct Hierarchy<NullType, Tlist, false, Position, Level, PositionInLevel, Unit> {
};

template<
        typename CurrentType,
        typename Tlist,
        size_t Position,
        size_t Level,
        size_t PositionInLevel,
        template<class T> class Unit>
struct Hierarchy<CurrentType, Tlist, true, Position, Level, PositionInLevel, Unit>
        :
                Hierarchy
                        <typename TypeAt<
                                NextPosition<Position, Level, PositionInLevel>::res +
                                1, Tlist>::res,
                                Tlist,
                                false,
                                NextPosition<Position, Level, PositionInLevel>::res +
                                1,
                                Level + 1,
                                NextLevelPosition<PositionInLevel>::res + 1,
                                Unit>,

                Hierarchy
                        <typename TypeAt<
                                NextPosition<Position, Level, PositionInLevel>::res +
                                2, Tlist>::res,
                                Tlist,
                                false,
                                NextPosition<Position, Level, PositionInLevel>::res +
                                2,
                                Level + 1,
                                NextLevelPosition<PositionInLevel>::res + 2,
                                Unit>,

                Hierarchy
                        <typename TypeAt<
                                NextPosition<Position, Level, PositionInLevel>::res +
                                1 + 3, Tlist>::res,
                                Tlist,
                                false,
                                NextPosition<Position, Level, PositionInLevel>::res +
                                3,
                                Level + 1,
                                NextLevelPosition<PositionInLevel>::res + 3,
                                Unit> {
    Unit<CurrentType> unit;
};


template<
        typename CurrentType,
        typename Tlist,
        size_t Position,
        size_t Level,
        size_t PositionInLevel,
        template<class T> class Unit>
struct Hierarchy<CurrentType, Tlist, false, Position, Level, PositionInLevel, Unit>
        :
                Hierarchy<typename TypeAt<
                        Position + Power3<Level>::res, Tlist>::res,
                        Tlist,
                        true,
                        Position + Power3<Level>::res,
                        Level,
                        PositionInLevel,
                        Unit> {
    Unit<CurrentType> unit;
};


template<class TList, template<class T> class Unit>
struct GenCustomHierarchy :
        public Hierarchy<typename TypeAt<1, TList>::res, TList, false, 1, 1, 1, Unit>,
        public Hierarchy<typename TypeAt<2, TList>::res, TList, false, 2, 1, 2, Unit>,
        public Hierarchy<typename TypeAt<3, TList>::res, TList, false, 3, 1, 3, Unit> {
    Unit<typename TList::Head> unit;
};



