#include "timemanager.h"
#include <qdatetime.h>


namespace TimeManager {
QString GetCurrentTimeStr()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString strCurDate =current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
    return strCurDate;
}

}
