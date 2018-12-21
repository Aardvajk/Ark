#ifndef VIEWCONTAINER_H
#define VIEWCONTAINER_H

#include <QtWidgets/QWidget>

namespace QPx
{

class Settings;

}

class ViewPanel;
class AbstractViewPanelFactory;

class ViewContainer : public QWidget
{
    Q_OBJECT

public:
    ViewContainer(ViewPanel *panel, QWidget *parent = nullptr);

    void clear();

    void saveState(QPx::Settings &settings) const;
    void restoreState(const QPx::Settings &settings, const AbstractViewPanelFactory &factory);
};

#endif // VIEWCONTAINER_H
