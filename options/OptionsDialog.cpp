#include "OptionsDialog.h"

#include "actions/ActionList.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

#include <QPxWidgets/QPxKeyboardOptionsWidget.h>

OptionsDialog::OptionsDialog(ActionList *actions, QWidget *parent) : QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint)
{
    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);

    QTabWidget *tabWidget = new QTabWidget(this);
    layout->addWidget(tabWidget);

    auto keyboardOptions = new QPx::KeyboardOptionsWidget(actions, this);
    tabWidget->addTab(keyboardOptions, "Keyboard");
    connect(this, SIGNAL(commit()), keyboardOptions, SLOT(commit()));

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
    emit commit();
    QDialog::accept();
}

void OptionsDialog::apply()
{
    emit commit();
}
