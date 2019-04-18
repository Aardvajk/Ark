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

    QString text() const;
    QIcon icon() const;
    QMenu *menu() const;

    bool isChecked() const;

signals:
    void pressed();
    void clicked();
    void toggled(bool state);

public slots:
    void setText(const QString &text);
    void setIcon(const QIcon &icon);
    void setCheckable(bool state);
    void setChecked(bool state);
    void reset();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual bool event(QEvent *event) override;

private:
    void buttonPressed();
    void buttonReleased();

    pcx::aligned_store<64> cache;
};

#endif // GUIBUTTON_H
