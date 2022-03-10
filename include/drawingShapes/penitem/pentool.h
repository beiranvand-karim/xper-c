#ifndef CUBICBEZIER_H
#define CUBICBEZIER_H

#include "cubic.h"

#include <basepoint.h>
#include <baseshapeitem.h>
#include <lineitem.h>

class PenTool : public BaseShapeItem {
public:
  PenTool(QPointF itemPos, QGraphicsScene *parent = nullptr);
  ~PenTool();

  enum PenToolState { StraightLine, CubicBezier };

  void setPenState(QPointF pos, bool mousePressed);
  void draw(QPointF);
  void drawStraightLine(QPointF p2);
  void drawCubic(QPointF p2);

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  QPainterPath shape() const override;

protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
  // BaseShapeItem interface
  bool validateItemInsertion() override;

  // protected function
  void prepareToDraw();
  void initControlPoints();
  void setPointInSymmetry(ControlPoint *firstPoint, ControlPoint *secondPoint);

private:
  PenToolState penState;
  bool isDoubleClicked, stopDrawing;
  QVector<Cubic *> cubicList;
  QPointF ctrlPoint1, ctrlPoint2, symmetryOfCtrlPoint_1;
};

#endif // CUBICBEZIER_H_H
