#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QSqlTableModel>
#include <QSqlRecord>


void openBeep();
void Sql_Init();
QString SystemWarnInformation(int WarnID);


#define FootStart		0x01//¶ÁœÅÌ€¿ª¹ØÐÅºÅ  IN1
#define FootUp	    	0x02//œÅÌ€ÉÏ  IN2
/*********************ÔËÐÐÄ£Êœ:µ¥ŽÎ,Á¬Ðø,µã¶¯**********************/
#define CUTSMODE			0x08//µ¥ŽÎÄ£Êœ  IN4
#define CUTCMODE			0x04//Á¬ÐøÄ£Êœ  IN3
#define CUTJMODE			0x0C//µã¶¯Ä£Êœ
#define CUTEMODE			0x00//µ¥ŽÎÁ¬Ðø¶ŒÓÐÐ§£¬ŽíÎóÄ£Êœ
#define CutMode		        0x0C//ŒôÇÐ·œÊœ on Á¬Ðø off µ¥ŽÎ
#define UpperPoint		    0X10//ÉÏËÀµãÐÅºÅÊäÈë on Î»ÓÚÉÏËÀµã IN5
#define DownPoint			0X20// IN6
#define PumpSignal		    0X40//ÓÍ±ÃÆô¶¯ÐÅºÅ IN7

#define VFast  0x01
#define VSlow  0x02
#define Vkeep  0x04
#define Vunload 0x08
#define Vback   0x10
#define Vstop  0x20

#define ENTER_RETURN 0x88
#define ENTER_QUIT_STOP   0xA0
#define ENTER_ENABLE  0xAA
#define ENTER_DISENABLE  0x55




#define UpperPointAlarm   1

extern int ProgIndex;
extern int ProgNameNum;
extern int StepIndex;
extern int CurrentStep;

extern int UpMoldIndex;
extern int LowerMoldIndex;

extern int UpMoldNum;
extern int LowerMoldNum;

extern QSqlDatabase db;

#define MAIN_WIDGET_Y    0
#define WIDGET_Y    MAIN_WIDGET_Y + 100


struct _VALUESTATE
{
  unsigned char VFaststate;
  unsigned char VSlowstate;
  unsigned char VKeepstate;
  unsigned char Vunloadstate;
  unsigned char Vbackstate;
  unsigned char Vstopstate;

  unsigned short int KeepTime;
  unsigned short int UnloadTime;

};

extern struct _VALUESTATE ValveReg;

struct _CURRENTREG
{
  QString CurrentProgramName;
  int Current_ProgramLibRow;
  int Current_UpMoldRow;
  int Current_LowerMoldRow;
  int Current_MaterialRow;
  int Current_RunRow;
  int Current_StepProgramRow;
  int StepProgramRowTotal;
  int Current_MotorAlarm;
//  int CurrentRnuStateWorkedTotal;
  QString Current_WorkedTotal;

};

extern struct _CURRENTREG CurrentReg;


enum {
    UpMold_Id = 0,
    UpMold_Angle = 1,
    UpMold_Height = 2,
    UpMold_Radius = 3,
    UpMold_Impedance = 4
};



enum {
    LowerMold_Id = 0,
    LowerMold_Height = 1,
    LowerMold_DV = 2,
    LowerMold_Angle = 3,
    LowerMold_Radius = 4,
    LowerMold_SpeedPostion = 5,
    LowerMold_SpeedChange= 6,
    LowerMold_Impedance = 7
};


enum {
    StepProgram_Id = 0,
    StepProgram_Angle = 1,
    StepProgram_AngleCompensate = 2,
    StepProgram_Yaxis = 3,
    StepProgram_Xaxis = 4,
    StepProgram_XaxisCorrect = 5,
    StepProgram_Distance = 6,
    StepProgram_Pressure = 7,
    StepProgram_ReturnTime = 8,
    StepProgram_HoldingTime = 9,
    StepProgram_Raxis = 10
};

enum {
    RunStep_Angle = 0,
    RunStep_AngleCompensate = 1,
    RunStep_Yaxis = 2,
    RunStep_Xaxis = 3,
    RunStep_XaxisCorrect = 4,
    RunStep_Raxis =5
};

enum {
    Program_Id = 0,
    Program_Name = 1,
    Program_StepNum = 2,
    Program_BoardWide = 3,
    Program_BoardThick = 4,
    Program_Material = 5,
    Program_UpMold = 7,
    Program_LowerMold = 6,
    Program_ProcessNum= 8

};

enum SystemSettings
{
   LanguageItem=0,
   UnitsItem,
   ConcedeTimeItem,
   PressureKeepingTimeItem,
   RemovalTimeItem,
   FrameStrengthItem

};


enum
{
    Table_Id        = 0,
    Table_Name      = 1,
    Table_Value     = 2,
    Table_Info      = 3
};

enum {
    Material_Id = 0,
    Material_Name = 1,
    Material_EMold = 3,
    Material_StrengthFactor =2
};



struct Stepdata
{
  double Angle;
  double AngleCompensate;
  double Yaxis;
  double XaxisCorrect;
  double Distance;
  double Pressure;
  double Xaxis;
  double ReturnTime;
  double Holding;
  double Raxis;
  double Yzero;
};

extern struct Stepdata CurrentStepTemp;



struct ProgramFiles
{
  QString ProgramName;
  double StepNumber;
  double BroadWideth;
  double BroadThick;
  QString Material;
  double UpMold;
  double LowerMold;
  double ProcessedNum;
  struct Stepdata  StepProgram[50];
};


extern struct ProgramFiles  CurrentProgramTemp;



struct UpMoldData
{
  double Height;
  double Angle;
  double Radius;
  double Impedance;
};
extern struct UpMoldData  CurrentUpMoldTemp;

 struct LowerMoldData
 {
   double Height;
   double D_V;
   double Angle;
   double Radius;
   double SpeedChangePos;
   double SpeedSafeDis;
   double Impedance;
 };
extern struct LowerMoldData  CurrentLowerMoldTemp;

struct MaterialData
{
  double StrengthFactor;
  double EMold;

};
extern struct MaterialData  CurrentMaterialTemp;




class Global : public QWidget
{
    Q_OBJECT
public:
    explicit Global(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // GLOBAL_H
