#include "databaseoper.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>

#include "src/app/consts.h"

#include "uiutil.h"


DatabaseOper *DatabaseOper::m_instance = NULL;
DatabaseOper::DatabaseOper()
{
    initDatabase();
}

DatabaseOper::~DatabaseOper()
{

}

DatabaseOper *DatabaseOper::getInstance()
{
    if (NULL == m_instance)
    {
        m_instance = new DatabaseOper();
    }
    return m_instance;
}


void DatabaseOper::initDatabase()
{
    m_createSqlMap[TABLE_FOLDER] = "create table folder (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, image_path TEXT, create_time DATE)";
    m_createSqlMap[TABLE_NOTE] = "create table note (id INTEGER PRIMARY KEY AUTOINCREMENT, note_type INTEGER, content_text TEXT, content_path TEXT, voice_time INTEGER, voice_sample_data TEXT, folder_id INTEGER, create_time DATE)";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库的名称
    const QString DATABASE_PATH = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
     db.setDatabaseName(DATABASE_PATH);
    //打开数据库
     if (!db.open()){
        //return false;
         m_initFlag = false;
     }
     else {
         m_initFlag = true;
         n_sqlDatabase = QSqlDatabase::database();
         m_sqlQuery = QSqlQuery(db);
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
            createTable(m_createSqlMap.value(TABLE_NAME.at(i)));
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
//                //return false;
//            }

        }
    }

}

void DatabaseOper::createTable(QString createSql)
{
    //QSqlQuery sqlQuery;
    m_sqlQuery.prepare(createSql);
    if(!m_sqlQuery.exec())
    {
        //qDebug()<<"create table error: " << m_sqlQuery.lastError().text();
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("create table error:"), m_sqlQuery.lastError().text());
    }
    else
    {
        //qDebug()<<"table created: " << createSql;
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("table created:"), createSql);
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

    m_sqlQuery.prepare(insertSql);
    for (int i = 0; i < values.length(); i++) {
        m_sqlQuery.addBindValue(values.at(i));
    }

    if(!m_sqlQuery.exec())
    {
        //qDebug()<<"insertData error: " << m_sqlQuery.lastError().text();
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("insertData error:"), m_sqlQuery.lastError().text());
        return false;
    }
    else
    {
        return true;
    }
}

bool DatabaseOper::updateData(QString updateSql, QMap<QString, QVariant> valuesMap)
{
    m_sqlQuery.prepare(updateSql);

    QMapIterator<QString, QVariant> i(valuesMap);
    while (i.hasNext()) {
        i.next();
        m_sqlQuery.bindValue(i.key(), i.value());
    }
    if(!m_sqlQuery.exec())
    {
        //qDebug()<<"updateData error: " << m_sqlQuery.lastError().text();
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("updateData error:"), m_sqlQuery.lastError().text());
        return false;
    }
    else
    {
        return true;
    }
}

bool DatabaseOper::queryData(QString queryStr, int resultItemSize, QList<QList<QVariant>> & result)
{
    m_sqlQuery.prepare(queryStr);
    if(!m_sqlQuery.exec())
    {
        //qDebug()<<"queryData error: " << m_sqlQuery.lastError().text();
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("queryData error:"), m_sqlQuery.lastError().text());
        return false;
    }
    else
    {
        while(m_sqlQuery.next())
        {
            QList<QVariant> tmpList;
            for (int i = 0; i < resultItemSize; i++)
            {
                tmpList.append(m_sqlQuery.value(i));
            }
            result.append(tmpList);
        }
        return true;
    }

}

bool DatabaseOper::queryLastData(QString queryStr, int resultItemSize, QList<QVariant> & result)
{
    m_sqlQuery.prepare(queryStr);
    if(!m_sqlQuery.exec())
    {
        //qDebug()<<"queryData error: " << m_sqlQuery.lastError().text();
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("queryData error:"), m_sqlQuery.lastError().text());
        return false;
    }
    else
    {
        if (m_sqlQuery.last())
        {
            for (int i = 0; i < resultItemSize; i++)
            {
                result.append(m_sqlQuery.value(i));
            }
        }

        return true;
    }

}

bool DatabaseOper::deleteDataById(QString tableName, QString id, int idValue)
{
    QString deleteSql = "delete from %1 where %2 = ?";
    QString deleteSqlFinal = QString(deleteSql).arg(tableName).arg(id);

    m_sqlQuery.prepare(deleteSqlFinal);

    m_sqlQuery.addBindValue(QVariant(idValue));
    if(!m_sqlQuery.exec())
    {
        //qDebug()<<"deleteDataById error: " << m_sqlQuery.lastError().text();
        UiUtil::writeLog(2, __FILE__, __LINE__, Q_FUNC_INFO, QString("deleteDataById error:"), m_sqlQuery.lastError().text());
        return false;
    }
    else
    {
        return true;
    }
}




