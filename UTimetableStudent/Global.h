#ifndef GLOBAL_H
#define GLOBAL_H

#include "QtJson/json.h"
#include "URangeTimes.h"
#include <QColor>

const char codec[] = "utf8";

const QString timeFormat = "hh:mm:ss";
const QString dateFormat = "dd.MM.yyyy";

namespace TableLessons
{
    enum
    {
        NumberOfLesson, // номер пары
        Monday, // понедельник
        Tuesday,  // вторник
        Wednesday,  // среда
        Thursday,  // четверг
        Friday,  // пятница
        Saturday,  // суббота
        Sunday  // воскресенье
    };
}

namespace TableCalls
{
    enum
    {
        NumberOfLesson, // номер пары
        RangeTimes // диапазон времени
    };
}

const int numberOfLesson = TableCalls::NumberOfLesson;
const int rangeTimes = TableCalls::RangeTimes;

enum
{
    Recess, // Перемена
    Lesson  // Урок
};


/// FUNCTION
//// Функция вернет строкое описание времени
//QString longStringTime( const int second, bool hideNullValues = true );
//QString longStringTime2( const int second, const QString format = "hh:mm:ss" );

//// Найдем перемены
//UListRangeTimes findRecess( const UListRangeTimes & lrt );

//// Функция определения четности числа
//bool isEven( const int number );

//// Определяет по текущей дате четная ли неделя
//bool isEven();

//// Определение "четности" недели
//QString evenWeek( const QDate date );
//QString evenWeek();

//// Функция считывания содержимого файла
//QString readFile( const QString &fileName );

//// Заполним список диапазон времени
//void fillListRangeTimes( UListRangeTimes * lrt, const QString & fileName );

//// Заполняем таблицу расписания звонков
//void fillTimetableCalls( QTableWidget * table, const UListRangeTimes * lrt );

//// Заполняем таблицу расписания занятий
//void fillTimetableLesson( QTableWidget * table, const QString &fileName );

//// Закрасим все ячейки таблицы определенным цветом
//void fillTable( QTableWidget * table, QColor color = Qt::transparent );

//// Закрасим определенные ячейки таблицы определенным цветом
//void fillCellTable( QTableWidget * table, QList < QPair < int, int > > list, const QColor color = Qt::green );

//// Закрасим строку таблицы определенным цветом
//void fillRowTable( QTableWidget * table, int row, const QColor color = Qt::green );

//// Список дней недели
//QStringList daysOfWeeks();

//// Функцию определения номера пары по времени
//int findNumberLesson( UListRangeTimes &lrt, const QTime &time );

//// Записывает информацию о дате и времени в map
//QVariantMap dateTimeTo ( const QDateTime & dateTime, UListRangeTimes &lrt );

//// Определим следующую пару
//QVariantMap searchNextLesson( const QTableWidget * tableCalls, const QTableWidget * tableEven, const QTableWidget * tableOdd, UListRangeTimes &lrt , const QDateTime & dateTime );


class U
{
public:
    class Html
    {
    public:
        static QString bTag( const QString t )
        { return QString( "<" + t + ">" ); }

        static QString eTag( const QString t )
        { return QString( "</" + t + ">" ); }

        static QString tag( const QString t, const QString text )
        { return bTag( t ) + text + eTag( t ); }

        static QString tag( const QString t, const QString par, const QString text )
        { return bTag( t + " " + par ) + text + eTag( t ); }

        static QString hr() { return bTag( "hr" ); }
        static QString br() { return bTag( "br" ); }

        static QString big( const QString text )
        { return tag( "big", text ); }

        static QString small( const QString text )
        { return tag( "small", text ); }

        static QString b( const QString text )
        { return tag( "b", text ); }

        static QString i( const QString text )
        { return tag( "i", text ); }

        static QString color( const QString text, QColor color,
                              bool bold = false, bool italic = false )
        {
            QString result = tag( "font", "color=%1", text );
//            QString result = "<font color=%1>%2</font>";
            result = result./*arg( text ).*/arg( color.name() );

            if ( bold )
                result = b( result );

            if ( italic )
                result = i( result );

            return result;
        }
    };

public:
    static bool isEven( const int number )
    {
        return number % 2 == 0;
    }
    static QString evenWeek( const QDate date )
    {
        return isEven( date.weekNumber() ) ? "Четная" : "Нечетная";
    }

    static QString longStringTime( const int second, bool hideNullValues = true )
    {
        QString strHour = "%1 час";
        QString strMinute = "%1 минут";
        QString strSecond = "%1 секунд";

        QString text;

        int h = second / 3600;
        int m = ( second / 60 ) % 60;
        int s = second % 60;

        if ( hideNullValues )
        {
            if ( h )
            {
                strHour = strHour.arg( h );

                if ( (h >= 2 && h <= 4) || (h >= 22 && h <= 23) )
                    strHour.append("а");

                else if ( h >= 5 && h <= 20 )
                    strHour.append("ов");

                text.append( strHour );
                text.append( " " );
            }

            if ( m )
            {
                strMinute = strMinute.arg( m );

                if( m == 1 || m == 21 || m == 31 || m == 41 || m == 51 )
                    strMinute.append("а");
                else if (  (m >= 2 && m <= 4)
                           || (m >= 22 && m <= 24)
                           || (m >= 32 && m <= 34)
                           || (m >= 42 && m <= 44)
                           || (m >= 52 && m <= 54) )
                    strMinute.append("ы");

                text.append( strMinute );
                text.append( " " );
            }

            strSecond = strSecond.arg( s );

            if( s == 1 || s == 21 || s == 31 || s == 41 || s == 51 )
                strSecond.append("а");
            else if (  (s >= 2 && s <= 4)
                       || (s >= 22 && s <= 24)
                       || (s >= 32 && s <= 34)
                       || (s >= 42 && s <= 44)
                       || (s >= 52 && s <= 54) )
                strSecond.append("ы");

            text.append( strSecond );

        }else
        {
            strHour = strHour.arg( h );

            if ( (h >= 2 && h <= 4) || (h >= 22 && h <= 23) )
                strHour.append("а");

            else if ( h >= 5 && h <= 20 )
                strHour.append("ов");

            text.append( strHour );
            text.append( " " );

            strMinute = strMinute.arg( m );

            if( m == 1 || m == 21 || m == 31 || m == 41 || m == 51 )
                strMinute.append("а");
            else if ( (m >= 2 && m <= 4)
                      || (m >= 22 && m <= 24)
                      || (m >= 32 && m <= 34)
                      || (m >= 42 && m <= 44)
                      || (m >= 52 && m <= 54) )
                strMinute.append("ы");

            text.append( strMinute );
            text.append( " " );

            strSecond = strSecond.arg( s );

            if( s == 1 || s == 21 || s == 31 || s == 41 || s == 51 )
                strSecond.append("а");
            else if ( (s >= 2 && s <= 4)
                      || (s >= 22 && s <= 24)
                      || (s >= 32 && s <= 34)
                      || (s >= 42 && s <= 44)
                      || (s >= 52 && s <= 54) )
                strSecond.append("ы");

            text.append( strSecond );
        }

        return text;
    }

    static QString longStringTime2( const int second, const QString format = "hh:mm:ss" )
    {
        int h = second / 3600;
        int m = ( second / 60 ) % 60;
        int s = second % 60;

        return QTime(h, m, s).toString( format );
    }

    static UListRangeTimes findRecess( const UListRangeTimes & lrt )
    {
        UListRangeTimes listRecess;

        for ( int i = 0; i < lrt.list.size() - 1; i++ )
        {
            QTime time1 = lrt.list.at(i).time2;
            QTime time2 = lrt.list.at(i + 1).time1;

            QString strRangeTimes = QString("%1-%2")
                    .arg( time1.toString( "hh:mm:ss" ) )
                    .arg( time2.toString( "hh:mm:ss" ) );

            listRecess.list.append( URangeTimes( strRangeTimes, Recess ) );
        }

        return listRecess;
    }

    static QString readFile( const QString &filename )
    {
        QFile f(filename);

        if ( !f.open( QFile::ReadOnly | QFile::Text ) )
            return QString();
        else
        {
            QTextStream in( &f );
            in.setCodec( QTextCodec::codecForName( codec ) );

            return in.readAll();
        }
    }


    static void fillListRangeTimes( UListRangeTimes * lrt, const QString & fileName )
    {
        QString jsonText = readFile( fileName );

        if( jsonText.isEmpty() )
        {
            qDebug() << "Произошла ошибка при чтении файла: "
                     << fileName;
            return;
        }

        QtJson::JsonArray result = QtJson::parse( jsonText ).toList();

        if ( result.isEmpty() )
        {
            qDebug() << "Произошла ошибка при парсинге файла: "
                     << fileName;
            return;
        }

        lrt->list.clear();

        foreach ( QVariant line, result )
            lrt->list.append( URangeTimes( line.toString(), Lesson ) );

        lrt->list.append( findRecess(*lrt).list );
        lrt->sort();
    }

    static void fillTimetableCalls( QTableWidget * table, const UListRangeTimes * lrt )
    {
        table->clearContents();

        for ( int i = 0, row = 0; i < lrt->list.size(); i++ )
            if( lrt->list.at(i).d_data.toInt() == Lesson )
            {
                QTableWidgetItem *itemNumberLesson = new QTableWidgetItem();
                QTableWidgetItem *itemRangeTimes = new QTableWidgetItem();

                Qt::Alignment align = Qt::AlignCenter;

                itemNumberLesson->setTextAlignment( align );
                itemRangeTimes->setTextAlignment( align );

                itemNumberLesson->setText( QString::number( row + 1 ) );
                itemRangeTimes->setText( lrt->list.at(i).toString() );

                QVariantList data;
                data << lrt->list[i].range().first;
                data << lrt->list[i].range().second;

                itemRangeTimes->setData( Qt::UserRole, data );

                table->insertRow( table->rowCount() );

                table->setItem( row, numberOfLesson, itemNumberLesson );
                table->setItem( row, rangeTimes, itemRangeTimes );

                row++;
            }

        table->horizontalHeader()->resizeSection( numberOfLesson, 70 );

        int width = 0;
        for ( int i = 0; i < table->columnCount(); i++ )
            width += table->columnWidth(i);

        width += table->verticalHeader()->sizeHint().width();
        width += 3;

        table->setFixedWidth( width );

        table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    static void fillTimetableLesson( QTableWidget * table, const QString & fileName )
    {
        QString jsonText = readFile( fileName );

        if( jsonText.isEmpty() )
        {
            qDebug() << "Произошла ошибка при чтении файла: "
                     << fileName;
            return;
        }

        QtJson::JsonObject result = QtJson::parse( jsonText ).toMap();

        if ( result.isEmpty() )
        {
            qDebug() << "Произошла ошибка при парсинге файла: "
                     << fileName;
            return;
        }

        QtJson::JsonObject daysOfTheWeek = result[ "Дни недели" ].toMap();
        QMapIterator < QString, QVariant > it( daysOfTheWeek );

        while ( it.hasNext() )
        {
            it.next();
            QString day = it.key();

            int column = -1;

            for ( int i = 0; i < table->columnCount(); i++ )
                if( day.contains( table->horizontalHeaderItem(i)->text() ) )
                    column = i;

            if ( column < 0 )
            {
                qDebug() << "День:" << day << "необнаружили в таблице - пропускаем";
                continue;
            }

            QtJson::JsonArray lessons = it.value().toList();

            // занятий нет
            if( lessons.isEmpty() )
                continue;

            foreach ( QVariant lesson, lessons )
            {
                QtJson::JsonObject details = lesson.toMap();

                int row = -1;
                QString numberLesson = details[ "Номер пары" ].toString();

                for ( int i = 0; i < table->rowCount(); i++ )
                    if( numberLesson.contains( table->item( i, 0 )->text() ) )
                        row = i;

                if ( row < 0 )
                {
                    qDebug() << "Пара:" << numberLesson << "необнаружили в таблице - пропускаем";
                    continue;
                }

                QTableWidgetItem *item = table->item( row, column );

                if ( !item )
                {
                    table->setItem( row, column, new QTableWidgetItem() );
                    item = table->item( row, column );
                }

                QString name = details[ "Название" ].toString();
                QString type = details[ "Тип" ].toString();
                QString aud = details[ "Аудитория" ].toString();
                QString teacher = details[ "Преподаватель" ].toString();

                QString text = "%1 (%2)\n%3 %4";
                text = text
                        .arg( name )
                        .arg( type )
                        .arg( teacher )
                        .arg( aud );

                item->setText( text );
                item->setToolTip( text );
                item->setData( Qt::UserRole, details );
            }
        }
    }

    static void fillTable( QTableWidget * table, QColor color = Qt::transparent )
    {
        for ( int i = 0; i < table->rowCount(); i++ )
            for ( int j = 0; j < table->columnCount(); j++ )
            {
                QTableWidgetItem *item = table->item( i, j );
                item->setBackgroundColor( color );
            }
    }
    static void fillCellTable( QTableWidget * table, QList < QPair < int, int > > list, const QColor color /*= Qt::green*/ )
    {
        fillTable( table );

        for ( int i = 0; i < list.size(); i++ )
            table->item( list[i].first, list[i].second )->setBackgroundColor( color );
    }
    static void fillRowTable( QTableWidget * table, int row, const QColor color )
    {
        fillTable( table );

        for ( int j = 0; j < table->columnCount(); j++ )
        {
            QTableWidgetItem *item = table->item( row, j );
            item->setBackgroundColor( color );
        }
    }

    static QStringList daysOfWeeks()
    {
        return QStringList() << "Понедельник"
                             << "Вторник"
                             << "Среда"
                             << "Четверг"
                             << "Пятница"
                             << "Суббота"
                             << "Воскресенье";
    }

    static int findNumberLesson( UListRangeTimes & lrt, const QTime & time )
    {
        int result = -1;

        for ( int i = 0, lesson = 0; i < lrt.list.size(); i++ )
        {
            int typeData = lrt.list[i].d_data.toInt();

            // если лекция
            if( typeData == Lesson )
            {
                lesson++;

                // если наша дата попала в диапазон дат
                if ( lrt.list[i].check( time ) )
                {
                    result = lesson;
                    return result;
                }
            }
        }

        return result;
    }

    static QVariantMap dateTimeTo ( const QDateTime & dateTime, UListRangeTimes &lrt )
    {
        QVariantMap map;

        map[ "Неделя" ] = U::evenWeek( dateTime.date() );
        map[ "Номер недели" ] = dateTime.date().weekNumber();
        map[ "Дата" ] = dateTime.date();
        map[ "Время" ] = dateTime.time();
        map[ "День недели" ] = daysOfWeeks().at( dateTime.date().dayOfWeek() - 1 );
        map[ "Номер пары" ] = findNumberLesson( lrt, dateTime.time() );

        return map;
    }

    static QVariantMap searchNextLesson( const QTableWidget * tableCalls, const QTableWidget * tableEven, const QTableWidget * tableOdd, UListRangeTimes &lrt , const QDateTime & dateTime )
    {
        QVariantMap map;

        QDateTime dateTimeNextLesson = dateTime;
        QTime timeFirstLesson = lrt.list.first().time1;

        const int maxCounter = 14; // количество дней в 2 неделях
        int counter = maxCounter;

        // номер пары
        int row = findNumberLesson( lrt, dateTime.time() );

        // если сейчас перемена, то номер лекции
        // будет, тот, что после перемены
//        if ( row == -1 )
//            row = lrt.indexOf( dateTime.time() ) + 1;

        // если сейчас перемена, то номер лекции
        // будет, тот, что после перемены
        if ( row == -1 )
        {
            row = lrt.indexOf( dateTime.time() ) + 1;
            row = findNumberLesson( lrt, lrt.list.at( row ).time1 );

            row = row - 1; // индекс начинается с 0, а не с 1

//            qDebug() << row;
        }

        // номер дня недели
        int column = dateTime.date().dayOfWeek();

        // пока не заполним информацию о следующей паре
        while ( map.isEmpty() )
        {
            int weekNumber = dateTimeNextLesson.date().weekNumber();
            const QTableWidget * table = U::isEven( weekNumber ) ? tableEven : tableOdd;

            // просмотрим следующие пары на данном дне недели
            // просмотр завершится после дохождения до конца
            // или нахождения пары
            for ( int i = row; i < table->rowCount(); i++ )
            {
                QTableWidgetItem * item = table->item( i, column );

                // если item'а не существует
                if ( !item )
                    continue;

                QVariant data = tableCalls->item( i, rangeTimes )->data( Qt::UserRole );

                if ( data.type() != QVariant::List )
                {
                    qDebug() << "В данных забралась ошибка..." << i;
                    continue;
                }

                QTime timeLesson = data.toList().first().toTime();
//qDebug() << timeLesson;
                // переведем время к времени начала пары
                dateTimeNextLesson.setTime( timeLesson );

                data = item->data( Qt::UserRole );

                // если пара есть
                if ( !data.toMap().isEmpty() )
                {
                    map = dateTimeTo( dateTimeNextLesson, lrt );

                    QVariantMap dataItem = data.toMap();

                    // Добавим информацию о паре с соответствующей ячейки таблицы
                    map[ "Название" ] = dataItem[ "Название" ];
                    map[ "Тип" ] = dataItem[ "Тип" ];
                    map[ "Преподаватель" ] = dataItem[ "Преподаватель" ];
                    map[ "Аудитория" ] = dataItem[ "Аудитория" ];

                    break;
                }
            }

            // пары на данный день проверили и, к сожалению,
            // не нашли, поэтому переходим на следующий день
            // и начинаем с первой пары
            dateTimeNextLesson = dateTimeNextLesson.addDays(1);
            dateTimeNextLesson.setTime( timeFirstLesson );

            row = findNumberLesson( lrt, dateTimeNextLesson.time() );
            column = dateTimeNextLesson.date().dayOfWeek();

            if ( row < 0 )
                row = 0;

            // перебрали все варианты дней (14 дней)
            // и не обнаружили пару -> расписания нет
            if ( --counter == 0 )
                break;
        }

        // Если перебрали все дни
        if ( maxCounter == counter )
            qDebug() << "Плохо! Похоже таблицы расписаний пусты :(";

        return map;
    }

    static QString infoLesson( const QMap < QString, QVariant > & data )
    {
        QString text;

        text.append( Html::b( data.value( "Название" ).toString() ) );
        text.append( QString( " (%1) в " ).arg( data.value( "Тип" ).toString() ) );
        text.append( Html::color( data.value( "Аудитория" ).toString(), Qt::red, true ) );
        text.append( Html::br() );
        text.append( "Преподаватель: " + data.value( "Преподаватель" ).toString() );

        return text;
    }

    class PathToFile
    {
    public:
        static QString timetableCalls()
        {
            return QDir::toNativeSeparators( qApp->applicationDirPath()
                                             + "\\"
                                             + "Расписание звонков.timetable" );
        }
        static QString timetableLessons_Odd()
        {
            return QDir::toNativeSeparators( qApp->applicationDirPath()
                                             + "\\"
                                             + "Нечетная неделя.timetable" );
        }
        static QString timetableLessons_Even()
        {
            return QDir::toNativeSeparators( qApp->applicationDirPath()
                                             + "\\"
                                             + "Четная неделя.timetable" );
        }
    };
};

#endif // GLOBAL_H
