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
	{
		/**
		 * @brief The type of event that has been triggered.
		 * 
		 */
		enum EventType
		{
			Close
		};

		EventType type;
	};
} // namespace wd