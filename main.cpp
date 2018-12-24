#include "MainWindow.h"

#include "properties/custom/Selection.h"
#include "properties/custom/Mesh.h"

#include <QtWidgets/QApplication>

namespace
{

QColor grey(int value)
{
    return QColor(value, value, value);
}

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("Ark");
    QApplication::setWindowIcon(QIcon(":/resources/images/ark.png"));

    QApplication::instance()->setProperty("ui-panel", grey(230));
    QApplication::instance()->setProperty("ui-border", grey(190));
    QApplication::instance()->setProperty("ui-text", grey(100));
    QApplication::instance()->setProperty("ui-hover", grey(200));
    QApplication::instance()->setProperty("ui-hilight", grey(250));

    QMetaType::registerComparators<Selection>();
    QMetaType::registerComparators<Mesh>();
    qRegisterMetaTypeStreamOperators<Mesh>("Mesh");

//    QApplication::instance()->setProperty("ui-panel", grey(60));
//    QApplication::instance()->setProperty("ui-border", grey(16));
//    QApplication::instance()->setProperty("ui-text", grey(200));
//    QApplication::instance()->setProperty("ui-hover", grey(120));
//    QApplication::instance()->setProperty("ui-hilight", grey(32));

    MainWindow w;
    w.show();

    return a.exec();
}
