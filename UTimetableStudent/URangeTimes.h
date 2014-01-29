#ifndef URANGETIMES_H
#define URANGETIMES_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>

class URangeTimes
{
public:
    URangeTimes( QString time, QVariant data );
    bool check(const QTime time );
    QString toString( QString format = "hh:mm" ) const;
    QPair < QTime, QTime > range() const;

public:
    QTime time1;
    QTime time2;

    QVariant d_data;
};


class UListRangeTimes
{
public:
    QVariant find( const QTime time, bool * b = 0 );
//    int indexData( const QVariant data );
    int indexOf( const QTime time );
    void sort( Qt::SortOrder order = Qt::AscendingOrder );

public:
    QList < URangeTimes > list;
};

#endif // URANGETIMES_H
