#ifndef LOG_H
#define LOG_H
#include <QString>

#endif // LOG_H 

enum LOGSTATE
{
    COMMON, // 常规
    WARNING, //警告
    ERROR, // 错误
};

class Log
{
public:
    Log();
    static Log& GetInstace();
    ~Log();
    void SetLogName(QString strLogName,bool bNeedTime = false);
    void WriteLog(const QString& strLog,LOGSTATE eLogState=LOGSTATE::COMMON,bool bNeedTime=true);
private:
    QString m_strLogName;
};

#define G_LOG Log::GetInstance()
