#include <QApplication>

#include "NaubScene.h"
#include "NaubView.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

  NaubScene scene;
	NaubView view(&scene);
	view.show();

	return app.exec();
}
