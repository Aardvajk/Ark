#include "CopyEntitiesCommand.h"

#include "models/ModelData.h"

#include <QtCore/QMimeData>

#include <QtGui/QClipboard>

#include <QtWidgets/QApplication>

CopyEntitiesCommand::CopyEntitiesCommand(const QString &name, Model *model) : Command(name, model)
{
}

bool CopyEntitiesCommand::isValid() const
{
    return !v.isEmpty();
}

bool CopyEntitiesCommand::modifiesPersistentState() const
{
    return false;
}

void CopyEntitiesCommand::undo()
{
}

void CopyEntitiesCommand::redo()
{
    QByteArray bytes;
    QDataStream ds(&bytes, QIODevice::WriteOnly);

    ds << v.count();
    for(int i: v)
    {
        ds << data->entities[i];
    }

    auto mime = new QMimeData();
    mime->setData("aardvajk/ark/entities", bytes);

    QApplication::clipboard()->setMimeData(mime);
}

void CopyEntitiesCommand::copy(const QVector<int> &indices)
{
    v = indices;
}
