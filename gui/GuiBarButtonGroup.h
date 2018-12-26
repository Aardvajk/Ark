#ifndef GUIBARBUTTONGROUP_H
#define GUIBARBUTTONGROUP_H

#include <QtCore/QObject>

#include <pcx/aligned_store.h>

class GuiBarButton;

class GuiBarButtonGroup : public QObject
{
    Q_OBJECT

public:
    explicit GuiBarButtonGroup(QObject *parent = nullptr);

    GuiBarButton *addButton(GuiBarButton *button);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event) override;

private slots:
    void buttonDestroyed(QObject *button);
    void buttonToggled(bool state);

private:
    pcx::aligned_store<8> cache;
};

#endif // GUIBARBUTTONGROUP_H
