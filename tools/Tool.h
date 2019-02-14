#ifndef TOOL_H
#define TOOL_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>

namespace QPx
{

class Settings;
class VBoxLayout;

}

class QPixmap;
class QMouseEvent;
class ModelView;
class Graphics;
class RenderParams;
class Model;

class Tool : public QObject
{
    Q_OBJECT

public:
    Tool(QPx::Settings &settings, QObject *parent = nullptr);

    virtual QString name() const = 0;
    virtual QIcon icon() const = 0;

    virtual void addOptions(QPx::VBoxLayout *layout) const;

signals:
    void selected(Tool *tool);

public slots:
    void select();

    virtual void mousePressed(ModelView *view, QMouseEvent *event);
    virtual void mouseMoved(ModelView *view, QMouseEvent *event);
    virtual void mouseReleased(ModelView *view, QMouseEvent *event);

    virtual void render(ModelView *view, Graphics *graphics, const RenderParams &params);

    virtual void focusLost();

protected:
    void addGridSnapCheckbox(QPx::VBoxLayout *layout) const;
    QVariant gridValue(Model *model) const;

    QPx::Settings &settings;
};

Q_DECLARE_METATYPE(Tool*)

#endif // TOOL_H
