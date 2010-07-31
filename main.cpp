#include <QApplication>

#include "NaubScene.h"
#include "NaubView.h"
#include "NaubSim.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

  NaubScene scene;
	NaubView view(&scene);
	view.show();
	NaubSim sim(&scene);
	sim.start();

	return app.exec();
}
