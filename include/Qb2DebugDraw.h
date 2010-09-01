#ifndef QB2DEBUGDRAW_H
#define QB2DEBUGDRAW_H


#include "Prereqs.h"

#include <QtGui>

#include <Box2D/Box2D.h>



class Qb2DebugDraw : public b2DebugDraw {
public:
    Qb2DebugDraw();

    QPainter *_painter;

    void DrawPolygon (const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
        QPolygonF p;
        for (int i = 0; i < vertexCount; i++)
            p.append(toQPointF((vertices[i])));
        _painter->setPen(QPen( QBrush(toQColor(color)), 1.0f ));
        _painter->drawPolygon(p);
    }

    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
        QPolygonF p;
        for (int i = 0; i < vertexCount; i++)
            p.append(toQPointF((vertices[i])));
        _painter->setBrush( QBrush(toQColor(color)) );
        _painter->drawPolygon(p);
    }

    void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {
        _painter->setPen(QPen( QBrush(toQColor(color)), 1.0f ));
        _painter->drawEllipse( toQPointF(center), radius, radius );
    }

    void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) {
        Q_UNUSED(axis);
        QPointF c = toQPointF(center);
        _painter->setBrush( QBrush(toQColor(color)) );
        _painter->drawEllipse( c, radius, radius );
    }

    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
        _painter->setPen(QPen( QBrush(toQColor(color)), 1.0f ));
        _painter->drawLine( toQPointF(p1), toQPointF(p2) );
    }

    void DrawTransform(const b2Transform &xf) {
        QPointF p = toQPointF(xf.position);
        qreal r = xf.GetAngle();
        QPointF pr = QPointF( qCos(r)*2, qSin(r)*2 );
        QPointF p0 = p - pr;
        QPointF p1 = p + pr;
        _painter->setPen(QPen( QBrush(Qt::red), 1.0f ));
        _painter->drawLine( p0, p1 );
    }

protected:
    QPointF toQPointF(b2Vec2 vec) {
        return QPointF(vec.x * 100, vec.y * 100);
    }

    QColor toQColor(b2Color color) {
        return QColor::fromRgbF(color.r, color.g, color.b);
    }
};


class Qb2DebugDrawItem : public QGraphicsObject {
public:
    Qb2DebugDrawItem(b2World *world);

    b2World *_world;
    Qb2DebugDraw *_drawer;

    void timerEvent(QTimerEvent *);

    QRectF boundingRect() const {
        return QRectF(-300, -200, 600, 400);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        _drawer->_painter = painter;
        _world->DrawDebugData();
    }
};


#endif // QB2DEBUGDRAW_H

