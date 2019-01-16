#ifndef TOOLOPTIONSVIEW_H
#define TOOLOPTIONSVIEW_H

#include <QtWidgets/QScrollArea>

namespace QPx
{

class VBoxLayout;

}

class Relay;
class QGroupBox;
class QVBoxLayout;
class Tool;

class ToolOptionsView : public QScrollArea
{
    Q_OBJECT

public:
    ToolOptionsView(Relay *relay, QWidget *parent = nullptr);

private slots:
    void toolChanged(Tool *tool);

private:
    QGroupBox *groupBox;
    QPx::VBoxLayout *groupLayout;
};

#endif // TOOLOPTIONSVIEW_H
