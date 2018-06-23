// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <Windows.h>
#include <queue>
#include <string>

#include <windraw/math.hpp>
#include <windraw/spec.hpp>
#include <windraw/style.hpp>

namespace wd
{
    class GraphicsContext;
    struct Event;

    using WindowHandle = HWND;

    typedef GraphicsContext *GraphicsHandle;

    /**
	 * @brief A wrapper for Win32 API Window creation and initialization,
	 * Windows event loop handling and propagation, and Window destruction.
	 * 
	 */
    class Window
    {
    public:
        using Style = unsigned int;

    public:
        /**
		 * @brief Construct a new Window object.
		 * 
		 * @param spec Dimensions + color depth of window
		 * @param style Window styles for the window
		 * @param title Title that will be displayed on window
		 */
        Window(Spec spec, Style style, const std::wstring &title);

        /**
		 * @brief Construct a new Window object from a window handle.
		 * 
		 * @param handle HWND that will become the handle for the window class
		 */
        Window(WindowHandle handle);

        /**
		 * @brief Construct a new Window object with default properties.
		 * 
		 */
        Window();

        Window &operator=(const Window &) = delete;
        Window &operator=(Window &&) = delete;
        Window(const Window &)       = delete;
        Window(Window &&)            = delete;

        /**
		 * @brief Creates a window handle and shows it,
		 * if the window class is not initialized, it is initialized here.
		 * 
		 * @return true When initialization is successful.
		 * @return false When the creation of the window or window class is unsuccessful.
		 */
        bool init();

        /**
		 * @brief Destroys the window handle if it was initialized,
		 * also destroys the GraphicsContext if it was initialized.
		 * 
		 * @return true When destruction is successful.
		 * @return false When the destruction of the window or graphics context is unsucessful.
		 */
        bool destroy();

        /**
		 * @brief Return the dimensions of the window.
		 * 
		 * @return Size4 x, y, width, and height of the window.
		 */
        Size4 getDimensions();

        /**
		 * @brief Return the visibility of the window.
		 * 
		 * @return true If the window is being displayed.
		 * @return false If the window is not being displayed.
		 */
        bool isVisible();

        /**
		 * @brief Returns if the window is still open.
		 * 
		 * @return true If the window hasn't been destroyed.
		 * @return false If the window has been destroyed.
		 */
        bool isOpen() const;

        /**
		 * @brief Attempts to hide the window.
		 * 
		 * @return true If the window was hidden successfully.
		 * @return false If the window wasn't hidden successfully.
		 */
        bool hide();

        /**
		 * @brief Attempts to show the window.
		 * 
		 * @return true If the window was shown sucessfully.
		 * @return false If the window wasn't shown sucessfully.
		 */
        bool show();

        /**
		 * @brief Checks the event queue and returns the event on the top.
		 * 
		 * @param event Outputs event type and args 
		 * @return true If there are more events left in the queue.
		 * @return false If there are no more events left in the queue.
		 */
        bool pollEvent(Event &event);

		/**
		 * @brief Checks the event queue. If blocking, then wait until next event. If not, then just continue execution.
		 * 
		 * @param event Outputs event type and args
		 * @param blocking Sets operation to blocking or non-blocking
		 * @return true If there are any more events in the queue.
		 * @return false If there aren't any more events in the queue.
		 */
        bool popEvent(Event &event, bool blocking);

    private:
        WindowHandle      m_windowHandle   = nullptr;
        GraphicsHandle    m_graphicsHandle = nullptr;
        LONG_PTR          m_lastCallback   = 0;
        Style             m_windowStyles   = 0;
        Spec              m_windowSpec     = { 1280, 720, 32 };
        bool              m_isVisible      = true;
        bool              m_isInitialized  = false;
        std::queue<Event> m_eventQueue;
    };
} // namespace wd