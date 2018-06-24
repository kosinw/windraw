// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

namespace wd
{
    struct ColorF
    {
        ColorF(float r = 1.f, float g = 1.f, float b = 1.f)
            : r(r)
            , g(g)
            , b(b)
        {
        }

        ColorF(ColorI other)
            : r(other.r / 255.f)
            , g(other.g / 255.f)
            , b(other.b / 255.f)
        {
        }

        float r;
        float g;
        float b;		
    };

    struct ColorI
    {
        ColorI(unsigned char r = 255, unsigned g = 255, unsigned b = 255)
            : r(r)
            , g(g)
            , b(b)
        {
        }

        ColorI(ColorF other)
            : r(static_cast<unsigned int>(other.r * 255))
            , g(static_cast<unsigned int>(other.g * 255))
            , b(static_cast<unsigned int>(other.b * 255))
        {
        }

        unsigned char r;
        unsigned char g;
        unsigned char b;
    };
} // namespace wd