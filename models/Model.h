#ifndef MODEL_H
#define MODEL_H

#include <QPxEditor/QPxAbstractEditorModel.h>

class ModelData;
class PropertyMap;
class Entity;

class Model : public QPx::AbstractEditorModel
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);
    virtual ~Model() override;

    const PropertyMap &properties() const;
    const QList<Entity> &entities() const;

    virtual bool clear() override;
    virtual bool open(const QString &path) override;
    virtual bool save(const QString &path) const override;

    virtual QString filter() const override;

signals:
    void changed();

private:
    ModelData *data;
};

#endif // MODEL_H
