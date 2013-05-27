#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QDialog>

namespace Ui {
class ProgressBar;
}

class ProgressBar : public QDialog
{
    Q_OBJECT
    
private:
    Ui::ProgressBar *ui_;
    int progress_;

public:
    explicit ProgressBar(QWidget *parent = 0);
    ~ProgressBar();
    void SetMaximum(int maximum_value = 100);

public slots:
    void slotSetValueOnProgressBar(int progress);

private slots:
    void on_ProgressBar_rejected();
};

#endif // PROGRESSBAR_H
