#ifndef JPEGFILTER_H
#define JPEGFILTER_H

#include <QMainWindow>
#include <QFileDialog>

#include "settingsdialog.h"
#include "gaussianblur.h"

namespace Ui {
    class JpegFilter;
}

class JpegFilter : public QMainWindow
{
    Q_OBJECT

private:
    QImage input_image_;
    QImage output_image_;

    int radius_;
    double diviation_;
    bool blur_parametres_is_set_;
    bool have_img_to_save;

    Ui::JpegFilter *ui_;


    /* F u n c s */

    void SetFileNameOnTitle(const QString &file_name);
    void SetInputImage(const QString &file_name);
    void UpdateButtons();
    bool Save(const QString &file_name);
    bool SaveAs();
    QSize scale_size_if_lesser(QSize size, int max_size);

private slots:
    void on_action_open_triggered();
    void on_action_save_triggered();
    void on_action_save_as_triggered();
    void on_action_settings_triggered();
    void on_action_blur_image_triggered();

public:
    explicit JpegFilter(QWidget *parent = 0);
    ~JpegFilter();
};

#endif // JPEGFILTER_H
