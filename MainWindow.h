#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxMainWindow.h>

class ActionList;
class Model;

class ViewContainer;

class MainWindow : public QPx::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private slots:
    void load();
    void save();

    void updateTitle();

private:
    QPx::ApplicationSettings settings;

    ActionList *actions;
    Model *model;

    ViewContainer *vc;
};

#endif // MAINWINDOW_H
