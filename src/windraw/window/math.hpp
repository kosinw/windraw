// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

namespace wd
{
    struct Size4
    {
        struct
        {
            float x;
            float y;
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
        };
    };
} // namespace wd