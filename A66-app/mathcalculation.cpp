#include "mathcalculation.h"
#include "global.h"
#include "math.h"

#define PI 3.1415926

MathCalculation::MathCalculation(QObject *parent) :
    QObject(parent)
{
}
/************************************************
函数名：AngleToYDis()
功  能：角度转换Y坐标
参  数：void
返回值：void
************************************************/
float AngleToLength(float m_ba);
float MathCalculation::AngleToYDis(int angle,int compensationAngle,unsigned int compensationMode,float boardThick,float moldThick,float YZero)
{
   // uint8 m_No = (uint8)DisMenu[MultiStepProgram].Dis[MspMoldNum].fword;//模具号
    float m_a =  angle ;     //角度
    float m_ac = compensationAngle; //补偿值
    unsigned int m_com =   compensationMode;  //补偿方式
    float p_t = boardThick;//DisMenu[MultiStepProgram].Dis[MspPancel].fword; //程序中的板厚
    float m_t = moldThick; // sMold[m_No-1].PancelThickness;//模具库中的板料厚度

    float m_y;
    float EspYm;

    if(m_com == 0)  //角度补偿
    {
        m_y =   2* AngleToLength(m_a) - AngleToLength(m_a-m_ac);
        EspYm =  m_y + YZero;


    }
    else            //深度补偿
    {
     //   m_y =   AngleToDepthV1(m_a,m_No) + (m_t-p_t)+ m_ac;

        EspYm=  m_y ;

    }
    return EspYm;
}
/************************************************
函数名：AngleToYDis()
功  能：角度转换Y方向滑块进深
参  数：void
返回值：void
************************************************/
float MathCalculation::AngleToLength(float m_ba)
{
    float sin_value,cos_value,tan_value,temp,result;
    float ma =CurrentLowerMoldTemp.Angle*PI/(180.0*4);// MoldLib[(uint8)DisMenu[MultiStepProgram].Dis[MspMoldNum].fword - 1].MoldAngle *PI/(180.0*4);//下模角度的1/4
    float ba,m_R,m_k,m_t,m_h;
    float C,q;
    float m_l = CurrentProgramTemp.BroadWideth;//DisMenu[MultiStepProgram].Dis[MspLength].fword;//板宽
    float m_s = 1;//DisMenu[SystemSetting].Dis[Strength].fword;  //框架强度
    float m_v = CurrentLowerMoldTemp.D_V; //MoldLib[(uint8)DisMenu[MultiStepProgram].Dis[MspMoldNum].fword - 1].MoldOpening_W;
    float m_tt =CurrentProgramTemp.BroadThick; //DisMenu[MultiStepProgram].Dis[MspPancel].fword;
    float m_r = CurrentLowerMoldTemp.Radius;//MoldLib[(uint8)DisMenu[MultiStepProgram].Dis[MspMoldNum].fword - 1].MoldRadius;
//	float m_ba = DisMenu[EachStepProgram].Dis[EspAngle].fword;
    float m_e = CurrentMaterialTemp.EMold;//MaterLib[(uint8)DisMenu[MultiStepProgram].Dis[MspMaterial].fword - 1].E_Module;
    float m_o = CurrentMaterialTemp.StrengthFactor;// MaterLib[(uint8)DisMenu[MultiStepProgram].Dis[MspMaterial].fword - 1].TensileStrength;

    if (m_ba >= 180)    return 0-m_tt;
    else
    {
        m_t=m_v/8;
        temp = 2*m_v/m_t;
        if(temp <= 10)
        {
            C = 1.3;
        }
        else if(temp < 15)
        {
            C = (1.2 + 1.3)/2;
        }
        else if(temp < 20)
        {
            C = 1.2;
        }
        else if(temp < 25)
        {
            C = (1.2+1.15)/2;
        }
        else if(temp < 30)
        {
            C = 1.15;
        }
        else if(temp < 40)
        {
            C = (1.15 + 1.1)/2;
        }
        else
        {
            C = 1.1-((temp-40)*0.1);
        }
        m_k = (0.17 - 0.125)/(8.75 - 7)* (m_v/m_t - 7)+0.125;
        m_R = m_k*(2*m_r * tanf(ma*2)+m_v-2*m_r*cosf(m_ba*PI/360));
        temp = m_R /m_t;
        if(temp <= 0.1)
            q = 0.32;
        else if(temp <= 0.25)
        {
            q = (temp - 0.1) * (0.35 - 0.32)/0.15 + 0.32;
        }
        else if(temp <= 0.5)
            q = (temp - 0.25) * (0.38 - 0.35)/0.25 + 0.35;
        else if(temp <= 1)
            q = (temp - 0.5) * (0.42 - 0.38)/0.5 + 0.38;
        else if(temp <= 2)
            q = (temp - 1) * (0.445 - 0.42) + 0.42;
        else if(temp <= 3)
            q = (temp - 2) * (0.47 - 0.445) + 0.445;
        else if(temp <= 4)
            q = (temp - 3) * (0.475 - 0.47) + 0.47;
        else
            q = 0.5;
        ba = (180 - (180 - m_ba)/(1 - 3*C*m_o * (m_k*m_v + 0.5 *q* m_t)/(m_e*q*m_t)))*PI/360.0;//折弯角度的一半
        m_R = m_k*(2*m_r * tanf(ma*2)+m_v-2*m_r*cosf(ba*PI/360));
        ba = (180 - (180 - m_ba)/(1 - 3*C*m_o * (m_R + 0.5 *q* m_t)/(m_e*q*m_t)))*PI/360.0;//折弯角度的一半
        sin_value = sinf(ba);
        cos_value = cosf(ba);
        tan_value = tanf(ba);
        temp = 1/(2*tan_value)-m_k/sin_value + m_k;

        m_h = temp*m_v - (1/sin_value)*m_t + ((1-sin_value)-2*(cos_value - tanf(PI/4 - ma))*temp)*m_r ;

        if (m_ba<110)
        {
                m_h = m_h +(m_ba-110)*0.006+m_v*0.004;//;
        }
        else if (m_ba>=110 && m_ba<130)
        {
                if(m_v>20)
                    m_h = m_h+m_v*0.001; //+(m_ba[i]-110)*0.001//
        }
        else if (m_ba>=130 && m_ba<150)
        {
                m_h = m_h +(m_ba-130)*0.001+m_v*0.0015;//;//+(m_v*m_BendAngle);
        }
        else if (m_ba>=150)
        {
                m_h = m_h +(m_ba-150)*0.001+m_v*0.002;//;//+(m_v*m_BendAngle);
        }


        if (m_ba<100 && m_tt>m_t)
            m_h=m_h+(m_t-m_tt)*1.16;
        else if (m_ba<100 && m_tt<(m_t-m_v/20))
            m_h=m_h+(m_t-m_tt)+(m_t-m_v/20-m_tt)*0.6;
        else
            m_h=m_h+(m_t-m_tt);

        result = (0.00053*m_s*m_tt*m_tt*m_l)/m_v + m_h;// + DisMenu[YSetting].Dis[YZero].fword;

        return result;
    }
}

