#include "datamanager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
DGZGrid* DataManager::m_grid = nullptr;
QImage* DataManager::m_image = nullptr;
DataManager::DataManager()
{

}

DGZGrid* DataManager::LoadGrid(const QString& filename)
{
    DGZGrid* tempGrid = new DGZGrid(); //задаем
    bool StartReadingData = false;
    QFile inputFile(filename); //открыли файл
    if (inputFile.open(QIODevice::ReadOnly)) //считываем файл
    {
       QTextStream in(&inputFile);
       //считываем шапку файла
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if(line.contains("FSNROW"))
          {
              QStringList list = line.split(" ");
              for(auto word: list) //проходим по всем словам
              {
                  bool ok;
                  int number = word.toInt(&ok);
                  if(ok)
                  {
                    //qDebug() << number;

                        if(tempGrid->xSize != 0)
                        {
                           tempGrid->ySize = number;
                        }
                        if(tempGrid->xSize == 0)
                        {
                           tempGrid->xSize = number;
                        }
                  }
              }

          }
          //считываем цифры для построения грида

          if(StartReadingData)
          {
              QStringList list = line.split(" "); //разбиваем на слова. проверяем, что слово - это цифра
              for(auto word: list)
              {
                  bool ok;
                  float number = word.toFloat(&ok);
                  if(ok)
                  {
                    if(number > tempGrid->maxValue) //поиск максимального числа
                    {
                        tempGrid->maxValue = number;
                    }
                     tempGrid->values.push_back(number);
                  }
              }
          }
          if(line.contains("->Default"))
          {
                  StartReadingData = true;
            }

       }

       qDebug() << tempGrid->values.size();
       qDebug() << tempGrid->xSize * tempGrid->ySize;
       m_grid = tempGrid;
       inputFile.close();
    }
    return tempGrid;
}

QImage *DataManager::LoadImage(const QString &filename)
{

    QImage* tempImage = new QImage();
    bool ok = tempImage->load(filename);
    if(!ok) {
        qDebug() << "NO IMAGE";
        //QMessageBox::warning(,tr("Сообщение"), tr("Не могу загрузить изображение %l").arg(filename));
        return nullptr;
    }
    m_image = tempImage;
    return tempImage;
}
