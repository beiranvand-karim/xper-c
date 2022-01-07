#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include "baseitem.h"

class RectangleItem : public BaseItem {
public:
  RectangleItem(MainCanvas *canvas = nullptr, int x = 10, int y = 10,
                int width = 100, int height = 100);
  ~RectangleItem();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  // BaseItem interface
public:
  void setCanvas(MainCanvas *canvas) override;
  void setIsFill(bool fill) override;
  void setBorderWidth(int borderWidth) override;
  void setBoundWidth(int boundWidth) override;
  void setBoundHeight(int boundHeight) override;
  void setBrushColor(QColor color) override;
  void setPenColor(QColor color) override;
  void setPenWidth(int penWidth) override;
  int getXPos() override;
  void setXPos(int newXPos) override;
  int getYPos() override;
  void setYPos(int newYPos) override;
  void updateItem();

private:
  int radiusX, radiusY;
};

#endif // RECTANGLEITEM_H
