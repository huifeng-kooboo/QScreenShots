#ifndef LOG_H
#define LOG_H
#include <QString>
#include <QMap>
#endif // LOG_H 

enum LOGSTATE
{
    COMMON = 1, // 常规
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
    void WriteLog(const QString& strLog,LOGSTATE eLogState=LOGSTATE::COMMON,bool bNeedTime=true); // 写入日志
private:
    QString m_strLogName;
    QMap<int,QString> m_mapState;
};

#define G_LOG Log::GetInstance()
