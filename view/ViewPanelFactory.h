#ifndef VIEWPANELFACTORY_H
#define VIEWPANELFACTORY_H

namespace QPx
{

class Settings;

}

class ViewPanel;

class AbstractViewPanelFactory
{
public:
    virtual ViewPanel *operator()(const QPx::Settings &settings) const = 0;
};

template<typename T> class ViewPanelFactory : public AbstractViewPanelFactory
{
public:
    virtual ViewPanel *operator()(const QPx::Settings &settings) const override { return new T(settings); }
};

#endif // VIEWPANELFACTORY_H
