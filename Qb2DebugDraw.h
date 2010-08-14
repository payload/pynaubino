#ifndef QB2DEBUGDRAW_H
#define QB2DEBUGDRAW_H

#include <QtGui>
#include <Box2D.h>

class Qb2DebugDraw : public b2DebugDraw
{
public:
    Qb2DebugDraw();

    QPainter *painter;

    void DrawPolygon (const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
        QPolygonF p;
        for (int i = 0; i < vertexCount; i++)
            p.append(toQPointF((vertices[i])));
        painter->setPen(QPen( QBrush(toQColor(color)), 1.0f ));
        painter->drawPolygon(p);
    }

    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
        QPolygonF p;
        for (int i = 0; i < vertexCount; i++)
            p.append(toQPointF((vertices[i])));
        painter->setBrush( QBrush(toQColor(color)) );
        painter->drawPolygon(p);
    }

    void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {
        painter->setPen(QPen( QBrush(toQColor(color)), 1.0f ));
        painter->drawEllipse( toQPointF(center), radius, radius );
    }

    void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) {
        Q_UNUSED(axis);
        QPointF c = toQPointF(center);
        painter->setBrush( QBrush(toQColor(color)) );
        painter->drawEllipse( c, radius, radius );
    }

    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
        painter->setPen(QPen( QBrush(toQColor(color)), 1.0f ));
        painter->drawLine( toQPointF(p1), toQPointF(p2) );
    }

    void DrawTransform(const b2Transform &xf) {
        QPointF p = toQPointF(xf.position);
        qreal r = xf.GetAngle();
        QPointF pr = QPointF( qCos(r)*2, qSin(r)*2 );
        QPointF p0 = p - pr;
        QPointF p1 = p + pr;
        painter->setPen(QPen( QBrush(Qt::red), 1.0f ));
        painter->drawLine( p0, p1 );
    }

protected:
    QPointF toQPointF(b2Vec2 vec) {
        return QPointF(vec.x, vec.y);
    }

    QColor toQColor(b2Color color) {
        return QColor::fromRgbF(color.r, color.g, color.b);
    }
};

class Qb2DebugDrawItem : public QGraphicsItem
{
public:
    Qb2DebugDrawItem(b2World *world);

    b2World *world;
    Qb2DebugDraw *drawer;

    QRectF boundingRect() const {
        return QRectF(-300, -200, 600, 400);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        drawer->painter = painter;
        world->DrawDebugData();
    }
};

#endif // QB2DEBUGDRAW_H