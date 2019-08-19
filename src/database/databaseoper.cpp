#include "databaseoper.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "src/app/consts.h"


DatabaseOper *DatabaseOper::instance = NULL;
DatabaseOper::DatabaseOper()
{
    initDatabase();
}

DatabaseOper::~DatabaseOper()
{

}

DatabaseOper *DatabaseOper::getInstance()
{
    if (NULL == instance)
    {
        instance = new DatabaseOper();
    }
    return instance;
}

void DatabaseOper::initDatabase()
{
    createSqlMap[TABLE_FOLDER] = "create table folder (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, image_path TEXT, create_time DATE)";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库的名称
     db.setDatabaseName(DB_PATH);
    //打开数据库
     if (!db.open()){
        //return false;
         initFlag = false;
     }
     else {
         initFlag = true;
         sqlDatabase = QSqlDatabase::database();
         sqlQuery = QSqlQuery(db);
     }
     checkTableExist();

}

void DatabaseOper::checkTableExist()
{
    //QString createFolderSql = "create table folder (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, image_path TEXT, create_time DATE)";
    QStringList tableList = QSqlDatabase::database().tables(QSql::Tables);
    for (int i = 0; i < TABLE_NAME.size(); i++)
    {
        if (!tableList.contains(TABLE_NAME.at(i)))
        {
            createTable(createSqlMap.value(TABLE_NAME.at(i)));
        }
        else
        {
//            QSqlQuery query;
//          query.prepare("INSERT INTO person (id, forename, surname) "
//                        "VALUES (?, ?, ?)");
//          query.addBindValue(1001);
//          query.addBindValue("Bart");
//          query.addBindValue("Simpson");
//          query.exec();

//            QString testSql = "insert into folder (name, image_path, create_time) values ('test', '/mnt/hgfs/D/test/img/test.png', '2019-08-16 12:00:00')";
//            QSqlQuery sqlQuery;
//            sqlQuery.prepare(testSql);
//            if(!sqlQuery.exec())
//            {
//                qDebug()<<"exec sql error: " << sqlQuery.lastError().text();
//                //return false;
//            }

        }
    }

}

void DatabaseOper::createTable(QString createSql)
{
    //QSqlQuery sqlQuery;
    sqlQuery.prepare(createSql);
    if(!sqlQuery.exec())
    {
        qDebug()<<"create table error: " << sqlQuery.lastError().text();
    }
    else
    {
        qDebug()<<"table created: " << createSql;
    }
}

bool DatabaseOper::insertData(QString tableName, QStringList columnName, QList<QVariant> values)
{
    QString insertSql = "insert into %s (%s) values (%s)";
    QString value = "?";
    //QSqlQuery sqlQuery;
    //拼接問號

    for (int i = 0; i < columnName.length() - 1; i++)
    {
        value.append(", ?");
    }
    insertSql.sprintf(insertSql.toLatin1().constData(), tableName.toLatin1().constData(), columnName.join(",").toLatin1().constData(), value.toLatin1().constData());

    sqlQuery.prepare(insertSql);
    for (int i = 0; i < values.length(); i++) {
        sqlQuery.addBindValue(values.at(i));
    }

    if(!sqlQuery.exec())
    {
        qDebug()<<"insertData error: " << sqlQuery.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

bool DatabaseOper::updateData(QString updateSql, QMap<QString, QVariant> valuesMap)
{
    sqlQuery.prepare(updateSql);

    QMapIterator<QString, QVariant> i(valuesMap);
    while (i.hasNext()) {
        i.next();
        sqlQuery.bindValue(i.key(), i.value());
    }
    if(!sqlQuery.exec())
    {
        qDebug()<<"updateData error: " << sqlQuery.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

bool DatabaseOper::queryData(QString queryStr, int resultItemSize, QList<QList<QVariant>> & result)
{
    sqlQuery.prepare(queryStr);
    if(!sqlQuery.exec())
    {
        qDebug()<<"queryData error: " << sqlQuery.lastError().text();
        return false;
    }
    else
    {
        while(sqlQuery.next())
        {
            QList<QVariant> tmpList;
            for (int i = 0; i < resultItemSize; i++)
            {
                tmpList.append(sqlQuery.value(i));
            }
            result.append(tmpList);
        }
        return true;
    }

}

bool DatabaseOper::deleteDataById(QString tableName, QString id, int idValue)
{
    QString deleteSql = "delete from %s where %s = ?";
    QString value = "?";


    deleteSql.sprintf(deleteSql.toLatin1().constData(), tableName.toLatin1().constData(), id.toLatin1().constData());
    sqlQuery.addBindValue(QVariant(idValue));
    sqlQuery.prepare(deleteSql);


    if(!sqlQuery.exec())
    {
        qDebug()<<"deleteDataById error: " << sqlQuery.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}




