#include "MainWindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("Ark");
    QApplication::setWindowIcon(QIcon(":/resources/images/ark.png"));

    QApplication::instance()->setProperty("ui-light", QColor(240, 240, 240));
    QApplication::instance()->setProperty("ui-dark", QColor(190, 190, 190));
    QApplication::instance()->setProperty("ui-text", QColor(100, 100, 100));

    MainWindow w;
    w.show();

    return a.exec();
}
