#ifndef RELAY_H
#define RELAY_H

#include <QtCore/QObject>

class Tool;
class ModelView;
class QMouseEvent;
class Graphics;
class RenderParams;

class Relay : public QObject
{
    Q_OBJECT

public:
    explicit Relay(QObject *parent = nullptr);

signals:
    void toolAdded(Tool *tool);
    void toolSelected(Tool *tool);

    void mousePressed(ModelView *view, QMouseEvent *event);
    void mouseMoved(ModelView *view, QMouseEvent *event);
    void mouseReleased(ModelView *view, QMouseEvent *event);

    void render(ModelView *view, Graphics *graphics, const RenderParams &params);
};

#endif // RELAY_H
