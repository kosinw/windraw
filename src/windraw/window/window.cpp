// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <queue>

#include <windraw/window/event.hpp>
#include <windraw/window/style.hpp>
#include <windraw/window/window.hpp>

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
        m_isDestroyed   = false;

        return true;
    }

    bool Window::destroy()
    {
        if (!m_isDestroyed)
        {
            if (m_windowHandle)
            {
                if (!DestroyWindow(m_windowHandle))
                {
                    return false;
                }

                numWindows--;
            }

            if (numWindows == 0)
            {
                if (!UnregisterClassW(wdClassName, GetModuleHandleW(nullptr)))
                {
                    return false;
                }
            }
        }

        m_isDestroyed = true;

        return true;
    }

    bool Window::getDimensions(Size2 &dimensions)
    {
        if (m_windowHandle)
        {
            RECT boundingBox;
            ZeroMemory(&boundingBox, sizeof(boundingBox));

            BOOL result = GetClientRect(m_windowHandle, &boundingBox);

            if (!result)
            {
                return false;
            }

            dimensions.w = static_cast<float>(boundingBox.right - boundingBox.left);
            dimensions.z = static_cast<float>(boundingBox.bottom - boundingBox.top);

            return true;
        }

        return false;
    }

    bool Window::getSize(Size2 &dimensions)
    {
        if (m_windowHandle)
        {
            RECT boundingBox;
            ZeroMemory(&boundingBox, sizeof(boundingBox));

            BOOL result = GetWindowRect(m_windowHandle, &boundingBox);

            if (!result)
            {
                return false;
            }

            dimensions.x = static_cast<float>(boundingBox.left);
            dimensions.y = static_cast<float>(boundingBox.top);

            return true;
        }

        return false;
    }

    bool Window::isOpen() const
    {
        return m_isInitialized && !m_isDestroyed;
    }

    bool Window::pollEvent(Event &event)
    {
        if (isOpen() && popEvent(event, false))
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

    WindowHandle Window::getWindowHandle() const
    {
        return m_windowHandle;
    }

    bool Window::registerWindowClass()
    {
        WNDCLASSW wndclass;
        ZeroMemory(&wndclass, sizeof(wndclass));

        wndclass.hInstance     = GetModuleHandle(nullptr);
        wndclass.lpszClassName = wdClassName;
        wndclass.style         = CS_VREDRAW | CS_HREDRAW;
        wndclass.lpfnWndProc   = &Window::windowProcedure;
        wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wndclass.hCursor       = LoadCursor(wndclass.hInstance, IDC_ARROW);
        wndclass.hIcon         = LoadIcon(wndclass.hInstance, IDI_APPLICATION);
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

        // For all i care you can create 90 more windows if you click the X button
        if (message == WM_CLOSE)
        {
            return 0;
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
        switch (message)
        {
        case WM_CLOSE:
        {
            Event ev;
            ev.type = Event::Close;
            m_eventQueue.push(ev);
            return true;
        }

        case WM_MOVE:
        {
            Size2 currentSize;
            getSize(currentSize);

            if (m_lastSize.xy != currentSize)
            {
                m_lastSize.xy = currentSize;

                Event ev;
                ev.type       = Event::Move;
                ev.position.x = m_lastSize.x;
                ev.position.y = m_lastSize.y;
                m_eventQueue.push(ev);
            }

            return true;
        }

        case WM_SIZE:
        {
            Size2 currentSize;
            getDimensions(currentSize);

            if (wParam != SIZE_MINIMIZED && m_lastSize.wz != currentSize)
            {
                m_lastSize.wz = currentSize;

                Event ev;
                ev.type        = Event::Resize;
                ev.size.width  = m_lastSize.width;
                ev.size.height = m_lastSize.height;
                m_eventQueue.push(ev);
            }

            return true;
        }
        }

        return false;
    }
}