#include "ResourcesView.h"

#include "models/Model.h"
#include "models/ResourcesModel.h"
#include "models/TextureMap.h"

#include "commands/CreateEntityCommand.h"
#include "commands/DeleteEntityCommand.h"

#include "entity/EntityFactory.h"

#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QFileDialog>

ResourcesView::ResourcesView(Model *model, QWidget *parent) : QTreeView(parent), model(model)
{
    header()->hide();

    resources = new ResourcesModel(model, this);

    setFrameStyle(QFrame::NoFrame);
    setModel(resources);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(contextMenuRequested(QPoint)));

    expandAll();
}

void ResourcesView::contextMenuRequested(const QPoint &pos)
{
    QMenu menu(this);

    if(true)
    {
        auto add = menu.addAction("Add...");
        connect(add, SIGNAL(triggered()), SLOT(addClicked()));
    }

    if(true)
    {
        auto del = menu.addAction("Delete");
        connect(del, SIGNAL(triggered()), SLOT(delClicked()));
    }

    menu.exec(mapToGlobal(pos));
}

void ResourcesView::addClicked()
{
    auto type = resources->itemType(selectionModel()->currentIndex());

    if(type != Entity::Type::Invalid)
    {
        auto base = model->property("Textures").value<QString>();
        if(!base.isEmpty())
        {
            auto path = QFileDialog::getOpenFileName(this, "Select Texture", base, "Images (*.png)");
            if(!path.isEmpty())
            {
                auto pix = QPixmap(path).scaledToHeight(64, Qt::SmoothTransformation);
                if(!pix.isNull())
                {
                    auto e = EntityFactory::create(type);
                    e.setProperty("Path", QFileInfo(path).fileName());
                    e.setProperty("Thumbnail", QVariant::fromValue(pix));

                    auto command = new CreateEntityCommand("Add", model);
                    command->create(e);

                    model->endCommand(command);
                }
            }
        }
    }
}

void ResourcesView::delClicked()
{
    auto index = resources->itemIndex(selectionModel()->currentIndex());
    if(index >= 0)
    {
        auto command = new DeleteEntityCommand("Delete", model);
        command->remove(index);

        model->endCommand(command);
    }
}

