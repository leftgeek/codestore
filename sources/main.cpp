#include <QtGui/QApplication>
#include "./headers/mainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec* codec = QTextCodec::codecForName("System");//获取系统编码
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    MainWindow mainWindow;
    mainWindow.resize(1000,600);
    mainWindow.setVisible(true);
    QDesktopWidget* desktop = QApplication::desktop();
    mainWindow.move((desktop->width() - mainWindow.width())/2, (desktop->height() - mainWindow.height())/2);

    return a.exec();
}
