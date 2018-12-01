#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxMainWindow.h>

class ActionList;

class MainWindow : public QPx::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private:
    QPx::ApplicationSettings settings;
    ActionList *actions;
};

#endif // MAINWINDOW_H
