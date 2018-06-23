// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <windraw/style.hpp>
#include <windraw/window.hpp>

namespace
{
    unsigned int   numWindows  = 0;
    const wchar_t *wdClassName = L"WDClass";
}

namespace wd
{
    Window::Window(Spec spec, const std::wstring &title, unsigned int style)
        : m_windowSpec(spec)
        , m_windowStyles(style)
        , m_title(title)
    {
        init();
    }

    bool Window::init()
    {
        m_isInitialized = false;

        // If window class has not been initialized, then initialize it
        if (numWindows == 0)
        {
            if (!registerWindowClass())
            {
                return false;
            }
        }

        // Create window and windowex styles
        DWORD winStyles = WS_VISIBLE;

        if (m_windowStyles == Style::None)
        {
            winStyles |= WS_POPUP;
        }
        else
        {
            if (m_windowStyles & Style::Titlebar)
            {
                winStyles |= WS_CAPTION | WS_MINIMIZEBOX;
            }
            if (m_windowStyles & Style::Resize)
            {
                winStyles |= WS_THICKFRAME | WS_MAXIMIZEBOX;
            }

            if (m_windowStyles & Style::Close)
            {
                winStyles |= WS_SYSMENU;
            }
        }

        // Get DC of monitor to get the center position
        HDC monitorDC = GetDC(nullptr);
        int width     = GetDeviceCaps(monitorDC, HORZRES);
        int height    = GetDeviceCaps(monitorDC, VERTRES);
        int left      = (width - m_windowSpec.width) / 2;
        int top       = (height - m_windowSpec.height) / 2;

        width  = m_windowSpec.width;
        height = m_windowSpec.height;
        ReleaseDC(nullptr, monitorDC);

        // Calculate the bounding box of the whole window
        RECT boundingBox = { 0, 0, width, height };

        AdjustWindowRect(&boundingBox, winStyles, false);

        width  = boundingBox.right - boundingBox.left;
        height = boundingBox.bottom - boundingBox.top;

        HINSTANCE instance = GetModuleHandle(nullptr);

        // Create the window
        m_windowHandle = CreateWindow(
            wdClassName,
            m_title.c_str(),
            winStyles,
            left,
            top,
            width,
            height,
            NULL,
            NULL,
            instance,
            this);

        if (!m_windowHandle)
        {
            return false;
        }

        SetWindowPos(m_windowHandle, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

        numWindows++;
        m_isInitialized = true;

        return true;
    }

    bool Window::isOpen() const
    {
        return m_isInitialized && !m_isDestroyed;
    }

    bool Window::pollEvent(Event &event)
    {
        if (popEvent(event, false))
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    bool Window::popEvent(Event &event, bool blocking)
    {
        if (m_eventQueue.empty())
        {
            runMainLoop();

            if (blocking)
            {
                while (m_eventQueue.empty())
                {
                    runMainLoop();
                }
            }
        }

        if (!m_eventQueue.empty())
        {
            event = m_eventQueue.front();
            m_eventQueue.pop();

            return true;
        }

        return false;
    }

    bool Window::registerWindowClass()
    {
        WNDCLASSW wndclass;
        ZeroMemory(&wndclass, sizeof(wndclass));

        wndclass.hInstance     = GetModuleHandle(nullptr);
        wndclass.lpszClassName = wdClassName;
        wndclass.style         = CS_VREDRAW | CS_HREDRAW;
        wndclass.lpfnWndProc   = &Window::windowProcedure;
        wndclass.lpszMenuName  = NULL;

        if (RegisterClass(&wndclass))
        {
            return true;
        }

        return false;
    }

    LRESULT CALLBACK Window::windowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
    {
        LRESULT result = 0;

        if (message == WM_CREATE)
        {
            LONG_PTR window = reinterpret_cast<LONG_PTR>(
                reinterpret_cast<CREATESTRUCT *>(lParam)->lpCreateParams);

            SetWindowLongPtr(handle, GWLP_USERDATA, window);

            result = 1;
        }

        // For all i care you can create 90 more windows if you click the X button
        if (message == WM_CLOSE)
        {
            return 0;
        }

        Window *window = handle ? reinterpret_cast<Window *>(GetWindowLongPtr(handle, GWLP_USERDATA)) : nullptr;

        if (window)
        {
            if (!window->handleEvent(message, wParam, lParam))
            {
                result = DefWindowProcW(handle, message, wParam, lParam);
            }
        }

        else
        {
            result = DefWindowProcW(handle, message, wParam, lParam);
        }

        return result;
    }

    void Window::runMainLoop()
    {
        MSG message;

        while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }

    bool Window::handleEvent(UINT message, WPARAM wParam, LPARAM lParam)
    {
        return false;
    }
}