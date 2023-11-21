#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QScrollArea>

class TitleBar;
class SideBar;
class ContentPage;
class PlayController;
class MediaPlayer;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    void paintEvent(QPaintEvent* ev) override;
    void resizeEvent(QResizeEvent *event) override;

private:

    TitleBar* title_bar_ = nullptr;
    SideBar* side_bar_ = nullptr;
    ContentPage* content_page_ = nullptr;
    QScrollArea* content_area_ = nullptr;
    PlayController* play_controller_ = nullptr;

    std::shared_ptr<MediaPlayer> media_player_ = nullptr;
};
#endif // MAINWINDOW_H
