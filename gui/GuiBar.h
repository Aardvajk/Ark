#ifndef GUIBAR_H
#define GUIBAR_H

#include <QtWidgets/QWidget>

#include <pcx/aligned_store.h>

class GuiBar : public QWidget
{
    Q_OBJECT

public:
    enum class Type
    {
        Small,
        Large
    };

    GuiBar(Qt::Orientation orientation, Type type, QWidget *parent = nullptr);

    void addWidget(QWidget *widget);
    void addSeparator();
    void addStretch();

    void insertWidget(int index, QWidget *widget);

    template<typename T> T *addTypedWidget(T *widget){ addWidget(widget); return widget; }

    Qt::Orientation orientation() const;
    Type type() const;
    QSize defaultButtonSize() const;

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    pcx::aligned_store<32> cache;
};

#endif // GUIBAR_H
