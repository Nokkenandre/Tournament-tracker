#include "input_dialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QStandardItemModel>
#include <QStandardItem>

DynamicInputDialog::DynamicInputDialog(const QString window_title, const QList<Field>& fields, QWidget* parent)
    : QDialog(parent) {
    setWindowTitle(window_title);
    layout = new QVBoxLayout(this);

    for (const auto& field : fields) {
        QLabel* label = new QLabel(field.name, this);
        layout->addWidget(label);

        QWidget* input = nullptr;

        if (field.type == Field::Text) {
            auto* lineEdit = new QLineEdit(this);
            input = lineEdit;

        } else if (field.type == Field::Dropdown) {
            auto* comboBox = new QComboBox(this);

            auto* model = new QStandardItemModel(field.options.size(), 1, comboBox);
            for (int i = 0; i < field.options.size(); ++i) {
                auto* item = new QStandardItem(field.options[i]);
                if (i < field.tooltips.size())
                    item->setToolTip(field.tooltips[i]);
                model->setItem(i, 0, item);
            }

            comboBox->setModel(model);
            input = comboBox;
        }

        if (input) {
            inputWidgets[field.name] = input;
            layout->addWidget(input);
        }
    }

    auto* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QMap<QString, QString> DynamicInputDialog::getValues() const {
    QMap<QString, QString> result;

    for (auto it = inputWidgets.begin(); it != inputWidgets.end(); ++it) {
        auto* widget = it.value();
        if (auto* lineEdit = qobject_cast<QLineEdit*>(widget)) {
            result[it.key()] = lineEdit->text();
        } else if (auto* comboBox = qobject_cast<QComboBox*>(widget)) {
            result[it.key()] = comboBox->currentText();
        }
    }

    return result;
}
