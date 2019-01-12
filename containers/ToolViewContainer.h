#ifndef TOOLVIEWCONTAINER_H
#define TOOLVIEWCONTAINER_H

#include <QtWidgets/QWidget>

class Relay;

class ToolViewContainer : public QWidget
{
    Q_OBJECT

public:
    ToolViewContainer(Relay *relay, QWidget *parent = nullptr);
};

#endif // TOOLVIEWCONTAINER_H
