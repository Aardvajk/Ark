#include "Tool.h"

Tool::Tool(QObject *parent) : QObject(parent)
{
}

void Tool::select()
{
    emit selected(this);
}
