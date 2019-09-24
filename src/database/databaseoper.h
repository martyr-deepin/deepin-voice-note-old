#ifndef DATABASEOPER_H
#define DATABASEOPER_H

#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>
#include <QDebug>
#include "consts.h"


class DatabaseOper
{
public:
    DatabaseOper();
    ~DatabaseOper();

    static DatabaseOper *getInstance();

    bool insertData(QString tableName, QStringList columnName, QList<QVariant> values);
    bool updateData(QString updateSql, QMap<QString, QVariant> valuesMap);
    bool queryData(QString queryStr, int resultItemSize, QList<QList<QVariant>> & result);
    bool queryLastData(QString queryStr, int resultItemSize, QList<QVariant> & result);
    bool deleteDataById(QString tableName, QString id, int idValue);


private:
    static DatabaseOper *m_instance;
    QSqlDatabase n_sqlDatabase;
    QSqlQuery m_sqlQuery;
    bool m_initFlag = false;
    const QStringList TABLE_NAME = {TABLE_FOLDER, TABLE_NOTE};
    QMap<QString, QString> m_createSqlMap;

    void initDatabase();
    void checkTableExist();
    void createTable(QString createSql);



};



#endif // DATABASEOPER_H
