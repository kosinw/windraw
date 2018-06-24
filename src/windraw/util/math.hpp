// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

namespace wd
{
    struct Size2
    {
        Size2() = default;

        Size2(float x, float y)
            : x(x)
            , y(y)
        {
        }

        union {
            struct
            {
                float x;
                float y;
            };

            struct
            {
                float w;
                float z;
            };

            struct
            {
                float width;
                float height;
            };
        };

        bool operator==(const Size2 &other);
        bool operator!=(const Size2 &other);
    };

    struct Size4
    {
        Size4() = default;
        
        Size4(float x, float y, float z, float w)
            : x(x)
            , y(y)
            , z(z)
            , w(w)
        {
        }

        union {
            struct
            {
                float x;
                float y;
            };

            Size2 xy;
        };

        union {
            struct
            {
                float w;
                float z;
            };

            struct
            {
                float width;
                float height;
            };

            Size2 wz;
        };

        bool operator==(const Size4 &other);
        bool operator!=(const Size4 &other);
    };

    using Vector2f = Size2;
    using Vector4f = Size4;
} // namespace wd