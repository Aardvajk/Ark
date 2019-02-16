#ifndef EXPORT_H
#define EXPORT_H

#include <QtCore/QString>

class Model;

bool exportModel(const QString &path, const Model *model);

#endif // EXPORT_H
