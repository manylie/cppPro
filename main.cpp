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
    QWidget *mainWidget;
    QPushButton *button;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QLabel *label4;
    QLabel *label;
    QLabel *label2;
    QLabel *label3;
    QVBoxLayout *layout;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Crear el widget central
    mainWidget = new QWidget(this);  // Cambiar el nombre a 'mainWidget'
    setCentralWidget(mainWidget);

    layout = new QVBoxLayout();
    button = new QPushButton("Botón 1", this);
    connect(button, &QPushButton::clicked, this, &MainWindow::b1Clicked);
    
    button2 = new QPushButton("Botón 2", this);
    connect(button2, &QPushButton::clicked, this, &MainWindow::b2Clicked);
    
    button3 = new QPushButton("Botón 3", this);
    connect(button3, &QPushButton::clicked, this, &MainWindow::b3Clicked);
    
    button4 = new QPushButton("Botón 4", this);
    connect(button4, &QPushButton::clicked, this, &MainWindow::b4Clicked);
    
    label = new QLabel("Label 1", this);
    label2 = new QLabel("Label 2", this);
    label3 = new QLabel("Label 3", this);
    label4 = new QLabel("Label 4", this);

    layout->addWidget(label);
    layout->addWidget(button);
    layout->addWidget(label2);
    layout->addWidget(button2);
    layout->addWidget(label3);
    layout->addWidget(button3);
    layout->addWidget(button4);
    layout->addWidget(label4);
    
    mainWidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    // Los widgets se eliminan automáticamente al eliminar el MainWindow
}

void MainWindow::b1Clicked()
{
    label->setText("Botón 1 presionado");
}

void MainWindow::b2Clicked()
{
    label2->setText("Botón 2 presionado");
}

void MainWindow::b3Clicked()
{
    label3->setText("Botón 3 presionado");
}

void MainWindow::b4Clicked()
{
    label4->setText("Botón 4 presionado");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
