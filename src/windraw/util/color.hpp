// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <type_traits>

namespace wd
{
    struct ColorI;
    struct ColorF;

    struct ColorF
    {
        ColorF();
        ColorF(float r, float g, float b);
        ColorF(ColorI other);

        bool operator==(const ColorF& other) const;

        float r;
        float g;
        float b;
    };

    struct ColorI
    {
        ColorI();
        ColorI(unsigned char r, unsigned char g, unsigned char b);
        ColorI(ColorF other);

        unsigned char r;
        unsigned char g;
        unsigned char b;
    };

    namespace Color
    {
        const ColorF WhiteF = ColorF(1.f, 1.f, 1.f);
        const ColorF BlackF = ColorF(0.f, 0.f, 0.f);

        const ColorI WhiteI = ColorI(255, 255, 255);
        const ColorI BlackI = ColorI(0, 0, 0);
    }
} // namespace wd

// defined hash functor specialized for ColorF
namespace std
{
    template <>
    struct hash<wd::ColorF>
    {
        std::size_t operator()(const wd::ColorF &c) const
        {
            return ((std::hash<float>()(c.r)
                        ^ std::hash<float>()(c.g) << 1)
                       >> 1)
                ^ (std::hash<float>()(c.b) << 1);
        }
    };
}