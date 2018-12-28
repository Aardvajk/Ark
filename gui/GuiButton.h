#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <QtWidgets/QWidget>

#include <pcx/aligned_store.h>

class QMenu;

class GuiButton : public QWidget
{
    Q_OBJECT

public:
    explicit GuiButton(QWidget *parent = nullptr);

    QMenu *setMenu(QMenu *menu);

    bool isChecked() const;

signals:
    void clicked();
    void toggled(bool state);

public slots:
    void setCheckable(bool state);
    void setChecked(bool state);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

    virtual bool event(QEvent *event) override;

private slots:
    void reset();

private:
    void buttonPressed();
    void buttonReleased();

    pcx::aligned_store<64> cache;
};

#endif // GUIBUTTON_H
