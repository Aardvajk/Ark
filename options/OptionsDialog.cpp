#include "OptionsDialog.h"

#include "actions/ActionList.h"

#include "options/KeyboardOptionsWidget.h"
#include "options/LayoutOptionsWidget.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

OptionsDialog::OptionsDialog(ActionList *actions, QWidget *parent) : QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint), changes(false)
{
    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);

    tabs = new QTabWidget(this);
    layout->addWidget(tabs);

    addPanel("Keyboard", new KeyboardOptionsWidget(actions));
    addPanel("Layout", new LayoutOptionsWidget(actions));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);

    QPushButton *applyButton = new QPushButton(tr("Apply"));
    connect(applyButton, SIGNAL(clicked()), SLOT(apply()));

    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);
    buttonBox->addButton(applyButton, QDialogButtonBox::ActionRole);

    layout->addWidget(buttonBox);

    setWindowTitle("Options");

    connect(buttonBox, SIGNAL(accepted()), SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), SLOT(reject()));
}

void OptionsDialog::accept()
{
    apply();
    QDialog::accept();
}

void OptionsDialog::changed()
{
    changes = true;
}

void OptionsDialog::apply()
{
    if(changes)
    {
        emit commit();
        changes = false;
    }
}

void OptionsDialog::addPanel(const QString &title, OptionsWidget *panel)
{
    tabs->addTab(panel, title);

    connect(this, SIGNAL(commit()), panel, SLOT(commit()));
    connect(panel, SIGNAL(changed()), SLOT(changed()));
}

