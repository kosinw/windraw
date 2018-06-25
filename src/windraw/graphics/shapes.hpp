// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <windraw/util/color.hpp>
#include <windraw/util/math.hpp>

namespace wd
{
    struct EllipseShape
    {
        Vector2f position;
        ColorI   color;
        float    radius;
        bool     filled;
    };

    struct RectShape
    {
        Vector4f dimensions;
        ColorI   color;
        bool     filled;
    };

    struct LineShape
    {
        Vector2f start;
        Vector2f end;
        ColorI   color;
    };

    struct PolygonShape
    {
        Vector2f *   points;
        ColorI *     colors;
        unsigned int size;
        bool         filled;
    };

} // namespace wd