#ifndef MODEL_H
#define MODEL_H

#include <QPxEditor/QPxAbstractEditorModel.h>

class Model : public QPx::AbstractEditorModel
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);

    bool clear() override;
    bool open(const QString &path) override;
    bool save(const QString &path) const override;

    QString filter() const override;
};

#endif // MODEL_H
