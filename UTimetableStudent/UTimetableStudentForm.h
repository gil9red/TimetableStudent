#ifndef UTimetableStudentForm_h
#define UTimetableStudentForm_h

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QTableWidget>
#include <QHeaderView>
#include <QFile>
#include <QApplication>
#include <QSplitter>

#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QTextCodec>
#include <QScrollBar>

#include <QDir>

#include <QCheckBox>

#include "URangeTimes.h"
#include "Global.h"
#include "QtJson/json.h"

class UTimetableStudentForm: public QWidget
{
    Q_OBJECT

public:
    UTimetableStudentForm( QWidget *parent = 0 );

private:
    void createGUI();
    void init();

private:
    QTimer timer;
    QLabel labelIndicator;

    UListRangeTimes lrt;

    QCheckBox cBoxVisibleTimetableCalls;
    QCheckBox cBoxVisibleTimetableLesson;

    QTableWidget tableTimetableCalls;    

    QTabWidget tabWidgetTimetableLesson;
    QTableWidget tableTimetableLessonEven;
    QTableWidget tableTimetableLessonOdd;

private slots:
    void updateIndicator();
};

#endif // UTimetableStudentForm_h
