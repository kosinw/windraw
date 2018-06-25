// Copyright (c) 2018 Kosi Nwabueze
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <windraw/windraw.hpp>

using namespace wd;

int main(int, char **)
{
    Window window(Spec(750, 750), L"Best Window Ever.", Style::Close);

    Size2 dimensions;
    window.getDimensions(dimensions);

    CanvasHandle canvas = window.getCanvasHandle();

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Resize:
            {
                dimensions = Size2(event.size.width, event.size.height);
                break;
            }

            case Event::Close:
            {
                window.destroy();
                break;
            }
            }
        }

        CanvasHandle canvas = window.getCanvasHandle();

        if (canvas)
        {
            RectShape rect;

            rect.color             = ColorF(1.0f, 0, 0);
            rect.dimensions.width  = 250;
            rect.dimensions.height = 250;
            rect.dimensions.x      = (dimensions.width - 250) / 2;
            rect.dimensions.y      = (dimensions.height - 250) / 2;

            canvas->beginDraw();

            canvas->clear();

            canvas->draw(rect);

            canvas->endDraw();
        }
    }

    return 0;
}