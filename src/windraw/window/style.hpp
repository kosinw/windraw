// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

namespace wd
{
    namespace Style
    {
        /**
         * @brief Bitfields that determine which styles a window would have.
         * 
         */
        enum : unsigned int
        {
            /**
             * @brief No styles will be applied to the window.
             * 
             */
            None = 0,

            /**
             * @brief The window will have a titlebar.
             * 
             */
            Titlebar = 1 << 0,

            /**
             * @brief The window will be able to be resized and have the minimize/maximize icon.
             * 
             */
            Resize = 1 << 1,

            /**
             * @brief The window will be able to be closed via an X button.
             * 
             */
            Close = 1 << 2,

            /**
             * @brief A combination of titlebar, resize, and close styles.
             * 
             */
            Default = Titlebar | Resize | Close
        };
    }
} // namespace wd