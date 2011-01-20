#ifndef STDNOTATIONPAINTER_H
#define STDNOTATIONPAINTER_H

#include "painterbase.h"
#include "staffdata.h"

class Position;
class Guitar;
class QPainter;
class Note;
class KeySignature;

class StdNotationPainter : public PainterBase
{
public:
    StdNotationPainter(const StaffData& staffInfo, Position* position, Guitar* guitar, KeySignature* keySignature);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    int getDisplayPosition(const QString& noteName);
    void drawRest(QPainter* painter);
    int getOctaveDiff(const Note* currentNote, const int pitch) const;

    StaffData staffInfo;
    Position* position;
    Guitar* guitar;
    KeySignature* keySignature;
    static QFont musicFont;
};

#endif // STDNOTATIONPAINTER_H