#include "Utils/log.h"
#include <QDateTime>
#include <QDate>
#include <QFileInfo>
#include "Utils/filemanager.h"
#include "Utils/timemanager.h"

Log& Log::GetInstace()
{
    static Log myLog;
    return myLog;
}

Log::Log()
{
    m_mapState.insert(1," State_Common:");
    m_mapState.insert(2," State_Warning:");
    m_mapState.insert(3," State_Error:");
}

Log::~Log()
{

}

// 写日志
void Log::WriteLog(const QString& strLog, LOGSTATE eLogState, bool bNeedTime)
{
    if(m_strLogName.isEmpty())
    {
        return;
    }
    QFile file(m_strLogName);
    file.open(QIODevice::Append | QIODevice::Text);
    QString strNote;
    if (bNeedTime)
    {
        QString strCurDate = TimeManager::GetCurrentTimeStr();
        strNote.append(strCurDate+":");
    }
    strNote.append(m_mapState[eLogState]);
    strNote.append(strLog);
    strNote.append("\n");
    file.write(strNote.toUtf8());
    file.close();
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
