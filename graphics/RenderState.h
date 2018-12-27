#ifndef RENDERSTATE_H
#define RENDERSTATE_H

#include <pcx/non_copyable.h>

class Graphics;
class RenderParams;

class RenderState : public pcx::non_copyable
{
public:
    enum class Type
    {
        Preview,
        Color,
        Screen
    };

    RenderState(Type type, Graphics *graphics, const RenderParams &params);
    RenderState(RenderState &&r);
    ~RenderState();

    operator bool() const;

private:
    Graphics *graphics;
};

#endif // RENDERSTATE_H
