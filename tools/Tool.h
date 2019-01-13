#ifndef TOOL_H
#define TOOL_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>

class QPixmap;
class QMouseEvent;
class ModelView;
class Graphics;
class RenderParams;

class Tool : public QObject
{
    Q_OBJECT

public:
    explicit Tool(QObject *parent = nullptr);

    virtual QString name() const = 0;
    virtual QPixmap icon() const = 0;

signals:
    void selected(Tool *tool);

public slots:
    void select();

    void mousePressed(ModelView *view, QMouseEvent *event);
    void mouseMoved(ModelView *view, QMouseEvent *event);
    void mouseReleased(ModelView *view, QMouseEvent *event);

    void render(ModelView *view, Graphics *graphics, const RenderParams &params);
};

Q_DECLARE_METATYPE(Tool*)

#endif // TOOL_H
