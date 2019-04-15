#ifndef RESOURCESVIEW_H
#define RESOURCESVIEW_H

#include <QtWidgets/QTreeView>

class Model;
class ResourcesModel;

class ResourcesView : public QTreeView
{
    Q_OBJECT

public:
    ResourcesView(Model *model, QWidget *parent = nullptr);

private slots:
    void contextMenuRequested(const QPoint &pos);

    void addClicked();
    void delClicked();

private:
    Model *model;
    ResourcesModel *resources;
};

#endif // RESOURCESVIEW_H
