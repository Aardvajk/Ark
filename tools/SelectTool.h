#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "tools/Tool.h"

class ActionList;
class Model;

class SelectTool : public Tool
{
    Q_OBJECT

public:
    SelectTool(ActionList *actions, Model *model, QObject *parent = nullptr);

    virtual QString name() const override;
    virtual QPixmap icon() const override;
};

#endif // SELECTTOOL_H
