#include <QApplication>
#include <QMainWindow>

class MainWindow : public QMainWindow{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QWidget* mainWidget;
};
MainWindow::~MainWindow(){}    
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    mainWidget= new QWidget(this);
    setCentralWidget(mainWidget);
}
int main (int argc , char *argv[]){
    QApplication a( argc , argv);
    MainWindow w;
    w.show();
    return a.exec();
}