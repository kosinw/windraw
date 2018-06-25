// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <d2d1.h>
#include <unordered_map>

#include <windraw/graphics/shapes.hpp>
#include <windraw/util/color.hpp>
#include <windraw/util/math.hpp>
#include <windraw/window/window.hpp>

namespace wd
{
    using WindowRenderTargetHandle = ID2D1HwndRenderTarget *;

    /**
	 * @brief Represents a class that will interface will Windows drivers
	 * to draw simple 2D shapes, textures, and text.
	 * 
	 */
    class Canvas
    {
        friend Window;

    public:
        /**
         * @brief Constructs a new Canvas object.
         * 
         * @param handle A handle to a Window
         */
        Canvas(WindowHandle handle, Size2 dimensions);

        // No copy or move constructors
        Canvas(const Canvas &) = delete;
        Canvas(Canvas &&)      = delete;

        // No copy or move assignment operators
        Canvas &operator=(const Canvas &) = delete;
        Canvas &operator=(Canvas &&) = delete;

        /**
         * @brief Clears the screen with the specified color
         * 
         * @param color Color that the screen should be filled with
         * @return true If clearing the screen was successful
         * @return false If clearing the screen was unsuccessful
         */
        void clear(ColorF color = wd::Color::BlackF);

        /**
         * @brief Must be called before any drawing can occur to the render target.
         * 
         */
        void beginDraw();

        /**
         * @brief Must be called after all drawing has occured to a render target.
         * 
         */
        void endDraw();

        /**
         * @brief Draws an ellipse onto the canvas's render target.
         * 
         * @param shape An ellipse
         */
        void draw(const EllipseShape &shape);

        /**
         * @brief Draws a rectangle onto the canvas's render target.
         * 
         * @param shape A rectangle
         */
        void draw(const RectShape &shape);

        /**
         * @brief Draws a line onto the canvas's render target.
         * 
         * @param shape A line
         */
        void draw(const LineShape &shape);

        /**
         * @brief Draws a polygon onto the canvas's render target.
         * 
         * @param shape A polygon
         */
        void draw(const PolygonShape &shape);

        /**
         * @brief Destroys a Canvas object.
         * 
         */
        ~Canvas();

    private:
        void resizeRenderTarget(const Size2 &newSize);

    private:
        WindowHandle                                       m_windowHandle;
        WindowRenderTargetHandle                           m_renderTarget;
        Size2                                              m_dimensions;
        ID2D1Factory *                                     m_factory;
        std::unordered_map<ColorF, ID2D1SolidColorBrush *> m_solidBrushes;
    };
} // namespace wd