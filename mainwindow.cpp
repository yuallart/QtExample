#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QString imageLocation = *new QString(":/resource/images/image.jpg");
    ui->label->setPixmap(QPixmap(imageLocation));
    ui->label->setScaledContents(true);
}

MainWindow::~MainWindow() {
    delete ui;
}


