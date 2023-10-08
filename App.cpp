#include <QApplication>
#include "Testing.h"
#include "GUI.h"

int main(int argc, char *argv[]) {
    Testing test;
    test.testAll();
    QApplication a(argc, argv);

    Repository repo=Repository("studenti.txt");
    Service serv=Service(repo);
    GUI gui=GUI(serv);
    gui.show();

    return QApplication::exec();
}
