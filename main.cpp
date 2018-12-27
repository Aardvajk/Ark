#include "MainWindow.h"

#include "properties/custom/Selection.h"
#include "properties/custom/Mesh.h"

#include <pcx/process.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

#include <exception>

namespace
{

inline QColor grey(int value){ return QColor(value, value, value); }

void setUI()
{
    QApplication::instance()->setProperty("gui-panel", grey(230));
    QApplication::instance()->setProperty("gui-border", grey(190));
    QApplication::instance()->setProperty("gui-text", grey(100));
    QApplication::instance()->setProperty("gui-hover", grey(200));
    QApplication::instance()->setProperty("gui-hilight", grey(250));
    QApplication::instance()->setProperty("gui-splitter", grey(175));
}

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("Ark");
    QApplication::setWindowIcon(QIcon(":/resources/images/ark.png"));

    setUI();

    QMetaType::registerComparators<Selection>();
    QMetaType::registerComparators<Mesh>();
    qRegisterMetaTypeStreamOperators<Mesh>("Mesh");

    try
    {
        if(pcx::process::execute("shc -v C:/Projects/Ark/Ark/previewvertex.txt C:/Projects/Ark/Ark/previewvertex.dat") ||
           pcx::process::execute("shc -v C:/Projects/Ark/Ark/colorvertex.txt C:/Projects/Ark/Ark/colorvertex.dat") ||
           pcx::process::execute("shc -v C:/Projects/Ark/Ark/screenvertex.txt C:/Projects/Ark/Ark/screenvertex.dat"))
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
