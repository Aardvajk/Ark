#ifndef TOOLLIST_H
#define TOOLLIST_H

#include <QtCore/QObject>
#include <QtCore/QList>

class Relay;
class Tool;

class ToolList : public QObject
{
    Q_OBJECT

public:
    ToolList(Relay *relay, QObject *parent = nullptr);

    Tool *addTool(Tool *tool);

signals:
    void toolAdded(Tool *tool);

private:
    Relay *relay;
    QList<Tool*> data;
};

#endif // TOOLLIST_H
