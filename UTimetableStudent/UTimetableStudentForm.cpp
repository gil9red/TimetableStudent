#include "UTimetableStudentForm.h"

/// PUBLIC
UTimetableStudentForm::UTimetableStudentForm(QWidget *parent)
    : QWidget(parent)
{
    createGUI();           

    U::fillListRangeTimes( &lrt, U::PathToFile::timetableCalls() );
    U::fillTimetableCalls( &tableTimetableCalls, &lrt );

    init();

    U::fillTimetableLesson( &tableTimetableLessonOdd, U::PathToFile::timetableLessons_Odd() );
    U::fillTimetableLesson( &tableTimetableLessonEven, U::PathToFile::timetableLessons_Even() );

    tableTimetableLessonOdd.hideColumn( TableLessons::Sunday );
    tableTimetableLessonEven.hideColumn( TableLessons::Sunday );

    updateIndicator();

    tabWidgetTimetableLesson.setCurrentWidget( U::isEven( QDate::currentDate().weekNumber() ) ?
                                                   &tableTimetableLessonEven :
                                                   &tableTimetableLessonOdd );

    timer.start();
}

/// PRIVATE
void UTimetableStudentForm::createGUI()
{
    setWindowTitle( "Расписание студента" );

    QAbstractItemView::SelectionBehavior behavior = QAbstractItemView::SelectRows;
    QAbstractItemView::SelectionMode mode = QAbstractItemView::SingleSelection;
    QAbstractItemView::EditTriggers triggers = QAbstractItemView::NoEditTriggers;

    bool alternatingRowColors = true;
    bool wordWrap = true;

    tableTimetableCalls.setSelectionBehavior( behavior );
    tableTimetableCalls.setSelectionMode( mode );
    tableTimetableCalls.setAlternatingRowColors( alternatingRowColors );

    QStringList labelsTimetableCalls;
    labelsTimetableCalls << "Пара"
                         << "Время";
    tableTimetableCalls.setColumnCount( labelsTimetableCalls.size() );
    tableTimetableCalls.setHorizontalHeaderLabels( labelsTimetableCalls );


    tabWidgetTimetableLesson.addTab( &tableTimetableLessonEven, "Четная" );
    tabWidgetTimetableLesson.addTab( &tableTimetableLessonOdd, "Нечетная" );
    tabWidgetTimetableLesson.setTabPosition( QTabWidget::South );

    tableTimetableLessonEven.setSelectionBehavior( behavior );
    tableTimetableLessonOdd.setSelectionBehavior( behavior );

    tableTimetableLessonEven.setSelectionMode( mode );
    tableTimetableLessonOdd.setSelectionMode( mode );

    tableTimetableLessonEven.setAlternatingRowColors( alternatingRowColors );
    tableTimetableLessonOdd.setAlternatingRowColors( alternatingRowColors );

    tableTimetableLessonOdd.setEditTriggers( triggers );
    tableTimetableLessonEven.setEditTriggers( triggers );
    tableTimetableCalls.setEditTriggers( triggers );

    tableTimetableLessonOdd.setWordWrap( wordWrap );
    tableTimetableLessonEven.setWordWrap( wordWrap );

    tableTimetableCalls.horizontalHeader()->setResizeMode( QHeaderView::Fixed );
    tableTimetableCalls.verticalHeader()->setResizeMode( QHeaderView::Fixed );

    QSplitter *splitter = new QSplitter();
    splitter->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    splitter->setChildrenCollapsible( false );
    splitter->addWidget( &tableTimetableCalls );
    splitter->addWidget( &tabWidgetTimetableLesson );

    QHBoxLayout *layoutCheckbox = new QHBoxLayout();
    layoutCheckbox->setSpacing( 0 );
    layoutCheckbox->addWidget( &cBoxVisibleTimetableCalls );
    layoutCheckbox->addWidget( &cBoxVisibleTimetableLesson );

    QVBoxLayout *vBoxLayout = new QVBoxLayout();
    vBoxLayout->setMargin(5);
    vBoxLayout->setSpacing(5);
    vBoxLayout->addWidget( &labelIndicator );
    vBoxLayout->addLayout( layoutCheckbox );
    vBoxLayout->addWidget( splitter );

    setLayout(vBoxLayout);

//    labelIndicator.setTextInteractionFlags( Qt::TextSelectableByMouse );

    connect( &timer, SIGNAL( timeout() ), SLOT( updateIndicator() ) );

    timer.setInterval(500);


    cBoxVisibleTimetableCalls.setText( "Расписание звонков" );
    cBoxVisibleTimetableLesson.setText( "Расписание занятий" );

    connect( &cBoxVisibleTimetableCalls, SIGNAL( toggled(bool) ),
             &tableTimetableCalls, SLOT( setVisible(bool) ) );
    connect( &cBoxVisibleTimetableLesson, SIGNAL( toggled(bool) ),
             &tabWidgetTimetableLesson, SLOT( setVisible(bool) ) );

    cBoxVisibleTimetableCalls.setChecked( false );
    cBoxVisibleTimetableLesson.setChecked( false );

    tableTimetableCalls.setVisible( cBoxVisibleTimetableCalls.isChecked() );
    tabWidgetTimetableLesson.setVisible( cBoxVisibleTimetableLesson.isChecked() );
}
void UTimetableStudentForm::init()
{
    QStringList labelsTableLesson;
    labelsTableLesson << "Пара" << U::daysOfWeeks();

    int columnCount = labelsTableLesson.size();
    int rowCount = tableTimetableCalls.rowCount();

    QStringList emptyStringList;
    for (int i = 0; i < rowCount; i++)
        emptyStringList << " ";

    tableTimetableLessonEven.setColumnCount( columnCount );
    tableTimetableLessonOdd.setColumnCount( columnCount );

    tableTimetableLessonEven.setHorizontalHeaderLabels( labelsTableLesson );
    tableTimetableLessonOdd.setHorizontalHeaderLabels( labelsTableLesson );

    tableTimetableLessonEven.setRowCount( rowCount );
    tableTimetableLessonOdd.setRowCount( rowCount );

    tableTimetableLessonEven.setVerticalHeaderLabels( emptyStringList );
    tableTimetableLessonOdd.setVerticalHeaderLabels( emptyStringList );

    tableTimetableCalls.setVerticalHeaderLabels( emptyStringList );

    for ( int i = 0; i < rowCount; i++ )
        for ( int j = 0; j < columnCount; j++ )
        {
            tableTimetableLessonEven.setItem( i, j, new QTableWidgetItem() );
            tableTimetableLessonOdd.setItem( i, j, new QTableWidgetItem() );
        }

    for ( int i = 0; i < tableTimetableCalls.rowCount(); i++ )
    {
        QTableWidgetItem *item = tableTimetableCalls.item( i, numberOfLesson );

        tableTimetableLessonEven.setItem( i, numberOfLesson, item->clone() );
        tableTimetableLessonOdd.setItem( i, numberOfLesson, item->clone() );
    }
}

/// PRIVATE SLOTS
void UTimetableStudentForm::updateIndicator()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

//    // TODO REMOVE THIS
//    currentDateTime.setDate( QDate( 2013, 10, 29 ) );
//    currentDateTime.setTime( QTime( 13, 10, 43 ) );

    QDate currentDate = currentDateTime.date();
    QTime currentTime = currentDateTime.time();

    // получим индекс времени в списке диапазонов времени
    int index = lrt.indexOf( currentTime );

    int type = -1;

    // если текущее время было обнаружено
    if( index >= 0 )
        type = lrt.list.at( index ).d_data.toInt();

    int numberLesson = -1;

    QString lesson;

    QString tempText;

//    if ( index < 0 )
//        lesson = "Занятия закончились";
//    else
//    {
    switch ( type )
    {
    case Recess:
        lesson = "Сейчас перемена";
        lesson = U::Html::color( lesson, QColor( "#FC0FC0" ), true );
        break;

    case Lesson:
        // Определим номер пары
        numberLesson = U::findNumberLesson( lrt, currentTime );

        tempText = QString( "Сейчас %1-ая пара" ).arg( numberLesson );
        tempText = U::Html::color( tempText, Qt::blue, true );

        lesson = tempText;
        lesson.append( QString( " (%1)" ).arg( lrt.list[index].toString() ) );

        break;

    default:
        lesson = "";
    }
//    }

    int dayOfWeek = currentDate.dayOfWeek();

    QString textIndicator;

    tempText = QString( "%1 %2 (%3)" )
            .arg( currentTime.toString( timeFormat ) )
            .arg( currentDate.toString( dateFormat ) )
            .arg( U::daysOfWeeks().at( dayOfWeek - 1 ) );

    tempText = U::Html::big( tempText );
    tempText = U::Html::b( tempText );
    tempText.append( U::Html::br() );
    textIndicator.append( tempText );

    tempText = QString( " %1 неделя (%2-я неделя)" )
                     .arg( U::evenWeek( currentDate ) )
                     .arg( currentDate.weekNumber() );

    tempText = U::Html::small( tempText );
    tempText = U::Html::b( tempText );
    tempText = U::Html::color( tempText, Qt::gray );
    tempText.append( U::Html::hr() );

    textIndicator.append( tempText );
    textIndicator.append( lesson );

    QTableWidget *table;

    // проверим четность недели
    if ( U::isEven( currentDate.weekNumber() ) )
        table = &tableTimetableLessonEven;
    else
        table = &tableTimetableLessonOdd;

    bool nowLesson = false;

    if ( numberLesson >= 0 )
    {
        QColor color = QColor( "#50C878" );

        int row = numberLesson - 1; // индекс в таблицах с 0 начинается
        int column = dayOfWeek;

        U::fillRowTable( &tableTimetableCalls, row, color );

        // В списке укажем индексы какие ячеек закрасить
        QList < QPair < int, int > > listIndex;
        listIndex << QPair < int, int > ( row, column );
        listIndex << QPair < int, int > ( row, numberOfLesson );

        // закрасим ячейки
        U::fillCellTable( table, listIndex, color );

        // определим какая сейчас у нас идет пара
        QTableWidgetItem * item = table->item( row, column );
        QtJson::JsonObject data = item->data( Qt::UserRole ).toMap();

        nowLesson = !data.isEmpty();

        // если данная ячейка содержит пару
        if( nowLesson )
        {
//            text.append( QString( "%1 (%2)<br> %3<br> %4 ауд." )
//                         .arg( data.value( "Название" ).toString() )
//                         .arg( data.value( "Тип" ).toString() )
//                         .arg( data.value( "Преподаватель" ).toString() )
//                         .arg( data.value( "Аудитория" ).toString() ) );

            textIndicator.append( ":" );
            textIndicator.append( U::Html::br() );
            textIndicator.append( U::infoLesson( data ) );
        }               

    }else
    {
        U::fillTable( &tableTimetableCalls );
        U::fillTable( table );
    }

    //    if ( index >= 0 )
    //    {
            QTime nextTime;

            // заглянем вперед
            int nextIndex = index + 1;

            if ( nextIndex >= lrt.list.size() )
                nextIndex = lrt.list.size() - 1;

            if(  nextIndex != lrt.list.size() - 1 )
                nextTime = lrt.list.at( nextIndex ).time1;
            else
                nextTime = lrt.list.at( nextIndex ).time2;

            int second = qAbs( currentTime.secsTo( nextTime ) );

            if ( type == Recess || index < 0 )
                textIndicator.append( " до звонка осталось " );

            else
            {
                if( nowLesson )
                    textIndicator.append( U::Html::br() );

                textIndicator.append( U::Html::br() );
                textIndicator.append( "До звонка осталось " );
            }

            tempText = U::longStringTime2( second );

            textIndicator.append( U::Html::color( tempText, Qt::darkGreen, true ) );
    //    }

    // Определим ближайшую пару
    QVariantMap map = U::searchNextLesson( &tableTimetableCalls,
                                           &tableTimetableLessonEven,
                                           &tableTimetableLessonOdd,
                                           lrt,
                                           currentDateTime );

    if ( map.isEmpty() )
    {
        labelIndicator.setText( "Произошла ошибка! Похоже расписания нету :(" );
        return;
    }

    textIndicator.append( U::Html::hr() );

    QDateTime dateTimeNextLesson;
    dateTimeNextLesson.setDate( map[ "Дата" ].toDate() );
    dateTimeNextLesson.setTime( map[ "Время" ].toTime() );

    QDate dateNextLesson = dateTimeNextLesson.date();
    QTime timeNextLesson = dateTimeNextLesson.time();

    // следующая пара будет на этой недели
    bool nextLessonOnCurrentWeek = U::evenWeek( currentDate ) == U::evenWeek( dateNextLesson );

    // номер следующей пары
    int numberNextLesson = map[ "Номер пары" ].toInt();

    // дней до следующей пары
    int daysBeforeNextLesson = qAbs( currentDateTime.daysTo( dateTimeNextLesson ) );

    tempText = "Следующая пара";
    tempText = U::Html::color( tempText, Qt::darkBlue, true );
    tempText.append( " будет " );

    textIndicator.append( tempText );

    // если следующая лекция будет не на текущей недели
    if ( !nextLessonOnCurrentWeek )
    {
        tempText = " на следующей недели";
        tempText = U::Html::color( tempText, Qt::darkRed, true );
        tempText.append( ":" );
        textIndicator.append( tempText );
    }

    if ( daysBeforeNextLesson == 0 )
    {
       textIndicator.append( U::Html::color( "сегодня", Qt::darkCyan, true ) );

//       int beforeNextLesson = qAbs( numberLesson - numberNextLesson );
       int secondBeforeNextLesson = qAbs( currentTime.secsTo( timeNextLesson ) );

//       textIndicator.append( ", до следующей пары осталось" );
       textIndicator.append( ", осталось" );
//       textIndicator.append( QString(": %1-а пар" ).arg( beforeNextLesson ) );

       tempText = U::longStringTime2( secondBeforeNextLesson );
       tempText = U::Html::color( tempText, Qt::darkGreen, true );

       textIndicator.append( QString( " %1" ).arg( tempText ) );



    }else if ( daysBeforeNextLesson == 1 )
        textIndicator.append( U::Html::color( "завтра", Qt::darkCyan, true ) );

    else if ( daysBeforeNextLesson == 2 )
        textIndicator.append( U::Html::color( "послезавтра", Qt::darkCyan, true ) );

//    else if ( daysBeforeNextLesson > 2 )
//    {
//        textIndicator.append( U::Html::br() );
//        textIndicator.append( QString( "%1 %2 (%3)" )
//                              .arg( timeNextLesson.toString( timeFormat ) )
//                              .arg( dateNextLesson.toString( dateFormat ) )
//                              .arg( map[ "День недели" ].toString() ) );
//    }else
    {
        textIndicator.append( ":" );
        textIndicator.append( U::Html::br() );
        textIndicator.append( QString( "%1 (%4-я пара) %2 (%3)" )
                              .arg( timeNextLesson.toString( timeFormat ) )
                              .arg( dateNextLesson.toString( dateFormat ) )
                              .arg( map[ "День недели" ].toString() )
                              .arg( numberNextLesson ) );
    }

//    textIndicator.append( QString( "<br>Следующая пара %1-я" )
//                          .arg( numberNextLesson ) );

    textIndicator.append( U::Html::br() );
    textIndicator.append( U::infoLesson( map ) );
//    textIndicator.append( QString( " %2 (%3), %4, %5 ауд." )
//                          .arg( map[ "Название" ].toString() )
//            .arg( map[ "Тип" ].toString() )
//            .arg( map[ "Преподаватель" ].toString() )
//            .arg( map[ "Аудитория" ].toString() ) );

    textIndicator.append( U::Html::hr() );

    labelIndicator.setText(textIndicator);
}
