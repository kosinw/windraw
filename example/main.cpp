// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <windraw/windraw.hpp>

int main(int, char **)
{
    wd::Window window(wd::Spec(1280, 720), L"Best Window Ever.");

    while (window.isOpen())
    {
        wd::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case wd::Event::Close:
            {
                break;
            }

            case wd::Event::Resize:
            {
                std::cout << event.size.width
                          << ", "
                          << event.size.height
                          << std::endl;

                break;
            }

            case wd::Event::Move:
            {
                std::cout << event.position.x
                          << ", "
                          << event.position.y
                          << std::endl;
                          
                break;
            }
            }
        }
    }

    return 0;
}