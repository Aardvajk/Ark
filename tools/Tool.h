#ifndef TOOL_H
#define TOOL_H

#include <QtCore/QObject>
#include <QtCore/QMetaType>

class QPixmap;

class Tool : public QObject
{
    Q_OBJECT

public:
    explicit Tool(QObject *parent = nullptr);

    virtual QString name() const = 0;
    virtual QPixmap icon() const = 0;

signals:
    void selected(Tool *tool);

public slots:
    void select();
};

Q_DECLARE_METATYPE(Tool*)

#endif // TOOL_H
