#ifndef MYTOOL_H
#define MYTOOL_H


#include <QFile>
#include <QDir>
#include <QtDebug>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
static int last_position = 0;

//记录当前已经处理掉的文件位置
void doSomething(string line)
{
    std::cout << "**** " << line << " ****"<< std::endl;
}
void find_last_line(ifstream &infile) {
    infile.seekg(0, ios::end);
    int filesize = infile.tellg();
    for(int n = last_position; n < filesize; n++)
    {
        infile.seekg(last_position, ios::beg);
        string line; getline(infile, line);
        doSomething(line);//获取最新行的内容
        if(infile.tellg()>0)//这里必须加入这个判断，因为在频繁更新目标文件时，会导致该函数返回-1
        {
            n = last_position = infile.tellg();
        }
    }
}
int ReadFileRealTime(std::string file_full_path) {
    int position = 0;
    while(true) {
        ifstream infile(file_full_path);
        find_last_line(infile);
    }

}


//create file
void createFile(QString filePath,QString fileName)
{
    QDir tempDir;
    //临时保存程序当前路径
    QString currentDir = tempDir.currentPath();
    //如果filePath路径不存在，创建它
    if(!tempDir.exists(filePath))
    {
        qDebug()<<"不存在该路径"<<endl;
        tempDir.mkpath(filePath);
    }
    QFile *tempFile = new QFile;
    //将程序的执行路径设置到filePath下
    tempDir.setCurrent(filePath);
    qDebug()<<tempDir.currentPath();
    //检查filePath路径下是否存在文件fileName,如果停止操作。
    if(tempFile->exists(fileName))
    {
        qDebug()<<"文件存在";
        return ;
    }
    //此时，路径下没有fileName文件，使用下面代码在当前路径下创建文件
    tempFile->setFileName(fileName);
    if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"打开失败";
    }
    tempFile->close();
    //将程序当前路径设置为原来的路径
    tempDir.setCurrent(currentDir);
    qDebug()<<tempDir.currentPath();
}

////ReadFileRealTime("/home/wangpengcheng/CUDA9.0_Samples/NVIDIA_CUDA-9.0_Samples/0_Simple/asyncAPI/readme.txt");
//QString file_dir=QDir::currentPath();
//QDateTime current_date_time =QDateTime::currentDateTime();
//QString current_date =current_date_time.toString("yyyy-MM-dd-hh:mm:ss:zzz")+".txt";
//createFile(file_dir,current_date);
//QFileInfo file_mesage(file_dir+'/'+current_date);
//qDebug()<<file_mesage;

#endif // MYTOOL_H
