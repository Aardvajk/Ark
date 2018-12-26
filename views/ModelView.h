#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QGxGraphics/QGxGraphicsWidget.h>

class Model;
class Graphics;

class ModelView : public QGx::GraphicsWidget
{
    Q_OBJECT

public:
    ModelView(Model *model, Graphics *graphics, QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Graphics *graphics;
};

#endif // MODELVIEW_H
