#include "Utils/log.h"
#include <QDateTime>
#include <QDate>
#include <QFileInfo>
#include "Utils/filemanager.h"

Log& Log::GetInstace()
{
    static Log myLog;
    return myLog;
}

Log::Log()
{

}

Log::~Log()
{

}

// 写日志
void Log::WriteLog(const QString& strLog, LOGSTATE eLogState, bool bNeedTime)
{

}

// 是否需要时间
void Log::SetLogName(QString strLogName, bool bNeedTime)
{
    if(strLogName.isEmpty())
    {
        return;
    }
    m_strLogName = strLogName + ".log";
    if(bNeedTime == true)
    {
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString strCurDate =current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
        m_strLogName = strLogName.append(strCurDate).append(".log");
    }
    //创建log文件
    QFileInfo fileInfo(m_strLogName);
    if(fileInfo.exists())
    {
        return;
    }
    // 创建文件
    FileManager::CreateFile(m_strLogName);
}
