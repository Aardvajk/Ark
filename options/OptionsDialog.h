#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QtWidgets/QDialog>

class ActionList;

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    OptionsDialog(ActionList *actions, QWidget *parent = nullptr);

signals:
    void commit();

public slots:
    virtual void accept() override;

    void changed();
    void apply();

private:
    bool changes;
};

#endif // OPTIONSDIALOG_H
