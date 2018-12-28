#ifndef GUIBUTTONGROUP_H
#define GUIBUTTONGROUP_H

#include <QtCore/QObject>

#include <pcx/aligned_store.h>

class GuiButton;

class GuiButtonGroup : public QObject
{
    Q_OBJECT

public:
    explicit GuiButtonGroup(QObject *parent = nullptr);

    GuiButton *addButton(GuiButton *button);

    int count() const;

protected:
    virtual bool eventFilter(QObject *object, QEvent *event) override;

private slots:
    void buttonDestroyed(QObject *button);
    void buttonToggled(bool state);

private:
    pcx::aligned_store<8> cache;
};

#endif // GUIBUTTONGROUP_H
