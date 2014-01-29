#include <QApplication>
#include "UTimetableStudentForm.h"

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    QTextCodec::setCodecForCStrings( QTextCodec::codecForName( codec ) );

    UTimetableStudentForm w;   
    w.show();

    return app.exec();
}
