#!/bin/sh

function build() {
    g++ src/snake.cpp -o snake.a -lsfml-graphics -lsfml-window -lsfml-system
}

build
