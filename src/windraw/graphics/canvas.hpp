// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <windraw/graphics/canvas_impl.hpp>

namespace wd
{
    /**
	 * @brief Represents a class that will interface will Windows drivers
	 * to draw simple 2D shapes, textures, and text.
	 * 
	 */
    class Canvas
    {
    public:
		Canvas();
    private:
        CanvasImpl *m_impl;
    };
} // namespace wd