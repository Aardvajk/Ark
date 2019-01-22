#ifndef MODEL_H
#define MODEL_H

#include "properties/Property.h"

#include <QPxEditor/QPxAbstractEditorModel.h>

#include <QtCore/QVector>

#include <pcx/aligned_store.h>

class Graphics;
class ModelData;
class PropertyMap;
class Entity;
class ModelBuffers;
class Command;

class Model : public QPx::AbstractEditorModel
{
    Q_OBJECT

public:
    Model(Graphics *graphics, QObject *parent = nullptr);

    void beginCommand(Command *command);

    QStringList properties() const;
    Property property(const QString &name) const;
    void addProperty(const QString &name, const Property &property);
    template<typename T> void setProperty(const QString &name, const T &value){ setPropertyVariant(name, QVariant::fromValue(value)); }

    const QVector<Entity> &entities() const;

    Entity &entity(int index);
    Entity entity(int index) const;

    const ModelBuffers *buffers() const;

    QVector<int> selected() const;

    virtual bool clear() override;
    virtual bool open(const QString &path) override;
    virtual bool save(const QString &path) const override;

    virtual QString filter() const override;

public slots:
    void change();

signals:
    void changed();

private:
    void setPropertyVariant(const QString &name, const QVariant &value);

    pcx::aligned_store<24> cache;
};

template<> void Model::setProperty<QVariant>(const QString &name, const QVariant &value){ setPropertyVariant(name, value); }

#endif // MODEL_H
