#ifndef GUISPLITTER_H
#define GUISPLITTER_H

#include <QPxWidgets/QPxLineSplitter.h>

class GuiSplitter : public QPx::LineSplitter
{
    Q_OBJECT

public:
    GuiSplitter(Qt::Orientation orientation, QWidget *parent = nullptr);
};

#endif // GUISPLITTER_H
