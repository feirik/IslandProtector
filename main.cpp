#include "game.h"

#include <QApplication>
#include <QDebug>

game *gameVar;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Freed on close of application or manually in QCoreApplication::quit() states
    gameVar = new (std::nothrow) game();

    if(gameVar == nullptr)
    {
        qDebug() << "Failed to allocate gameVar memory";
        return -1;
    }

    gameVar->show();

    gameVar->setAttribute(Qt::WA_DeleteOnClose);

    return a.exec();
}
