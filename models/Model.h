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
class TextureMap;

class Model : public QPx::AbstractEditorModel
{
    Q_OBJECT

public:
    Model(Graphics *graphics, QObject *parent = nullptr);

    void beginCommand(Command *command);

    QStringList properties() const;
    Property property(const QString &name) const;

    const QVector<Entity> &entities() const;

    const ModelBuffers *buffers() const;

    QVector<int> selected() const;
    QVector<int> objects() const;
    QVector<int> resources() const;

    TextureMap &textures();

    virtual bool clear() override;
    virtual bool open(const QString &path) override;
    virtual bool save(const QString &path) const override;

    virtual QString filter() const override;

public slots:
    void change();

signals:
    void changed();
    void reset();

private:
    pcx::aligned_store<32> cache;
};

#endif // MODEL_H
