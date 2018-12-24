#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxMainWindow.h>

class ActionList;
class Model;

class MainWindow : public QPx::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private slots:
    void updateTitle();

private:
    QPx::ApplicationSettings settings;

    ActionList *actions;
    Model *model;
};

#endif // MAINWINDOW_H
