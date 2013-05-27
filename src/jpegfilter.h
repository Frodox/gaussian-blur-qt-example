#ifndef JPEGFILTER_H
#define JPEGFILTER_H

#include <QMainWindow>
#include <QFileDialog>
#include <settingsdialog.h>
#include <gaussianblur.h>

namespace Ui {
class JpegFilter;
}

class JpegFilter : public QMainWindow
{
    Q_OBJECT

private:
    QImage input_image_;
    int radius_;
    double diviation_;
    bool blur_parametres_is_set_;
    Ui::JpegFilter *ui_;

public:
    explicit JpegFilter(QWidget *parent = 0);
    ~JpegFilter();
    void SetFileNameOnTittle(const QString &file_name);
    void SetInputImage(const QString &file_name);

private slots:
    void on_action_open_triggered();
    void on_action_save_triggered();
    void on_action_save_as_triggered();
    void on_action_settings_triggered();
    void on_action_blur_image_triggered();
};

#endif // JPEGFILTER_H
