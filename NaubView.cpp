#include "NaubView.h"

#include <QPainter>

NaubView::NaubView(NaubScene *scene) {
	setScene(scene);
	setRenderHint(QPainter::Antialiasing);
}
