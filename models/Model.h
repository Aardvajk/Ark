#ifndef MODEL_H
#define MODEL_H

#include <QPxEditor/QPxAbstractEditorModel.h>

#include <QtCore/QList>

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

    const PropertyMap &properties() const;
    const QList<Entity> &entities() const;

    const ModelBuffers *buffers() const;

    virtual bool clear() override;
    virtual bool open(const QString &path) override;
    virtual bool save(const QString &path) const override;

    virtual QString filter() const override;

public slots:
    void change();

signals:
    void changed();

private:
    pcx::aligned_store<24> cache;
};

#endif // MODEL_H
