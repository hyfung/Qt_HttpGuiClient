#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->urlInput->setText("https://google.com");
    ui->urlInput->setToolTip("Enter the url here");
    ui->urlInput->setPlaceholderText("Enter the url here");
    ui->headers->setPlaceholderText("Http reponse headers will be shown here");
    ui->response->setPlaceholderText("Http response will be shown here");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_getButton_clicked()
{
    QString url = ui->urlInput->text();

    if (url == "")
    {
        return;
    }

    QEventLoop loop;
    QNetworkAccessManager *pQNAM = new QNetworkAccessManager;
    QNetworkRequest request = QNetworkRequest(url);
    QNetworkReply* pReply = pQNAM->get(request);

    connect(pReply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray rep = pReply->readAll();
    QString sHeaders;

    for (auto &pair : pReply->rawHeaderPairs())
    {
        sHeaders += pair.first;
        sHeaders += ":";
        sHeaders += pair.second;
        sHeaders += "\n";
    }

    ui->headers->setText(sHeaders);
    ui->response->setText(QString::fromUtf8(rep));
}

void MainWindow::on_exitButton_clicked()
{
    exit(0);
}
