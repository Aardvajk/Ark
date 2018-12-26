#ifndef GUIBARBUTTON_H
#define GUIBARBUTTON_H

#include <QtWidgets/QWidget>

#include <pcx/aligned_store.h>

class GuiBar;
class QMenu;

class GuiBarButton : public QWidget
{
    Q_OBJECT

public:
    GuiBarButton(const QPixmap &pixmap, GuiBar *parent);
    GuiBarButton(const QString &text, const QPixmap &pixmap, GuiBar *parent);
    GuiBarButton(QMenu *menu, const QPixmap &pixmap, GuiBar *parent);

    void setCheckable(bool state);

    bool isCheckable() const;
    bool isChecked() const;

signals:
    void clicked();
    void toggled(bool state);

public slots:
    void click();
    void setChecked(bool state);
    void toggle();

protected:
    virtual bool event(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void reset();

private:
    void buttonPressed();
    void buttonReleased();

    pcx::aligned_store<88> cache;
};

#endif // GUIBARBUTTON_H
