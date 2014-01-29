#include "URangeTimes.h"

/// FUNCTION
bool lessThan(const URangeTimes &rt1, const URangeTimes &rt2)
{
    return rt1.time1 < rt2.time1;
}
bool moreThan(const URangeTimes &rt1, const URangeTimes &rt2)
{
    return rt1.time1 > rt2.time1;
}


/// PUBLIC
URangeTimes::URangeTimes( QString time, QVariant data )
{
    // удаляем пробелы
    time = time.remove(" ");

    QString strTime1 = time.split("-").at(0);
    QString strTime2 = time.split("-").at(1);

    time1 = QTime::fromString(strTime1);
    time2 = QTime::fromString(strTime2);

    d_data = data;
}
bool URangeTimes::check( const QTime time )
{
    if( time1 <= time && time <= time2 )
        return true;

    return false;
}
QString URangeTimes::toString( QString format ) const
{
    return QString( "%1-%2" )
            .arg( time1.toString( format ) )
            .arg( time2.toString( format ) );
}
QPair < QTime, QTime > URangeTimes::range() const
{
    return QPair < QTime, QTime > ( time1, time2 );
}


/// PUBLIC
QVariant UListRangeTimes::find( const QTime time, bool * b /*= 0*/ )
{
    *b = false;

    for ( int i = 0; i < list.size(); i++ )
        // если нашли, возвращаем дату
        if ( list[i].check( time ) )
        {
            *b = true;
            return list[i].d_data;
        }

    return QVariant();
}
//int UListRangeTimes::indexData( const QVariant data )
//{
//    for ( int i = 0; i < list.size(); i++ )
//        if ( list[i].d_data == data )
//            return i;

//    return -1;
//}
int UListRangeTimes::indexOf( const QTime time )
{
    for ( int i = 0; i < list.size(); i++ )
        if ( list[i].check( time ) )
            return i;

    return -1;
}
void UListRangeTimes::sort( Qt::SortOrder order /*= Qt::AscendingOrder*/ )
{
    if(order == Qt::AscendingOrder)
        qSort( list.begin(), list.end(), lessThan );
    else
        qSort( list.begin(), list.end(), moreThan );
}
