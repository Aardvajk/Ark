#include "OptionsDialog.h"

#include "actions/ActionList.h"

#include "options/KeyboardOptionsWidget.h"
#include "options/LayoutOptionsWidget.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

namespace
{

template<typename T, typename... Args> void addPanel(OptionsDialog *dialog, QTabWidget *tabWidget, const QString &title, Args&&... args)
{
    auto panel = new T(std::forward<Args>(args)..., dialog);
    tabWidget->addTab(panel, title);

    QObject::connect(dialog, SIGNAL(commit()), panel, SLOT(commit()));
    QObject::connect(panel, SIGNAL(changed()), dialog, SLOT(changed()));
}

}

OptionsDialog::OptionsDialog(ActionList *actions, QWidget *parent) : QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint), changes(false)
{
    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);

    QTabWidget *tabWidget = new QTabWidget(this);
    layout->addWidget(tabWidget);

    addPanel<LayoutOptionsWidget>(this, tabWidget, "Layout", actions);
    addPanel<KeyboardOptionsWidget>(this, tabWidget, "Keyboard", actions);

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
