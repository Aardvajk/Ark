#ifndef CREATETOOL_H
#define CREATETOOL_H

#include "tools/Tool.h"

#include "core/Mesh.h"
#include "core/CreateMesh.h"

#include <GxMaths/GxVector.h>

#include <pcx/optional.h>

class ActionList;
class Model;

class CreateTool : public Tool
{
    Q_OBJECT

public:
    CreateTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent = nullptr);

    virtual QString name() const override;
    virtual QIcon icon() const override;

    virtual void addOptions(QPx::VBoxLayout *layout) const override;

public slots:
    virtual void mousePressed(ModelView *view, QMouseEvent *event) override;
    virtual void mouseMoved(ModelView *view, QMouseEvent *event) override;
    virtual void mouseReleased(ModelView *view, QMouseEvent *event) override;

    virtual void render(ModelView *view, Graphics *graphics, const RenderParams &params) override;

    virtual void focusLost() override;

private:
    Model *model;
    Gx::Vec3 start;
    CreateMesh::Type type;
    Mesh mesh;
};

#endif // CREATETOOL_H
