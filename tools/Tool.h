#ifndef TOOL_H
#define TOOL_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>

class ModelView;
class QMouseEvent;
class Graphics;
class RenderParams;
class QPixmap;

class Tool : public QObject
{
    Q_OBJECT

public:
    explicit Tool(QObject *parent = nullptr);

    virtual QString name() const = 0;
    virtual QPixmap icon() const = 0;

signals:
    void select();

public slots:
    virtual void mousePressed(ModelView *view, QMouseEvent *event);
    virtual void mouseMoved(ModelView *view, QMouseEvent *event);
    virtual void mouseReleased(ModelView *view, QMouseEvent *event);

    virtual void render(ModelView *view, Graphics *graphics, const RenderParams &params);

    virtual void focusLost();
};

Q_DECLARE_METATYPE(Tool*)

#endif // TOOL_H
