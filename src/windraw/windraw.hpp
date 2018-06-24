// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <windraw/window/event.hpp>
#include <windraw/window/spec.hpp>
#include <windraw/window/style.hpp>
#include <windraw/window/window.hpp>

#include <windraw/util/math.hpp>

#if defined(WD_DIRECT2D_ENABLED)
#elif defined(WD_GDIPLUS_ENABLED)
#endif