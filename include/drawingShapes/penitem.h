#ifndef PENITEM_H
#define PENITEM_H

#include <baseshapeitem.h>
#include <lineitem.h>

class PenItem : public BaseShapeItem {
public:
  PenItem(QPointF itemPos, QGraphicsScene *parent = nullptr);
  ~PenItem();
  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;
  bool getIsControlLineDrawn() const;
  void drawLineToNewPoint(QPointF p2);

protected:
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

  // BaseShapeItem interface
public:
  bool validateItemInsertion() override;
  void setLastPoint(QPointF newLastPoint) override;
  void checkIsPathClosed(QPointF &newPoint);
  void onPathClosed();

private:
  bool isDoubleClicked, shouldDrawControlLine, shouldDrawTempPath, isReleaseBtn,
      isPathClosed;
  QPointF endPoint;
  QLineF ctrlLine;
  QPainterPath path;
  QList<QPointF> pointList;
};

#endif // PENITEM_H
