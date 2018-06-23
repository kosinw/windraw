// Copyright (c) 2018 Kosi Nwabueze
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#if defined(__MINGW32__) || defined(__GNUCXX__)
	#define WD_PLATFORM_MINGW 1
#elif defined(_MSC_VER)
	#define WD_PLATFORM_MSVC 1
	#define WD_DIRECT2D_ENABLED 1
	#define WD_GDIPLUS_ENABLED 1
#endif