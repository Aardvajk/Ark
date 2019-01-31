#include "Render.h"

const char *Render::toString(Render::Type type)
{
    static const char *s[] = { "Wireframe", "Flat", "Textured", "None" };

    return s[static_cast<int>(type)];
}
