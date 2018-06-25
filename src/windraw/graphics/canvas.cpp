// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <Windows.h>
#include <d2d1.h>

#include <windraw/graphics/canvas.hpp>

namespace
{
    template <class Interface>
    inline void SafeRelease(
        Interface **ppInterfaceToRelease)
    {
        if (*ppInterfaceToRelease != nullptr)
        {
            (*ppInterfaceToRelease)->Release();

            (*ppInterfaceToRelease) = nullptr;
        }
    }
}

namespace wd
{
    Canvas::Canvas(WindowHandle handle, Size2 dimensions)
        : m_windowHandle(handle)
        , m_renderTarget(nullptr)
        , m_dimensions(dimensions)
        , m_factory(nullptr)
    {
        HRESULT hr = S_OK;

        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);

        if (!SUCCEEDED(hr))
        {
            // TODO: Add error logging here
        }
    }

    Canvas::~Canvas()
    {
        SafeRelease(&m_renderTarget);
        SafeRelease(&m_factory);

        if (!m_solidBrushes.empty())
        {
            for (auto brush : m_solidBrushes)
            {
                SafeRelease(&brush.second);
            }

            m_solidBrushes.clear();
        }
    }

    void Canvas::clear(ColorF color)
    {
        D2D1_COLOR_F d2dcolor = D2D1::ColorF(color.r, color.g, color.b);

        m_renderTarget->Clear(d2dcolor);
    }

    void Canvas::beginDraw()
    {
        HRESULT hr;

        auto renderProps     = D2D1::RenderTargetProperties();
        auto size            = D2D1::SizeU(static_cast<unsigned>(m_dimensions.width), static_cast<unsigned>(m_dimensions.height));
        auto hwndRenderProps = D2D1::HwndRenderTargetProperties(m_windowHandle, size);

        hr = m_factory->CreateHwndRenderTarget(
            renderProps,
            hwndRenderProps,
            &m_renderTarget);

        if (!SUCCEEDED(hr))
        {
            // TODO: Add error logging here
            return;
        }

        m_renderTarget->BeginDraw();
    }

    void Canvas::endDraw()
    {
        m_renderTarget->EndDraw();

        SafeRelease(&m_renderTarget);

        if (!m_solidBrushes.empty())
        {
            for (auto brush : m_solidBrushes)
            {
                SafeRelease(&brush.second);
            }

            m_solidBrushes.clear();
        }
    }

    void Canvas::draw(const RectShape &shape)
    {
        ID2D1SolidColorBrush *brush;

        if (m_solidBrushes.count(shape.color))
        {
            brush = m_solidBrushes[shape.color];
        }

        else
        {
            D2D1_COLOR_F color = D2D1::ColorF(shape.color.r, shape.color.g, shape.color.b);

            m_renderTarget->CreateSolidColorBrush(
                color,
                &brush);

            m_solidBrushes[shape.color] = brush;
        }

        Size4 dimensions = shape.dimensions;

        D2D1_RECT_F rect = D2D1::RectF(
            dimensions.x,
            dimensions.y,
            dimensions.x + dimensions.width,
            dimensions.y + dimensions.height);

        if (shape.filled)
        {
            m_renderTarget->FillRectangle(rect, brush);
        }

        else
        {
            m_renderTarget->DrawRectangle(rect, brush);
        }
    }

    void Canvas::resizeRenderTarget(const Size2 &newSize)
    {
        m_dimensions = newSize;
    }

} // namespace wd