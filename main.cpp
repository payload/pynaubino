#include <QtGui/QApplication>
#include "scene.h"
#include "view.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Scene scene;
    View view(&scene);
    view.show();

    return a.exec();
}
