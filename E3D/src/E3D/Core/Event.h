#pragma once

struct Event {
    enum Type { Keyboard, Resize, Close, Mouse };

    Type type;

    union {
        struct {
            int key, scancode, action, mods;
        } keyData;

        struct {
            int width, height;
        } resizeData;

        struct {
            double x, y;
        } mouseData;
    };

    bool handled = false;
    void MarkAsHandled() { handled = true; }
};
