#ifndef MODELCACHE_H
#define MODELCACHE_H

#include <QtCore/QObject>

class Model;

class ModelCache : public QObject
{
    Q_OBJECT

public:
    ModelCache(Model *model, QObject *parent = nullptr);

    QVector<int> selected() const;

public slots:
    void invalidate();

private:
    void refresh() const;

    Model *model;

    struct Data
    {
        QVector<int> selected;
    };

    mutable Data data;
    mutable bool valid;
};

#endif // MODELCACHE_H
