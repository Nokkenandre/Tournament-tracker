#pragma once

#include <QDialog>
#include <QMap>
#include <QString>
#include <QVariant>

class QVBoxLayout;
class QWidget;

// Struct to define each field
struct Field {
    QString name;
    enum Type { Text, Dropdown } type;
    QStringList options;        // For dropdowns
    QStringList tooltips;       // Optional tooltips for dropdowns
};

class DynamicInputDialog : public QDialog {
    Q_OBJECT

public:
    DynamicInputDialog(const QString windowTitle, const QList<Field>& fields, QWidget* parent = nullptr);
    QMap<QString, QString> getValues() const;

private:
    QMap<QString, QWidget*> inputWidgets;
    QVBoxLayout* layout;
};
