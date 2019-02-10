#ifndef RENDERSTATE_H
#define RENDERSTATE_H

#include <pcx/non_copyable.h>
#include <pcx/flags.h>

class Graphics;
class RenderParams;

class RenderState : public pcx::non_copyable
{
public:
    enum class Type
    {
        Preview,
        Flat,
        Color,
        Screen,
        Ndc
    };

    enum class Flag
    {
        Invert = 1,
        NoZ = 2,
        NoZWrite = 4
    };

    using Flags = pcx::flags<Flag>;

    RenderState(Type type, Flags flags, Graphics *graphics, const RenderParams &params);
    RenderState(RenderState &&r);
    ~RenderState();

    operator bool() const;

private:
    Graphics *graphics;
};

template<> struct pcx_is_flag_enum<RenderState::Flag> : std::true_type { };

#endif // RENDERSTATE_H
