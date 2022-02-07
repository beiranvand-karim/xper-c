#ifndef DRAWINGSTATES_H
#define DRAWINGSTATES_H

namespace CanvasState {
enum State { DRAW, MOVE, SCALE };

enum Shapes {
  NONE,
  RECTANGLE,
  LINE,
  POLYGON,
  ELLIPSE,
  IMAGE,
  TEXT,
  PEN,
  PENCIL,
  FRAME
};
}; // namespace DrawingStates

#endif // DRAWINGSTATES_H
