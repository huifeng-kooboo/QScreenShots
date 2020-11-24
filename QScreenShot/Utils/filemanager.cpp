#include "Utils/filemanager.h"

namespace FileManager {
void CreateFile(QString& strFileName)
{
    QFile file(strFileName);
    file.open(QIODevice::WriteOnly);
    file.close();
}
}
