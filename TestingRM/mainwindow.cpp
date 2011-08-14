#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QCoreApplication>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //  ui->setupUi(this);
    back = NULL;
    stack = new QStackedWidget();
    QObject::connect(stack,SIGNAL(currentChanged(int)),this,SLOT(activeWidgetChange(int)));
    stack->addWidget(new Homewidget(stack));
    setCentralWidget(stack);
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::activeWidgetChange(int index){
    QBaseWidget* current = static_cast<QBaseWidget*>(stack->widget(index));
    if(current){
        current->setFocus();
        QMenuBar* menubar = this->menuBar();
        menubar->clear();
        for(int i=0;i<current->GetMenuBar()->actions().count();i++){
            QAction *action = current->GetMenuBar()->actions(i);
            menubar->addAction(action);
        }
        createBasemenu();
    }
    changeWidget(current);
}

void MainWindow::createBasemenu(){
    menuBar()->addAction("Exit",this,SLOT(close()));
}

void MainWindow::changeWidget(QBaseWidget *current){
    if(current){
        QString classname = current->metaObject()->className();
        if(back != NULL){
            delete back;
            back = NULL;
        }
        if(classname == "FirstWidget" || classname == "SecWidget" || classname == "ThiredWidget" || classname == "FourWidget"){
            createOptionBack(current);
        }
        else{
            createOptionExit(current);
        }

    }
}

void MainWindow::createOptionExit(QWidget *current){
    back = new QAction("Exit",this);
    back->setSoftKeyRole(QAction::NegativeSoftKey);
    QObject::connect(back,SIGNAL(triggered()),this,SLOT(close()));
    this->addAction(back);

}

void MainWindow::createOptionBack(QBaseWidget *current){
    back = new QAction("Back",this);
    back->setSoftKeyRole(QAction::NegativeSoftKey);
    QObject::connect(back,SIGNAL(triggered()),this,SLOT(activePreviews()));
    this->addAction(back);
}

int MainWindow::activePreviews(){
    int ret = -1;
    QString currentName = stack->currentWidget()->metaObject()->className();
    QString previous;
    int count = stack->count();
    for(int i=stack->count()-1;i>=0;i--){
        QWidget* w = stack->widget(i);
        if(w->metaObject()->className()==currentName){
            {
                i--;
                previous = stack->widget(i)->metaObject()->className();
                ret = 0;
                stack->setCurrentWidget(stack->widget(i));
                stack->removeWidget(w);
                delete w;

            }
            break;
        }
    }
    return ret;
}


Homewidget::Homewidget(QStackedWidget *stackWidget, QWidget *parent):QBaseWidget(parent){
    BaseStackwidget = stackWidget;
    widget1 = new QPushButton("Shoot");
    QObject::connect(widget1,SIGNAL(clicked()),this,SLOT(createFirstWidget()));
    widget2 = new QPushButton("Inbox");
    QObject::connect(widget2,SIGNAL(clicked()),this,SLOT(createSecWidget()));
    widget3 = new QPushButton("Settings");
    QObject::connect(widget3,SIGNAL(clicked()),this,SLOT(createThiredWidget()));
    widget4 = new QPushButton("Register");
    QObject::connect(widget4,SIGNAL(clicked()),this,SLOT(createFourWidget()));


    createMenus();
    layout->addWidget(widget1);
    layout->addWidget(widget2);
    layout->addWidget(widget3);
    setLayout(layout);
}

Homewidget::~Homewidget(){

}

void Homewidget::createFirstWidget(){
    FirstWidget* first = new FirstWidget(BaseStackwidget);
    BaseStackwidget->addWidget(first);
    BaseStackwidget->setCurrentWidget(first);

}

void Homewidget::createSecWidget(){
    SecWidget* second = new SecWidget(BaseStackwidget);
    BaseStackwidget->addWidget(second);
    BaseStackwidget->setCurrentWidget(second);
}

void Homewidget::createThiredWidget(){
    ThiredWidget* thired = new ThiredWidget(BaseStackwidget);
    BaseStackwidget->addWidget(thired);
    BaseStackwidget->setCurrentWidget(thired);
}

void Homewidget::createFourWidget(){
    FourWidget* four = new FourWidget(BaseStackwidget);
    BaseStackwidget->addWidget(four);
    BaseStackwidget->setCurrentWidget(four);
}


QMenuBar* Homewidget::GetMenuBar() const {
    return menuBar;
}

void Homewidget::createMenus(){
    menuBar = new QMenuBar();

    //action widget 1
    firstWidgetAction = new QAction("Shoot",menuBar);
    menuBar->addAction(firstWidgetAction);
    connect(firstWidgetAction,SIGNAL(triggered()),this,SLOT(createFirstWidget()));

    //action widget 2
    secWidgetAction = new QAction("Inbox",menuBar);
    menuBar->addAction(secWidgetAction);
    connect(secWidgetAction,SIGNAL(triggered()),this,SLOT(createSecWidget()));

    //action widget 3
    thiredWidgetAction = new QAction("Settings",menuBar);
    menuBar->addAction(thiredWidgetAction);
    connect(thiredWidgetAction,SIGNAL(triggered()),this,SLOT(createThiredWidget()));

    //action widget 4
    fourWidgetAction = new QAction("Register",menuBar);
    menuBar->addAction(fourWidgetAction);
    connect(fourWidgetAction,SIGNAL(triggered()),this,SLOT(createFourWidget()));


}

FirstWidget::FirstWidget(QStackedWidget *stackWidget, QWidget *parent):QBaseWidget(parent){
    BaseStackwidget = stackWidget;
    widget2 = new QPushButton("Shoot");
    bool val = QObject::connect(widget2,SIGNAL(clicked()),this,SLOT(createSecWidget()));
    widget3 = new QPushButton("Inbox");
    QObject::connect(widget3,SIGNAL(clicked()),this,SLOT(createThiredWidget()));
    widget4 = new QPushButton("Register");
    QObject::connect(widget4,SIGNAL(clicked()),this,SLOT(createFourWidget()));

    createMenus();

    layout = new QVBoxLayout();
    layout->addLayout(widget2);
    layout->addLayout(widget3);
    layout->addLayout(widget4);

    setLayout(layout);
}





//Setting View Orientations

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded(){
#ifdef Q_OS_SYMBIAN
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}


