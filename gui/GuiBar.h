#ifndef GUIBAR_H
#define GUIBAR_H

#include <QtWidgets/QWidget>

class GuiBar : public QWidget
{
    Q_OBJECT

public:
    explicit GuiBar(QWidget *parent = nullptr);

    void addWidget(QWidget *widget);
    void addStretch();

    template<typename T> T *addTypedWidget(T *widget){ addWidget(widget); return widget; }

protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // GUIBAR_H
