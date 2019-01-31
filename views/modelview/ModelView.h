#ifndef MODELVIEW_H
#define MODELVIEW_H

#include "views/modelview/ModelViewState.h"

#include "graphics/RenderParams.h"

#include <QGxGraphics/QGxGraphicsWidget.h>

#include <GxCore/GxTimer.h>

#include <GxMaths/GxColor.h>

#include <pcx/optional.h>

class Model;
class Graphics;
class RenderParams;

class ModelView : public QGx::GraphicsWidget
{
    Q_OBJECT

public:
    ModelView(Model *model, Graphics *graphics, const ModelViewState &state, QWidget *parent = nullptr);

    ModelViewState state() const;
    RenderParams renderParams() const;

signals:
    void mousePressed(ModelView *view, QMouseEvent *event);
    void mouseMoved(ModelView *view, QMouseEvent *event);
    void mouseReleased(ModelView *view, QMouseEvent *event);

    void render(ModelView *view, Graphics *graphics, const RenderParams &params);

public slots:
    void setState(const ModelViewState &value);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    virtual Gx::Matrix projectionMatrix(const RenderParams &params) const = 0;

    virtual void updateMousePos(QMouseEvent *event, const Gx::Vec2 &mousePos, const Gx::Vec2 &prevMousePos);
    virtual void updateCamera(float delta) = 0;

    virtual void render() = 0;

    virtual Gx::Color background() const = 0;

    virtual RenderParams beginRender();
    virtual void renderModel(const RenderParams &params);
    virtual void endRender(const RenderParams &params);

    Model *model;
    Graphics *graphics;
    ModelViewState st;

    QSet<Qt::MouseButton> buttons;
    QSet<int> keys;
    pcx::optional<Gx::Vec2> prevMousePos;

    Gx::Timer timer;
};

#endif // MODELVIEW_H
