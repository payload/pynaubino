#ifndef NAUBVIEW_H
#define NAUBVIEW_H

#include "NaubScene.h"

#include <QGraphicsView>

class NaubView : public QGraphicsView {
 public:
	NaubView(NaubScene *scene);
};

#endif
