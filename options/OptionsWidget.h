#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QtWidgets/QWidget>

class OptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWidget(QWidget *parent = nullptr);

signals:
    void changed();

public slots:
    virtual void commit() = 0;
};

#endif // OPTIONSWIDGET_H
