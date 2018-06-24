// Copyright (c) 2018 Kosi Nwabueze
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <windraw/util/math.hpp>

namespace wd
{
	bool Size2::operator==(const Size2& other)
	{
		return x == other.x && y == other.y;	
	}

	bool Size2::operator!=(const Size2& other)
	{
		return !(operator==(other));
	}

	bool Size4::operator==(const Size4& other)
	{
		return x == other.x && y == other.y && w == other.w && z == other.z;
	}

	bool Size4::operator!=(const Size4& other)
	{
		return !(operator==(other));
	}
} // namespace wd