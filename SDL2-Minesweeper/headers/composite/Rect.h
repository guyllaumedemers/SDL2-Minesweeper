
#ifndef INCLUDED_RECT
#define INCLUDED_RECT

namespace Toolset {
    struct Rect {
        float x = 0, y = 0, w = 0, h = 0;
        Rect(const Rect&) = delete;
        Rect(Rect&&) = delete;
        Rect() = delete;
        Rect(const float& x, const float& y, const float& w, const float& h);
        ~Rect() = default;
        Rect& operator=(const Rect&) = delete;
        Rect& operator=(Rect&&) = delete;
    };

    inline Rect::Rect(const float& x, const float& y, const float& w, const float& h) : x(x), y(y), w(w), h(h)
    {
    }
}
#endif
