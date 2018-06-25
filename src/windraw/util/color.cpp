// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <windraw/util/color.hpp>

namespace
{
    typedef unsigned char uchar;
}

namespace wd
{
    ColorF::ColorF()
    {
        *this = Color::WhiteF;
    }

    ColorF::ColorF(float r, float g, float b)
        : r(r)
        , g(g)
        , b(b)
    {
    }

    ColorF::ColorF(ColorI other)
        : r(other.r / 255.f)
        , g(other.g / 255.f)
        , b(other.b / 255.f)
    {
    }

    bool ColorF::operator==(const ColorF& other) const
    {
        return r == other.r && b == other.b && g == other.g;
    }

    ColorI::ColorI()
    {
        *this = Color::WhiteI;
    }

    ColorI::ColorI(uchar r, uchar g, uchar b)
        : r(r)
        , g(g)
        , b(b)
    {
    }

    ColorI::ColorI(ColorF other)
        : r(static_cast<uchar>(other.r * 255))
        , g(static_cast<uchar>(other.g * 255))
        , b(static_cast<uchar>(other.b * 255))
    {
    }

} // namespace wd