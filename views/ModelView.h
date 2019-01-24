#ifndef MODELVIEW_H
#define MODELVIEW_H

#include "views/ModelViewState.h"

#include <QGxGraphics/QGxGraphicsWidget.h>

#include <GxCore/GxTimer.h>

#include <GxMaths/GxTransform.h>

class Model;
class Graphics;
class RenderParams;

class ModelView : public QGx::GraphicsWidget
{
    Q_OBJECT

public:
    ModelView(Model *model, Graphics *graphics, QWidget *parent = nullptr);

    ModelViewState state() const;
    RenderParams renderParams() const;

signals:
    void mousePressed(ModelView *view, QMouseEvent *event);
    void mouseMoved(ModelView *view, QMouseEvent *event);
    void mouseReleased(ModelView *view, QMouseEvent *event);

    void render(ModelView *view, Graphics *graphics, const RenderParams &params);

public slots:
    void setState(const ModelViewState &state);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void updateCamera(float delta);
    void renderModel();

    Model *model;
    Graphics *graphics;

    QSet<Qt::MouseButton> buttons;
    QSet<int> keys;

    Gx::Timer timer;
    Gx::Vec2 prevMousePos;

    ModelViewState st;
};

#endif // MODELVIEW_H
