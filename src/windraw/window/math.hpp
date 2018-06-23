// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

namespace wd
{
    struct Size2
    {
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