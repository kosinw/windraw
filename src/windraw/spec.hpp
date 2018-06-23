// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

namespace wd
{
    /**
	 * @brief Describes the width, height, and color depth of a window object.
	 * 
	 */
    class Spec
    {
        friend class wd::Window;

    public:
        /**
		 * @brief Construct a new Spec object
		 * 
		 * @param width Width of the window
		 * @param height Height of the window
		 * @param colorDepth Color depth of the window in bits per pixel (by default it is 32 bits per pixel)
		 */
        Spec(unsigned int width, unsigned int height, unsigned int colorDepth = 32);

    private:
        unsigned int m_Width;
        unsigned int m_Height;
        unsigned int m_ColorDepth;
    };

} // namespac wd