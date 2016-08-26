#ifndef MATHCALCULATION_H
#define MATHCALCULATION_H

#include <QObject>

class MathCalculation : public QObject
{
    Q_OBJECT
public:
    explicit MathCalculation(QObject *parent = 0);

    float AngleToYDis(int angle,int compensationAngle,unsigned int compensationMode,float boardThick,float moldThick,float YZero);
    float AngleToLength(float m_ba);
    
signals:
    
public slots:
    
};

#endif // MATHCALCULATION_H
