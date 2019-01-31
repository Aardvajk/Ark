#ifndef MODELVIEWSETTINGSWIDGET_H
#define MODELVIEWSETTINGSWIDGET_H

#include <QtWidgets/QFrame>

class ModelView;

class ModelViewSettingsWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ModelViewSettingsWidget(ModelView *view, QWidget *parent = nullptr);

private slots:
    void renderChanged(int index);

private:
    ModelView *view;
};

#endif // MODELVIEWSETTINGSWIDGET_H
