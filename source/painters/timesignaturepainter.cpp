#include "timesignaturepainter.h"

#include <powertabdocument/timesignature.h>
#include <powertabdocument/staff.h>
#include <painters/musicfont.h>

#include <QMessageBox>
#include <QFont>
#include <QPainter>

TimeSignaturePainter::TimeSignaturePainter(const StaffData& staffInformation, const TimeSignature& signature) :
    staffInfo(staffInformation),
    timeSignature(signature)
{
    init();
}

void TimeSignaturePainter::init()
{
    bounds = QRectF(0, 0, timeSignature.GetWidth(), staffInfo.getStdNotationStaffSize());
}

void TimeSignaturePainter::mousePressEvent(QGraphicsSceneMouseEvent *)
{
}

void TimeSignaturePainter::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    QMessageBox message;
    message.setText("Time Signature");
    message.exec();
}

void TimeSignaturePainter::mouseMoveEvent(QGraphicsSceneMouseEvent *)
{
}

void TimeSignaturePainter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (timeSignature.IsCommonTime() || timeSignature.IsCutTime())
    {
        MusicFont musicFont;
        QFont displayFont = musicFont.getFont();
        displayFont.setPixelSize(25);
        painter->setFont(displayFont);

        QChar symbol;
        if (timeSignature.IsCommonTime())
        {
            symbol = musicFont.getSymbol(MusicFont::CommonTime);
        }
        else
        {
            symbol = musicFont.getSymbol(MusicFont::CutTime);
        }

        painter->drawText(0, 2 * Staff::STD_NOTATION_LINE_SPACING, symbol);
    }
    else
    {
        drawNumber(painter, 2 * Staff::STD_NOTATION_LINE_SPACING, timeSignature.GetBeatsPerMeasure());
        drawNumber(painter, 4 * Staff::STD_NOTATION_LINE_SPACING, timeSignature.GetBeatAmount());
    }
}

void TimeSignaturePainter::drawNumber(QPainter* painter, const double y, const quint8 number) const
{
    QString text = QString().setNum(number);

    MusicFont musicFont;
    QFont displayFont = musicFont.getFont();
    displayFont.setPixelSize(27);

    const double width = QFontMetricsF(displayFont).width(text);
    const double x = centerItem(0, timeSignature.GetWidth(), width);

    painter->setFont(displayFont);
    painter->drawText(x, y, text);
}
