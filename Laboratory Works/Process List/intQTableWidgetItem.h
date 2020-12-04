#pragma once
#include <QTableWidget>

class intQTableWidgetItem : public QTableWidgetItem
{
public:
	virtual bool operator<(const QTableWidgetItem &other);
};

