#ifndef CUBIC_H
#define CUBIC_H

#include "basepoint.h"
#include "baseshapeitem.h"
#include "controlpoint.h"

class Cubic : public BaseShapeItem {
public:
  Cubic(QPointF startPoint, QGraphicsItem *parent = nullptr,
        QGraphicsScene *scene = nullptr);
  ~Cubic();

  void setShowPointsHandlers(bool showPoints);

  QPointF getCtrlPoint1() const;
  QPointF getCtrlPoint2() const;

  void setCtrlPoint1(QPointF newCtrlPoint1);
  void setCtrlPoint2(QPointF newCtrlPoint2);

  ControlPoint *getCtrlPointHandler1() const;
  void setCtrlPointHandler1(ControlPoint *newCtrlPointHandler1);

  ControlPoint *getCtrlPointHandler2() const;
  void setCtrlPointHandler2(ControlPoint *newCtrlPointHandler2);

  BasePoint *getSecondPointHandler() const;
  void setSecondPointHandler(BasePoint *newLastPointHandler);

  BasePoint *getFirstPointHandler() const;
  void setFirstPointHandler(BasePoint *newFirstPointHandler);

  void setShowCtrlPoint1(bool showCtrl1);
  void setShowCtrlPoint2(bool showCtrl1);

  // BaseShapeItem interface
public:
  void setFirstPoint(QPointF newItemPos) override;
  void setSecondPoint(QPointF newLastPoint) override;

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QPainterPath shape() const override;

private:
  QGraphicsScene *mainCanvas;
  QPointF ctrlPoint1, ctrlPoint2;
  BasePoint *firstPointHandler, *lastPointHandler;
  ControlPoint *ctrlPointHandler1, *ctrlPointHandler2;
  bool showPoints;
};

#endif // CUBIC_H
