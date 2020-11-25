#include "timemanager.h"
#include <qdatetime.h>


namespace TimeManager {

// 得到当前时间字符串
QString GetCurrentTimeStr()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString strCurDate =current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
    return strCurDate;
}

}
