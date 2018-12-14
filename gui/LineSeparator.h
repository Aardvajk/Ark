#ifndef LINESEPARATOR_H
#define LINESEPARATOR_H

#include <QtWidgets/QWidget>

class LineSeparator : public QWidget
{
    Q_OBJECT

public:
    LineSeparator(Qt::Orientation orientation, QWidget *parent = nullptr);
};

#endif // LINESEPARATOR_H
