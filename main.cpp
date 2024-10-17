
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void b1Clicked();
    void b2Clicked();
    void b3Clicked();
    void b4Clicked();
private:
    QLabel* l1;
    QLabel* l2;
    QLabel* l3;
    QLabel* l4;
    QWidget *mainWidget;
    QVBoxLayout *layout;
    QLabel* myLabel(const QString &text, QLayout *layout);
    QPushButton* newBtnX(const QString &text,void(MainWindow::*slot)() ,QLayout *layout);
};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Crear el widget central
    mainWidget = new QWidget(this);  // Cambiar el nombre a 'mainWidget'
    setCentralWidget(mainWidget);

    layout = new QVBoxLayout();
    newBtnX("er1",&MainWindow::b1Clicked,layout);
    newBtnX("er2",&MainWindow::b2Clicked,layout);
    newBtnX("er3",&MainWindow::b3Clicked,layout);
    newBtnX("er4",&MainWindow::b4Clicked,layout);
    l1 = myLabel("b1",layout);
    l2=myLabel("b2",layout);
    l3=myLabel("b3",layout);
    l4=myLabel("b4",layout);
    mainWidget->setLayout(layout);

}

MainWindow::~MainWindow()
{
    // Los widgets se eliminan automáticamente al eliminar el MainWindow
}
QLabel* MainWindow:: myLabel(const QString &text, QLayout *layout){
    QLabel *label = new QLabel (text,this);
    layout->addWidget(label);
    return label;
}

QPushButton* MainWindow::newBtnX(const QString &text, void (MainWindow::*slot)(), QLayout *layout){
    QPushButton *button= new QPushButton(text,this);
    connect(button, &QPushButton::clicked,this, slot);
    layout->addWidget(button);
    return button;
}
void MainWindow::b1Clicked()
{
    l1->setText("Botón1 presionado");
    
}

void MainWindow::b3Clicked()
{
    l2->setText("Botón b3 presionado");
    
}
void MainWindow::b2Clicked()
{
    l3->setText("Botón b2 presionado");
    
}
void MainWindow::b4Clicked()
{
    l4->setText("boton b4 presionado");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
