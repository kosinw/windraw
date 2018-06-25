// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <windraw/windraw.hpp>

using namespace wd;

int main(int, char **)
{
    Window window(Spec(700, 700), L"Best Window Ever.");

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
        }

        CanvasHandle canvas = window.getCanvasHandle();

        Size2 size;
        window.getDimensions(size);

        RectShape rect;

        std::cout << size.x << ", " << size.y << std::endl;

        rect.color             = ColorF(255, 0, 0);
        rect.dimensions.width  = 350;
        rect.dimensions.height = 350;
        rect.dimensions.x      = 0;
        rect.dimensions.y      = 0;
        
        canvas->beginDraw();

        canvas->clear();

        canvas->draw(rect);

        canvas->endDraw();

        if (event.type == wd::Event::Close)
        {
            window.destroy();
            break;
        }
    }

    return 0;
}