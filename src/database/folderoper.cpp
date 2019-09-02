#include "databaseoper.h"
#include "folderoper.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

FolderOper::FolderOper()
{

}

bool FolderOper::addFolder(FOLDER folderInfo)
{
    QStringList columnName = {"name", "image_path", "create_time"};
    QList<QVariant> values;
    values.append(folderInfo.folderName);
    values.append(folderInfo.imgPath);
    values.append(folderInfo.createTime);
    return DatabaseOper::getInstance()->insertData(TABLE_FOLDER, columnName, values);
//    QString testSql = "insert into folder (name, image_path, create_time) values ('test', '/mnt/hgfs/D/test/img/test.png', '2019-08-16 12:00:00')";
//    QSqlQuery sqlQuery;
//    sqlQuery.prepare(testSql);
//    if(!sqlQuery.exec())
//    {
//        qDebug()<<"exec sql error: " << sqlQuery.lastError().text();
//        return false;
//    }
//    return true;
}

bool FolderOper::updateFolderName(FOLDER folderInfo)
{
    //todo:檢查folder name是否重複
    QString updateSql = "update %s set name = :name where id = :id";
    updateSql.sprintf(updateSql.toLatin1().constData(), TABLE_FOLDER);
    QMap<QString, QVariant> valuesMap;
    valuesMap[":name"] = folderInfo.folderName;
    valuesMap[":id"] = folderInfo.id;
    return DatabaseOper::getInstance()->updateData(updateSql, valuesMap);

}

QList<FOLDER> FolderOper::getFolderList()
{
    QString queryStr = "select id, name, image_path, create_time from %s order by create_time desc";
    queryStr.sprintf(queryStr.toLatin1().constData(), TABLE_FOLDER);
    QList<QList<QVariant>> result;
    QList<FOLDER> folderInfo;
    if (DatabaseOper::getInstance()->queryData(queryStr, 4, result))
    {
        for (int i = 0; i < result.size(); i++)
        {
            QList<QVariant> tmp = result.at(i);
            FOLDER folderInfoTmp;
            folderInfoTmp.id = tmp.at(0).toInt();
            folderInfoTmp.folderName = tmp.at(1).toString();
            folderInfoTmp.imgPath = tmp.at(2).toString();
            folderInfoTmp.createTime = tmp.at(3).toDateTime();
            folderInfo.append(folderInfoTmp);
            //delete tmp;  todo:delete
        }

    }
    return folderInfo;

}

QList<FOLDER> FolderOper::searchFolder(QString searchKey)
{
    QString queryStr = "select id, name, image_path, create_time from %1 where name like \'\%%2\%\' order by create_time desc";
    QString queryStrFinal = QString(queryStr).arg(TABLE_FOLDER).arg(searchKey);
    QList<QList<QVariant>> result;
    QList<FOLDER> folderInfo;
    if (DatabaseOper::getInstance()->queryData(queryStrFinal, 4, result))
    {
        for (int i = 0; i < result.size(); i++)
        {
            QList<QVariant> tmp = result.at(i);
            FOLDER folderInfoTmp;
            folderInfoTmp.id = tmp.at(0).toInt();
            folderInfoTmp.folderName = tmp.at(1).toString();
            folderInfoTmp.imgPath = tmp.at(2).toString();
            folderInfoTmp.createTime = tmp.at(3).toDateTime();
            folderInfo.append(folderInfoTmp);
            //delete tmp;  todo:delete
        }

    }
    return folderInfo;

}

QList<FOLDER> FolderOper::getFolderByName(QString folderName)
{
    QString queryStr = "select id, name, image_path, create_time from %1 where name is \'%2\' order by create_time desc";
    QString queryStrFinal = QString(queryStr).arg(TABLE_FOLDER).arg(folderName);
    QList<QList<QVariant>> result;
    QList<FOLDER> folderInfo;
    if (DatabaseOper::getInstance()->queryData(queryStrFinal, 4, result))
    {
        for (int i = 0; i < result.size(); i++)
        {
            QList<QVariant> tmp = result.at(i);
            FOLDER folderInfoTmp;
            folderInfoTmp.id = tmp.at(0).toInt();
            folderInfoTmp.folderName = tmp.at(1).toString();
            folderInfoTmp.imgPath = tmp.at(2).toString();
            folderInfoTmp.createTime = tmp.at(3).toDateTime();
            folderInfo.append(folderInfoTmp);
            //delete tmp;  todo:delete
        }

    }
    return folderInfo;
}

QStringList FolderOper::getFolderNameList()
{
    QString queryStr = "select name from %s";
    queryStr.sprintf(queryStr.toLatin1().constData(), TABLE_FOLDER);
    QList<QList<QVariant>> result;
    QStringList folderNameList;
    if (DatabaseOper::getInstance()->queryData(queryStr, 1, result))
    {
        for (int i = 0; i < result.size(); i++)
        {
            QList<QVariant> tmp = result.at(i);
            folderNameList.append(tmp.at(0).toString());
        }
    }
    return folderNameList;
}

bool FolderOper::deleteFolder(int id)
{
    return DatabaseOper::getInstance()->deleteDataById(TABLE_FOLDER, "id", id);
}
