#include "simon.h"
#include "ui_simon.h"
#include <QKeyEvent>
#include <QApplication>
#include <iostream>
#include <thread>

Simon::Simon(Model* m,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Simon)
{
    ui->setupUi(this);

    SimonModel = m;

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);

   // the proper way to do a two way connection from view -> model and model -> view
   //connect(this, SIGNAL(modelSignal()), SimonModel, SLOT(displayMessage()));
   // connect(SimonModel, SIGNAL(endModelSignal()), this, SLOT(viewDisplay()));

   //connect(ui->redButton,SIGNAL(clicked(bool)),this,SLOT(redButton_clicked()));

   // View-to-Model connections
   connect(this, SIGNAL(startSignal()), SimonModel, SLOT(startButtonClicked()));
   connect(this, SIGNAL(redSignal()), SimonModel, SLOT(redButtonClicked()));
   connect(this, SIGNAL(yellowSignal()), SimonModel, SLOT(yellowButtonClicked()));
   connect(this, SIGNAL(greenSignal()), SimonModel, SLOT(greenButtonClicked()));
   connect(this, SIGNAL(blueSignal()), SimonModel, SLOT(blueButtonClicked()));

   connect(SimonModel, SIGNAL(disableColorButtonsSignal()), this, SLOT(disableColorButtons()));
   connect(SimonModel, SIGNAL(enableColorButtonsSignal()), this, SLOT(enableColorButtons()));
   connect(SimonModel, SIGNAL(disableStartButtonSignal()), this, SLOT(disableStartButton()));
   connect(SimonModel, SIGNAL(enableStartButtonSignal()), this, SLOT(enableStartButton()));
   connect(SimonModel, SIGNAL(setLevelTextBoxSignal(QString)), this, SLOT(displayLevelTextBox(QString)));
   connect(SimonModel, SIGNAL(setGameStateTextBoxSignal(QString)), this, SLOT(displayGameStateText(QString)));
   connect(SimonModel, SIGNAL(setProgressBarValueSignal(int)), this, SLOT(displayProgressBar(int)));

   //Model-to-View connections to blink colors
   connect(SimonModel, SIGNAL(blinkRedSignalOn()), this, SLOT(blinkRedButtonOn()));
   connect(SimonModel, SIGNAL(blinkGreenSignalOn()), this ,SLOT(blinkGreenButtonOn()));
   connect(SimonModel, SIGNAL(blinkBlueSignalOn()), this ,SLOT(blinkBlueButtonOn()));
   connect(SimonModel, SIGNAL(blinkYellowSignalOn()),this,SLOT(blinkYellowButtonOn()));
   connect(SimonModel, SIGNAL(setColorsWhiteSignal()), this, SLOT(setAllColorButtonsToWhite()));
}

Simon::~Simon()
{
    delete ui;
}

void Simon::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_8)
    {
        ui->redButton->setStyleSheet("background-color:red");
        emit redSignal();
    }

    if(event->key() == Qt::Key_4)
    {
        ui->yellowButton->setStyleSheet("background-color:yellow");
        emit yellowSignal();
    }

    if(event->key() == Qt::Key_6)
    {
        ui->greenButton->setStyleSheet("background-color:green");
        emit greenSignal();
    }

    if(event->key() == Qt::Key_2)
    {
        ui->blueButton->setStyleSheet("background-color:blue");
        emit blueSignal();
    }
}

void Simon::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_8)
    {
        ui->redButton->setStyleSheet("background-color:white");
    }

    if(event->key() == Qt::Key_4)
    {
        ui->yellowButton->setStyleSheet("background-color:white");
    }

    if(event->key() == Qt::Key_6)
    {
         ui->greenButton->setStyleSheet("background-color:white");
    }

    if(event->key() == Qt::Key_2)
    {
         ui->blueButton->setStyleSheet("background-color:white");
    }
}

void Simon::disableColorButtons()
{
    std::cout << "DISABLING BUTTONS" << std::endl;
    ui->redButton->setDisabled(true);
    ui->yellowButton->setDisabled(true);
    ui->greenButton->setDisabled(true);
    ui->blueButton->setDisabled(true);
}

void Simon::enableColorButtons()
{
    std::cout << "ENABLING BUTTONS" << std::endl;
    ui->redButton->setEnabled(true);
    ui->yellowButton->setEnabled(true);
    ui->greenButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
}

void Simon::disableStartButton()
{
    std::cout << "DISABLING START" << std::endl;
    ui->StartButton->setDisabled(true);
}

void Simon::enableStartButton()
{
    std::cout << "ENABLING START" << std::endl;
    ui->StartButton->setEnabled(true);
}

void Simon::displayLevelTextBox(QString text)
{
    ui->LevelBox->setText(text);
}

void Simon::displayGameStateText(QString text)
{
    ui->GameStateBox->setText(text);
}

void Simon::displayProgressBar(int progress)
{
    ui->progressBar->setValue(progress);
}

void Simon::blinkRedButtonOn()
{
    ui->redButton->setStyleSheet("background-color:red");
}

void Simon::blinkYellowButtonOn()
{
    ui->yellowButton->setStyleSheet("background-color:yellow");
}

void Simon::blinkGreenButtonOn()
{
    ui->greenButton->setStyleSheet("background-color:green");
}

void Simon::blinkBlueButtonOn()
{
    ui->blueButton->setStyleSheet("background-color:blue");
}

void Simon::setAllColorButtonsToWhite()
{
    ui->redButton->setStyleSheet("background-color:white");
    ui->yellowButton->setStyleSheet("background-color:white");
    ui->greenButton->setStyleSheet("background-color:white");
    ui->blueButton->setStyleSheet("background-color:white");
}

void Simon::on_StartButton_clicked()
{
    emit startSignal();
}

void Simon::on_redButton_clicked()
{
    emit redSignal();
}

void Simon::on_yellowButton_clicked()
{
    emit yellowSignal();
}

void Simon::on_greenButton_clicked()
{
    emit greenSignal();
}

void Simon::on_blueButton_clicked()
{
    emit blueSignal();
}
