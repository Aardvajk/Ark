#ifndef MOVETOOL_H
#define MOVETOOL_H

#include "tools/Tool.h"

class ActionList;
class Model;

class MoveTool : public Tool
{
    Q_OBJECT

public:
    MoveTool(ActionList *actions, Model *model, QPx::Settings &settings, QObject *parent = nullptr);

    virtual QString name() const override;
    virtual QIcon icon() const override;
};

#endif // MOVETOOL_H
