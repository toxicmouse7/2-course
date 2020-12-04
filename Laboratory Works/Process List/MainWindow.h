#pragma once

#include <QtWidgets/QMainWindow>
#include <QTableWidgetItem>
#include <QProcess>
#include <QTimer>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;
	QTimer* timer;

	std::tuple<QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*> ParseProcess(PROCESSENTRY32W& Process);
    QString ParsePriority(DWORD PID);
	QList<std::tuple<QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*>> GetProcesses();
    SIZE_T GetProcMemory(unsigned long PID);
	

private slots:
	void UpdateProcesses();
	void KillProcess(QTableWidgetItem* item);
	
};
