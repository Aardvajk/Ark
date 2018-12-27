#ifndef MODELVIEWRELAY_H
#define MODELVIEWRELAY_H

#include <QtCore/QObject>

class ModelView;
class QMouseEvent;
class Graphics;
class RenderParams;

class ModelViewRelay : public QObject
{
    Q_OBJECT

public:
    explicit ModelViewRelay(QObject *parent = nullptr);

signals:
    void mousePressed(ModelView *view, QMouseEvent *event);
    void mouseMoved(ModelView *view, QMouseEvent *event);
    void mouseReleased(ModelView *view, QMouseEvent *event);

    void render(ModelView *view, Graphics *graphics, const RenderParams &params);

public slots:
    void mousePressedSlot(ModelView *view, QMouseEvent *event);
    void mouseMovedSlot(ModelView *view, QMouseEvent *event);
    void mouseReleasedSlot(ModelView *view, QMouseEvent *event);

    void renderSlot(ModelView *view, Graphics *graphics, const RenderParams &params);
};

#endif // MODELVIEWRELAY_H
