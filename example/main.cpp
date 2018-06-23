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
        }
    }

    return 0;
}