// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

namespace wd
{
    /**
	 * @brief Represent an event that can circulate in an event loop and can be polled for.
	 * 
	 */
    struct Event
    { /**
		 * @brief The type of event that has been triggered.
		 * 
		 */
        enum EventType
        {
            // Window events
            Close,
            Resize,
            Move,

            // General mouse events
            MouseDrag,
            MouseDown,
            MouseRelease,
        };

        struct MoveEvent
        {
            float x;
            float y;
        };

        struct ResizeEvent
        {
            float width;
            float height;
        };

        struct MouseEvent
        {
            enum
            {
                None   = 0,
                CTRL   = 1 << 0,
                SHIFT  = 1 << 1,
                LEFT   = 1 << 2,
                RIGHT  = 1 << 3,
                MIDDLE = 1 << 4
            };

            float        x;
            float        y;
            unsigned int mod;
        };

        EventType type;

        union {
            ResizeEvent size;
            MoveEvent   position;
            MouseEvent  mouse;
        };
    };
} // namespace wd