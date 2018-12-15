#ifndef VIEWSEPARATOR_H
#define VIEWSEPARATOR_H

#include <QtWidgets/QWidget>

class ViewSeparator : public QWidget
{
    Q_OBJECT

public:
    ViewSeparator(Qt::Orientation orientation, QWidget *parent = nullptr);
};

#endif // VIEWSEPARATOR_H
