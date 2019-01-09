#ifndef LAYOUTDIAGRAM_H
#define LAYOUTDIAGRAM_H

#include <QtWidgets/QWidget>

#include <pcx/aligned_store.h>

class LayoutDiagram : public QWidget
{
    Q_OBJECT

public:
    explicit LayoutDiagram(QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual bool event(QEvent *event) override;

private:
    void button(QMouseEvent *event, bool down);

    pcx::aligned_store<64> cache;
};

#endif // LAYOUTDIAGRAM_H
