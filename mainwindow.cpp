/*include headers*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtWebKitWidgets/QtWebKitWidgets>
#include <QUrl>
#include "dialog.h"
#include <QSyntaxHighlighter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->URLWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    file_path = " ";                        // Set the file path to nothing
    ui->plainTextEdit->setPlainText(" ");   // Thanos snap all the text from the code editor
    ui->webView->reload();
}

void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();               // cut the selected text in the code editor
}

void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();            // paste text from clipboard
}

void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();             // copy text to the clipboard
}

void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();             // undo
}

void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();             // redo
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a file");                   // create a file dialog named filename
    QFile file(filename);                                                                   // create pointer to filename
    file_path = filename;                                                                   // the file path = file
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){                                      // if the file can't open
        QMessageBox::warning(this, "Warning", "Can't open file: " + file.errorString());    // create a warning
        return;
    }
        setWindowTitle(filename + " - BlueTagz");
        QTextStream in(&file);
        QString text = in.readAll();
        ui->plainTextEdit->setPlainText(text);
        ui->webView->load(QUrl::fromLocalFile(filename));
        ui->webView->show();
        file.close();
}

void MainWindow::on_actionAbout_QT_Framework_triggered()
{
    QMessageBox::aboutQt(this, "About the QT Framework");
}

void MainWindow::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save As");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Can't Save file: " + file.errorString());
        return;
    }
    file_path = filename;
    setWindowTitle(filename + " - BlueTagz");
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out << text;
    ui->webView->load(QUrl::fromLocalFile(filename));
    ui->webView->show();
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    if(file_path==" ") {
        on_actionSave_As_triggered();
    }
    QFile file(file_path);
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out << text;
    file.close();
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Can't Save file: " + file.errorString());
        return;
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->webView->reload();
}

void MainWindow::on_actionsercet_message_box_triggered()
{
    Dialog easteregg;
    easteregg.setModal(true);
    easteregg.exec();
}

void MainWindow::on_actionOpen_from_URL_triggered()
{
    ui->URLWidget->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->webView->load(ui->URLBox->text());
}
