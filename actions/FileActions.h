#ifndef FILEACTIONS_H
#define FILEACTIONS_H

#include <QPxEditor/QPxEditorFileActions.h>

class Model;
class ActionList;

class FileActions : public QPx::EditorFileActions
{
    Q_OBJECT

public:
    FileActions(Model *model, ActionList *actions, QWidget *parent);
};

#endif // FILEACTIONS_H
