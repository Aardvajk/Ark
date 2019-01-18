#ifndef MODELCACHE_H
#define MODELCACHE_H

#include <QtCore/QObject>

class Model;

class ModelCache : public QObject
{
    Q_OBJECT

public:
    ModelCache(Model *model, QObject *parent = nullptr);

public slots:
    void invalidate();

private:
    Model *model;

    struct Data
    {
    };

    mutable Data data;
    mutable bool valid;
};

#endif // MODELCACHE_H
