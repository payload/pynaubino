#include <QApplication>
#include <QMainWindow>

#include "NaubScene.h"
#include "NaubView.h"

#include <QDebug>

class A { public: virtual void foo() { qDebug() << "A"; } };
class B : public A { public: virtual void foo() { qDebug() << "B"; } };

int main(int argc, char *argv[])
{
	qDebug() << "";
	QApplication app(argc, argv);
  NaubScene scene;
	NaubView view(&scene);
	view.show();
	scene.start();
	return app.exec();
}
