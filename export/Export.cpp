#include "Export.h"

#include "models/Model.h"

#include <pcx/datastream.h>

#include <fstream>

bool exportModel(const QString &path, const Model *model)
{
//    pcx::data_ofstream ds(path.toStdString());
//    if(!ds.is_open())
//    {
//        return false;
//    }

//    ds << 1 << 2 << 3;
//    return true;

    pcx::data_ifstream ds(path.toStdString());

    qDebug() << ds.get<int>();
    qDebug() << ds.get<int>();
    qDebug() << ds.get<int>();

    return true;
}
