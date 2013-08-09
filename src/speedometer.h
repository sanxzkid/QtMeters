#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include "defines.h"

class Speedometer : public QWidget
{
    Q_OBJECT

public:
    explicit Speedometer(QWidget *parent = 0);
    ~Speedometer();

    void setParameter(QString title, float percentage, float startScale, float endScale, QString unit);
    void setTitle(QString title);
    void setPercentage(float percentage);
    void setScale(float startScale, float endEscale);
    void setUnit(QString unit);
    void addRange(float startRange, float endRange, QColor color);
    void setRangeStart(int index, float startRange);
    void setRangeEnd(int index, float endRange);
    void setRangeColor(int index, QColor color);

public slots:
    void setSize(int value);

private:
    void paintEvent(QPaintEvent *event);

    SpeedMeasure dynamic;
    Parameter parameter;
    QList<Range> listRange;

    QPainter painter;
    void calculateMeasure(int size);
    void drawTitle();
    void drawLabel();
    void drawDisplay();
    void drawMeter();
    void drawRange();
    void drawScale();
    void drawPointer();
};

#endif
