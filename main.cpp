#include "MainWindow.h"

#include "core/Element.h"
#include "core/Render.h"
#include "core/Mesh.h"

#include "maths/Projection.h"

#include <QGxMaths/QGxMathsMetatypes.h>

#include <pcx/process.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

#include <exception>

namespace
{

inline QColor grey(int value){ return QColor(value, value, value); }

void setGui()
{
    QApplication::instance()->setProperty("gui-panel-color", grey(220));
    QApplication::instance()->setProperty("gui-border-color", grey(160));
    QApplication::instance()->setProperty("gui-text-color", grey(60));
    QApplication::instance()->setProperty("gui-hover-color", grey(190));
    QApplication::instance()->setProperty("gui-hilight-color", grey(250));

    QApplication::instance()->setProperty("gui-bar-height", 20);
    QApplication::instance()->setProperty("gui-bar-icon-size", 16);

    QApplication::instance()->setProperty("gui-tool-width", 70);
    QApplication::instance()->setProperty("gui-tool-height", 52);
    QApplication::instance()->setProperty("gui-tool-icon-size", 24);
    QApplication::instance()->setProperty("gui-tool-font-size", 7);
}

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("Ark");
    QApplication::setWindowIcon(QIcon(":/resources/images/ark.png"));

    setGui();

    QGx::registerMathStreamOperators();

    qRegisterMetaTypeStreamOperators<Element::Type>("Element::Type");
    qRegisterMetaTypeStreamOperators<Projection::Type>("Projection::Type");
    qRegisterMetaTypeStreamOperators<Projection::Direction>("Projection::Direction");
    qRegisterMetaTypeStreamOperators<Render::Type>("Render::Type");
    qRegisterMetaTypeStreamOperators<Mesh>("Mesh");

    try
    {
        if(pcx::process::execute("shc -v C:/Projects/Ark/Ark/previewvertex.txt C:/Projects/Ark/Ark/previewvertex.dat") ||
           pcx::process::execute("shc -v C:/Projects/Ark/Ark/colorvertex.txt C:/Projects/Ark/Ark/colorvertex.dat") ||
           pcx::process::execute("shc -v C:/Projects/Ark/Ark/screenvertex.txt C:/Projects/Ark/Ark/screenvertex.dat") ||
           pcx::process::execute("shc -v C:/Projects/Ark/Ark/ndcvertex.txt C:/Projects/Ark/Ark/ndcvertex.dat"))
        {
            throw std::runtime_error("unable to compile shader");
        }

        MainWindow w;
        w.show();

        return a.exec();
    }

    catch(const std::exception &e)
    {
        QMessageBox::critical(nullptr, "Error", e.what(), QMessageBox::Ok);
        return -1;
    }
}
