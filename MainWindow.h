#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPxCore/QPxSettings.h>

#include <QPxWidgets/QPxMainWindow.h>

class ActionList;
class FileActions;
class Model;
class GuiSplitter;
class GuiContainer;

class MainWindow : public QPx::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow() override;

protected:
    void customInterfaceAction(const QString &key, QWidget *parent);
    virtual void closeEvent(QCloseEvent *event) override;

private slots:
    void updateTitle();

private:
    QPx::ApplicationSettings settings;

    Model *model;

    ActionList *actions;
    FileActions *fileActions;

    GuiSplitter *split;
    GuiContainer *gcs[3];
};

#endif // MAINWINDOW_H
