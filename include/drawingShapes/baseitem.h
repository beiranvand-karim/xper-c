#ifndef BASEITEM_H
#define BASEITEM_H

#include <QBrush>
#include <QColor>
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>

class MainCanvas;
class BaseItem : public QGraphicsItem {

public:
  virtual ~BaseItem() = default;
  virtual void setCanvas(MainCanvas *canvas) = 0;
  virtual void setIsFill(bool fill) = 0;
  virtual void setBorderWidth(int borderWidth) = 0;
  virtual void setBoundWidth(int boundWidth) = 0;
  virtual void setBoundHeight(int boundHeight) = 0;
  virtual void setBrushColor(QColor color) = 0;
  virtual void setPenColor(const QColor penColor) = 0;
  virtual void setPenWidth(int penWidth) = 0;
  virtual int getXPos() = 0;
  virtual void setXPos(int newXPos) = 0;
  virtual int getYPos() = 0;
  virtual void setYPos(int newYPos) = 0;

protected:
  int id, xPos, yPos, boundWidth, boundHeight, borderWidth, penWidth;
  QPen *pen;
  QBrush *brush;
  bool isFill;
  MainCanvas *canvas;
};

#endif // BASEITEM_H
