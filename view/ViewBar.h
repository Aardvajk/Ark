#ifndef VIEWBAR_H
#define VIEWBAR_H

#include <QtWidgets/QWidget>

#include <pcx/aligned_store.h>

class ViewBar : public QWidget
{
    Q_OBJECT

public:
    enum class Type
    {
        Small,
        Large
    };

    ViewBar(Qt::Orientation orientation, Type type, QWidget *parent = nullptr);

    void addWidget(QWidget *widget);
    void addSeparator();
    void addStretch();

    template<typename T> T *addTypedWidget(T *widget){ addWidget(widget); return widget; }

    Qt::Orientation orientation() const;
    Type type() const;
    QSize defaultButtonSize() const;

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    pcx::aligned_store<32> cache;
};

#endif // VIEWBAR_H
