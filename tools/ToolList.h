#ifndef TOOLLIST_H
#define TOOLLIST_H

#include <QtCore/QObject>

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

private slots:
    void toolSelected(Tool *tool);

private:
    Relay *relay;
    Tool *curr;
};

#endif // TOOLLIST_H
