#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui>

class QBaseWidget;
class QPushButton;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    void changeWidget(QBaseWidget* current);
    void createBasemenu();
    void createOptionBack(QBaseWidget* current);
    void createOptionExit(QWidget* current);
    QAction* back;


    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

private:
    //  Ui::MainWindow *ui;
public slots :
    //    void openShoot();
    //    void openInbox();
    //    void openSettings();
    //    void openRegister();
    int activePreviews();

private slots :
    void activeWidgetChange(int index);
public :
    Ui::MainWindow *ui;
    QStackedWidget *stack;
private :
    QPushButton* btnOpenShoot();
    QPushButton* btnOpenInbox();
    QPushButton* btnOpenSettings();
    QPushButton* btnOpenRegister();

};

//class Basewidget
class QBaseWidget : public QWidget {
    Q_OBJECT
public :
    QBaseWidget(QWidget* parent = 0){

    }
    virtual ~QBaseWidget(){

    }
public :
    virtual QMenuBar* GetMenuBar() const = 0;
protected :
    QMenuBar* menuBar;
    QStackedWidget * BaseStackwidget;
};


//class HomeWidget
class Homewidget : public QBaseWidget {
    Q_OBJECT

public :
    Homewidget(QStackedWidget* stackWidget,QWidget* parent=0 );
    ~Homewidget();
    QMenuBar* GetMenuBar() const;
    void createMenus();

public slots :
    void createFirstWidget();
    void createSecWidget();
    void createThiredWidget();
    void createFourWidget();
private :
    QMenuBar *menuBar;
    QPushButton *widget1;
    QPushButton *widget2;
    QPushButton *widget3;
    QPushButton *widget4;


    QVBoxLayout *layout;

    QAction *firstWidgetAction;
    QAction *secWidgetAction;
    QAction *thiredWidgetAction;
    QAction *fourWidgetAction;

};


//class FirstWidget

class FirstWidget: public QBaseWidget {
    Q_OBJECT

public :
    FirstWidget(QStackedWidget* stackWidget, QWidget* parent=0);
    ~FirstWidget(){

    }
    QMenuBar* GetMenuBar() const;
    void createMenus();

public slots :
    void createSecWidget();
    void createThiredWidget();
    void createFourWidget();

private :
    QMenuBar *menuBar;
    QPushButton *widget2;
    QPushButton *widget3;
    QPushButton *widget4;
    QVBoxLayout *layout;


    QAction *secWidgetAction;
    QAction *thiredWidgetAction;
    QAction *fourWidgetAction;

};


//class SecondWidget

class SecWidget: public QBaseWidget {
    Q_OBJECT

public :
    SecWidget(QStackedWidget* stackWidget, QWidget* parent=0);
    ~SecWidget(){
    }
    QMenuBar* GetMenuBar() const;
    void createMenu();

public slots :

    void createThiredWidget();
    void createFourWidget();

private :
    QMenuBar *menuBar;


    QPushButton *widget3;
    QPushButton *widget4;
    QVBoxLayout *layout;

    // QLabel *thiredWidgetLabel;


    QAction *thiredWidgetAction;
    QAction *fourWidgetAction;

};


class ThiredWidget: public QBaseWidget {
    Q_OBJECT

public :
    ThiredWidget(QStackedWidget* stackWidget, QWidget* parent=0);
    ~ThiredWidget(){
    }
    QMenuBar* GetMenuBar() const;
    void createMenu();

public slots :

    void createFourWidget();

private :
    QMenuBar *menuBar;
    QLabel *widget4;
    QPushButton *widget4;

    QVBoxLayout *layout;
    QLabel *fourWidgetLabel;
    QAction *fourWidgetAction;


};

class FourWidget: public QBaseWidget {
    Q_OBJECT

public :
    FourWidget(QStackedWidget* stackWidget, QWidget* parent=0);
    ~ThiredWidget(){
    }
    QMenuBar* GetMenuBar() const;
    void createMenu();

public slots :

    void createFourdWidget();

private :
    QMenuBar *menuBar;

    QVBoxLayout *layout;
    QLabel *fourWidgetLabel;

};

#endif // MAINWINDOW_H
