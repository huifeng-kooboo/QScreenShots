#include "Utils/filemanager.h"

namespace FileManager {

// 创建文件
void CreateFile(QString& strFileName)
{
    QFile file(strFileName);
    file.open(QIODevice::WriteOnly);
    file.close();
}

bool DeleteFile(QString& strFileName)
{
    QFile file(strFileName);
    return file.remove();
}

bool CreateFolder(QString& strFolderPath)
{
    return true;
}

}
