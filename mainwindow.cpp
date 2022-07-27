#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNovo_triggered()
{
    arquivoAtual.clear();
    ui->textArea->setText(QString());
}


void MainWindow::on_actionAbrir_triggered()
{

    QString nomeArquivo = QFileDialog::getOpenFileName(this,  "Abrir o arquivo");
    QFile arquivo(nomeArquivo);
    arquivoAtual = nomeArquivo;
    if(! arquivo.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Aviso", "Não foi possível abrir o arquivo: " + arquivo.errorString());
        return;
    }else{
        setWindowTitle(nomeArquivo);
        QTextStream in(&arquivo);
        QString texto = in.readAll();
        ui->textArea->setText(texto);
        arquivo.close();
    }
}


void MainWindow::on_actionSalvar_como_triggered()
{
    QString nomeArquivo = QFileDialog::getSaveFileName(this, "Salvar como");
    QFile arquivo(nomeArquivo);
    if(! arquivo.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Aviso", "Não foi possível salvar o arquivo: " + arquivo.errorString());
        return;
    }else{
        arquivoAtual = nomeArquivo;
        setWindowTitle(nomeArquivo);
        QTextStream out(&arquivo);
        QString texto = ui->textArea->toPlainText();
        out<<texto;
        arquivo.close();

    }

}


void MainWindow::on_actionImprimir_triggered()
{
    QPrinter impressora;
    impressora.setPrinterName("Minha impressora");
    QPrintDialog pDialog(&impressora , this);
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Aviso", "Não foi possível imprimir o arquivo: ");
        return;
    }else{
        ui->textArea->print(&impressora);
    }
}


void MainWindow::on_actionSair_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopiar_triggered()
{
    ui->textArea->copy();
}


void MainWindow::on_actionColar_triggered()
{
    ui->textArea->paste();
}


void MainWindow::on_actionDesfazer_triggered()
{
    ui->textArea->undo();
}


void MainWindow::on_actionRecortar_triggered()
{
    ui->textArea->cut();
}

