#include <QMessageBox>
#include <QDebug>

#include "jpegfilter.h"
#include "ui_jpegfilter.h"


JpegFilter::JpegFilter(QWidget *parent) :
        QMainWindow(parent),
        ui_ (new Ui::JpegFilter)
{
    ui_->setupUi(this);
    // default values
    radius_ = 3;
    diviation_ = 1.0;
    blur_parametres_is_set_ = false;
    have_img_to_save = false;
}


JpegFilter::~JpegFilter()
{
    delete ui_;
}


/********************* F U N C T I O N S ***************************************/

void JpegFilter::SetFileNameOnTitle(const QString &file_name)
{
    setWindowTitle(file_name);
}


void JpegFilter::SetInputImage(const QString &file_name)
{
    input_image_.load(file_name);

    // image shouldn't be bigger then 700 px by any edge (I just want it)
    QSize scaled_size = this->scale_size_if_lesser(input_image_.size(), 700);

    QImage image  = input_image_.scaled(scaled_size, Qt::KeepAspectRatio);
    ui_->label_input_->setPixmap(QPixmap::fromImage(image));
}


void JpegFilter::UpdateButtons()
{
    bool input_is_loaded = ui_ -> label_input_ -> pixmap() -> isNull();
    if (false == input_is_loaded) {
        ui_ -> action_blur_image -> setEnabled(true);
    }
    ui_ -> action_save    -> setEnabled(have_img_to_save);
    ui_ -> action_save_as -> setEnabled(have_img_to_save);
}


bool JpegFilter::SaveAs()
{
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Сохранить изображение"),
                                                     QDir::currentPath(),
                                                     tr("Изображения (*.jpg *jpeg *.jpe)")
                                                     );
    if (true == file_name.isEmpty())
        return false;

    return Save(file_name);
}


bool JpegFilter::Save(const QString &file_name)
{
    output_image_.save(file_name, "jpg");
    return true;
}



QSize JpegFilter::scale_size_if_lesser(QSize size, int max_size)
{
    int scale_factor = 1;
    QSize scaled_size = size / max_size; // int - without float part

    if (scaled_size.width() >= 1 && scaled_size.height() >= 1) {
        scale_factor = qMax(scaled_size.height(), scaled_size.width());
    }

    size.scale(size / scale_factor, Qt::KeepAspectRatio);
    return size;
}



/********************* T R I G G E R S ***************************************/

void JpegFilter::on_action_open_triggered()
{
    QString file_path = QFileDialog::getOpenFileName(
                                    this,
                                    tr("Открыть изображение"),
                                    QDir::currentPath(),
                                    tr("Изображения (*.jpg *.jpeg *.jpe *.png)")
                                    );
    if (true == file_path.isEmpty()) {
        return;
    }
    else
    {
        SetFileNameOnTitle(file_path);
        SetInputImage(file_path);
        ui_ -> label_text ->setText(tr("До обработки:"));
        // this->blur_parametres_is_set_ = false;
        UpdateButtons();
    }
}


void JpegFilter::on_action_save_triggered()
{
    QString current_path = windowTitle();
    QString dir = QFileInfo(current_path).dir().path() + "/";
    QString suffix = QFileInfo(current_path).completeSuffix();
    this->Save(dir + tr("output.") + suffix);
}


void JpegFilter::on_action_save_as_triggered()
{
    this->SaveAs();
}


void JpegFilter::on_action_settings_triggered()
{
    SettingsDialog settings_dialog(this);

    settings_dialog.SetBlurRadius(this->radius_);
    settings_dialog.SetDiviation(this->diviation_);
    settings_dialog.exec();

    this->radius_ = settings_dialog.GetBlurRadius();
    this->diviation_ = settings_dialog.GetDiviation();
    this->blur_parametres_is_set_ = true;
}


void JpegFilter::on_action_blur_image_triggered()
{
    if (false == blur_parametres_is_set_)
    {
        this->on_action_settings_triggered();
    }

    QMessageBox::information(this, tr("Сейчас я как всё размою..."),
                    tr("Я хотел бы предупредить,\n"
                    "что процесс размытия по гаусу займёт некоторое время.\n"
                    "Можете выпить чаю и съесть печеньку."),
                    QMessageBox::Ok
                    );

    GaussianBlur blur(radius_, diviation_);
    output_image_ = blur.ApplyGaussianFilterToImage(input_image_);

    QSize scaled_size = this->scale_size_if_lesser(input_image_.size(), 700);
    QImage output = output_image_.scaled(scaled_size, Qt::KeepAspectRatio);

    QMessageBox::information(this, tr("Готово!"),
                    tr("Спасибо что были с нами.\n"
                    "Результат готов и появится после закрытия этого окошка."),
                    QMessageBox::Ok
                    );

    ui_ -> label_text ->setText(tr("После обработки:"));
    ui_ -> label_input_ -> setPixmap(QPixmap::fromImage(output));
    have_img_to_save = true;

    UpdateButtons();
}
