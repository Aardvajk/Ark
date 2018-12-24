#ifndef VIEWSPLITTER_H
#define VIEWSPLITTER_H

#include <QPxWidgets/QPxLineSplitter.h>

class ViewSplitter : public QPx::LineSplitter
{
    Q_OBJECT

public:
    ViewSplitter(Qt::Orientation orientation, QWidget *parent = nullptr);
};

#endif // VIEWSPLITTER_H
