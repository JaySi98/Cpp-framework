#!/bin/sh

cmake --build build/ --target doxygen-docs
xdg-open docs/html/index.html 