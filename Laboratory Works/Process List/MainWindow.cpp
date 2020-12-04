#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	timer = new QTimer;
	timer->setInterval(2000);
	connect(timer, SIGNAL(timeout()), this, SLOT(UpdateProcesses()));
	connect(ui.tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(KillProcess(QTableWidgetItem*)));

	UpdateProcesses();
	timer->start();
}

QList<std::tuple<QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*>> MainWindow::GetProcesses()
{
	PROCESSENTRY32W pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32W);

	HANDLE ProcessesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	QList<std::tuple<QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*>> ProcessList;

	if (ProcessesSnapshot == INVALID_HANDLE_VALUE)
	{
		return ProcessList;
	}

	Process32FirstW(ProcessesSnapshot, &pe32);

	do
	{
		ProcessList.push_back(ParseProcess(pe32));
	}
	while (Process32NextW(ProcessesSnapshot, &pe32));

	CloseHandle(ProcessesSnapshot);

	return ProcessList;
}

SIZE_T MainWindow::GetProcMemory(unsigned long PID)
{
	auto ProcHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID);
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(ProcHandle, &pmc, sizeof(pmc));
	return pmc.WorkingSetSize / 1024 / 1024;
}

void MainWindow::UpdateProcesses()
{
	auto ProcessList = GetProcesses();
	ui.tableWidget->setSortingEnabled(false);
	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(ProcessList.size());

	int i = 0;
	for (auto& process : ProcessList)
	{
		ui.tableWidget->setItem(i, 0, std::get<0>(process));
		ui.tableWidget->setItem(i, 1, std::get<1>(process));
		ui.tableWidget->setItem(i, 2, std::get<2>(process));
		ui.tableWidget->setItem(i, 3, std::get<3>(process));
		++i;
	}

	ui.tableWidget->setSortingEnabled(true);
}

void MainWindow::KillProcess(QTableWidgetItem* item)
{
	bool ok;
	item->text().toInt(&ok);
	QProcess proc;

	if (ok)
	{
		proc.start("taskkill /F /PID " + item->text());
		proc.waitForFinished();
	}
	else
	{
		proc.start("taskkill /F /IM " + item->text());
		proc.waitForFinished();
	}

	UpdateProcesses();
}

std::tuple<QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*> MainWindow::ParseProcess(PROCESSENTRY32W& Process)
{
	auto* Name = new QTableWidgetItem(QString::fromWCharArray(Process.szExeFile));
	auto* PID = new QTableWidgetItem(QString::number(Process.th32ProcessID));

	auto Memory = GetProcMemory(Process.th32ProcessID);
	auto* RAM = new QTableWidgetItem(QString::number(Memory));

	auto* Priority = new QTableWidgetItem(ParsePriority(Process.th32ProcessID));

	std::tuple<QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*, QTableWidgetItem*> parsed_process(Name, PID, RAM, Priority);

	return parsed_process;
}

QString MainWindow::ParsePriority(DWORD PID)
{
	auto hProc = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID);
	DWORD priority = GetPriorityClass(hProc);
	QString priority_string;

	switch (priority)
	{
		case ABOVE_NORMAL_PRIORITY_CLASS:
        priority_string = QString::fromWCharArray(L"Выше среднего");
        break;

	    case BELOW_NORMAL_PRIORITY_CLASS:
	        priority_string = QString::fromWCharArray(L"Ниже среднего");
	        break;

	    case NORMAL_PRIORITY_CLASS:
	        priority_string = QString::fromWCharArray(L"Средний");
	        break;

	    case HIGH_PRIORITY_CLASS:
	        priority_string = QString::fromWCharArray(L"Высокий");
	        break;

	    case IDLE_PRIORITY_CLASS:
	        priority_string = QString::fromWCharArray(L"Низкий");
	        break;

	    case REALTIME_PRIORITY_CLASS:
	        priority_string = QString::fromWCharArray(L"Реального времени");
	        break;

	    default:
	        priority_string = QString::fromWCharArray(L"Не определён");
	        break;
	}

	return priority_string;
}