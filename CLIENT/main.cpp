#include <QApplication>
#include <QDir>
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set the working directory to the application's directory
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    LoginWindow w;
    w.show();
    return a.exec();
}
