#ifndef VIEWCONTAINER_H
#define VIEWCONTAINER_H

#include <QtWidgets/QWidget>

namespace QPx
{

class Settings;

}

class ViewPanel;

class ViewContainer : public QWidget
{
    Q_OBJECT

public:
    explicit ViewContainer(QWidget *parent = nullptr);

    void addPanel(ViewPanel *panel);

    void saveState(QPx::Settings &settings) const;
    void restoreState(const QPx::Settings &settings);

public slots:
    void clear();

protected:
    virtual ViewPanel *createPanel(const QPx::Settings &settings) const = 0;

private:
    void saveContainerState(QWidget *widget, QPx::Settings &settings) const;
    QWidget *restoreContainerState(const QPx::Settings &settings);
};

template<typename T> class TypedViewContainer : public ViewContainer
{
public:
    TypedViewContainer(QWidget *parent = nullptr) : ViewContainer(parent) { }

protected:
    virtual ViewPanel *createPanel(const QPx::Settings &settings) const { return new T(settings); }
};

#endif // VIEWCONTAINER_H
