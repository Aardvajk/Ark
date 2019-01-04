#ifndef GUICOMBOBOX_H
#define GUICOMBOBOX_H

#include <QtWidgets/QComboBox>

#include <pcx/aligned_store.h>

class GuiComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit GuiComboBox(QWidget *parent = nullptr);

    virtual void showPopup();
    virtual void hidePopup();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual bool event(QEvent *event) override;

private:
    pcx::aligned_store<16> cache;
};

#endif // GUICOMBOBOX_H
