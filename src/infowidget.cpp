/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "infowidget.h"
#include "../info/infogui.h"
#include "../info/devicemanager.h"

#include <QDebug>
#include <QPointer>
#include <QPainter>
#include <QStyleOption>
#include <QDBusArgument>

InfoWidget::InfoWidget(QString machine, QWidget *parent) :
    QWidget(parent), arch(machine)
{
    qDebug() << Q_FUNC_INFO;
    this->setFixedSize(860, 460);
//    this->setAutoFillBackground(true);

    this->setStyleSheet("QWidget{background: #ffffff; border: none;border-bottom-right-radius:10px;border-bottom-left-radius:0px;}");
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(Qt::red));
    this->setPalette(palette);
    splitter = new QSplitter(this);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setHandleWidth(1);

    category_widget = new QListWidget(this);
    category_widget->setFixedSize(160,this->height());
    category_widget->setFocusPolicy(Qt::NoFocus);
    category_widget->setObjectName("infoList");
    category_widget->setStyleSheet("QListWidget{font-size:15px;background: rgb(237,237,237);line-height:10px;color:rgb(0,0,0,185);border-bottom-right-radius:0px;}\
                                   QListWidget::item:hover{border-radius:5px;background:rgba(61,107,229,80);color:rgb(0,0,0,185);}\
                                   QListWidget::item:selected{border-radius:5px;background:rgba(61,107,229,1);color:white;}");

    category_widget->setFlow(QListView::TopToBottom);
    //category_widget->setIconSize(QSize(16, 16));//设置QListWidget中的单元项的图片大小
    category_widget->setResizeMode(QListView::Adjust);
    category_widget->setViewMode(QListView::ListMode);   //设置QListWidget的显示模式
    category_widget->setMovement(QListView::Static);//设置QListWidget中的单元项不可被拖动
//    category_widget->setSpacing(1);//设置QListWidget中的单元项的间距

    stacked_widget = new QStackedWidget(this);//stacked_widget will delete when InfoWidget delete
//    stacked_widget->setStyleSheet("QStackedWidget{border: none;}");
    stacked_widget->setFocusPolicy(Qt::NoFocus);
    stacked_widget->setAutoFillBackground(true);


    firstLoadInputDev = true;
    firstLoadMultiMediaDev = true;
    firstLoadCommunicationDev = true;
    firstLoadDisplayDev = true;

    connect(category_widget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(changeInfoPage(QListWidgetItem*,QListWidgetItem*)));
}

InfoWidget::~InfoWidget()
{
    if (stacked_widget) {
        foreach (QObject *child, stacked_widget->children()) {
            QWidget *widget = static_cast<QWidget *>(child);
            widget->deleteLater();
        }
        delete stacked_widget;
    }
}

void InfoWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void InfoWidget::resetInfoLeftListUI(QStringList keys){
    // QList<QListWidgetItem *> items;
    // for (int i = 0; i < category_widget->count(); i++){
    //     QListWidgetItem * item = category_widget->item(i);
    //     if (keys.contains(item->statusTip())){
    //         items.append(item);
    //     }
    // }

    // /* 去掉不存在的页面 */
    // foreach (QListWidgetItem * pItem, items) {
    //     category_widget->blockSignals(true);
    //     category_widget->takeItem(category_widget->row(pItem));
    //     category_widget->blockSignals(false);
    // }

}

void InfoWidget::initInfoUI(bool has_battery, bool has_sensor)
{
    type_list.clear();
    icon_list.clear();

    type_list << tr("Computer");
    icon_list << "computer";
    InfoGui *system_widget = new InfoGui(this);//该页面永远存在，且在列表的第一个位置，为默认显示项
    system_widget->setInfoGuiName("computer");
    stacked_widget->addWidget(system_widget);
    stacked_widget->setCurrentWidget(system_widget);
    emit this->requestRefreshSystemInfo();
    emit this->requestupdateSystemRunnedTime();

//    if(info["system_message"]){
        type_list << tr("Desktop");
        icon_list << "unity";
        InfoGui *desktop_widget = new InfoGui(this);
        desktop_widget->setInfoGuiName("unity");
        stacked_widget->addWidget(desktop_widget);
//    }

//    if(info["cpu_info"]){
        type_list << tr("CPU");
        icon_list << "cpu";
        InfoGui *cpu_widget = new InfoGui(this);
        cpu_widget->setInfoGuiName("cpu");
        stacked_widget->addWidget(cpu_widget);
//    }

//    if(info["memory_info"]){
        type_list << tr("Memory");
        icon_list << "memory";
        InfoGui *memory_widget = new InfoGui(this);
        memory_widget->setInfoGuiName("memory");
        stacked_widget->addWidget(memory_widget);
//    }

//    if(info["board_info"]){
        type_list << tr("Board");
        icon_list << "board";
        InfoGui *board_widget = new InfoGui(this);
        board_widget->setInfoGuiName("board");
        stacked_widget->addWidget(board_widget);
//    }

//    if(info["harddisk_info"]){
        type_list << tr("HD");
        icon_list << "harddisk";
        InfoGui *hd_widget = new InfoGui(this);
        hd_widget->setInfoGuiName("harddisk");
        stacked_widget->addWidget(hd_widget);
//    }

//    if(info["networkcard_info"]){
        type_list << tr("NIC");
        icon_list << "network";
        InfoGui *nic_widget = new InfoGui(this);
        nic_widget->setInfoGuiName("network");
        stacked_widget->addWidget(nic_widget);
//    }

//    if(info["monitor_info"]){
        type_list << tr("Monitor");
        icon_list << "monitor";
        InfoGui *monitor_widget = new InfoGui(this);
        monitor_widget->setInfoGuiName("monitor");
        stacked_widget->addWidget(monitor_widget);
//    }

//    if(info["audiocard_info"]){
        type_list << tr("Audio");
        icon_list << "audio";
        InfoGui *audio_widget = new InfoGui(this);
        audio_widget->setInfoGuiName("audio");
        stacked_widget->addWidget(audio_widget);
//    }

//    if(info["input_info"]){
        type_list << tr("Input");
        icon_list << "input";
        InfoGui * input_widget = new InfoGui(this);
        input_widget->setInfoGuiName("input");
        stacked_widget->addWidget(input_widget);
//    }

//    if(info["communication_info"]){
        type_list << tr("Communication");
        icon_list << "communication";
        InfoGui * communication_widget = new InfoGui(this);
        communication_widget->setInfoGuiName("communication");
        stacked_widget->addWidget(communication_widget);
//    }

//    if(info["display_info"]){
        type_list << tr("Display");
        icon_list << "display";
        InfoGui * display_widget = new InfoGui(this);
        display_widget->setInfoGuiName("display");
        stacked_widget->addWidget(display_widget);
//    }

//    if(info["multimedia_info"]){
        type_list << tr("Multimedia");
        icon_list << "multimedia";
        InfoGui * multimedia_widget = new InfoGui(this);
        multimedia_widget->setInfoGuiName("multimedia");
        stacked_widget->addWidget(multimedia_widget);
//    }

    if (has_battery) {
        type_list << tr("Battery");
        icon_list << "battery";
        InfoGui *battery_widget = new InfoGui(this);
        battery_widget->setInfoGuiName("battery");
        stacked_widget->addWidget(battery_widget);
    }

    if (has_sensor) {
        type_list << tr("Sensor");
        icon_list << "sensor";
        InfoGui *sensor_widget = new InfoGui(this);
        sensor_widget->setInfoGuiName("sensor");
        stacked_widget->addWidget(sensor_widget);
    }

//    type_list << tr("Device Driver");
//    icon_list << "drive";
//    InfoGui *driver_widget = new InfoGui(this);
//    driver_widget->setInfoGuiName("drive");
//    stacked_widget->addWidget(driver_widget);

    for(int i = 0;i < type_list.length();i++) {
//        if (i == 1 && arch == "aarch64")
//        {
//            // FT arm can not access board
//        }
//        else if (i == 11 && arch == "aarch64" && serverOrDesktop.contains("server")) {
//            //arm server no sensor
//        }
//        QIcon icon;
//        icon.addFile(":/hd/res/hardware/" + icon_list.at(i), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *item = nullptr;
        item = new QListWidgetItem("          "+type_list.at(i), category_widget);

        //            item->setSizeHint(QSize(120,31)); //设置单元项的宽度和高度
        item->setSizeHint(QSize(160,30)); //设置单元项的宽度和高度
        item->setStatusTip(icon_list.at(i));
        item->setToolTip(type_list.at(i));
        item->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
//        item->setIcon(icon);

        if(i == 0)
            default_listitem = item;
    }

    category_widget->setCurrentRow(0);
    current_tip = category_widget->currentItem()->statusTip();

    QVBoxLayout *center_layout = new QVBoxLayout();
//    QVBoxLayout *name_layout = new QVBoxLayout();
//    QFrame *frame = new QFrame();
//    if(type_list.size() > 9){
//        frame->setFixedSize(this->width(),70);
//        name_layout->addWidget(category_widget);
//        name_layout->addWidget(category_widget1);
//        name_layout->setSpacing(5);
//        name_layout->setMargin(0);
//        name_layout->setContentsMargins(40, 5, 0, 0);
//    }else{
//        frame->setFixedSize(this->width(),50);
//        name_layout->addWidget(category_widget);
//        name_layout->setSpacing(0);
//        name_layout->setMargin(0);
//        name_layout->setContentsMargins(40, 0, 0, 0);
//    }
//    frame->setLayout(name_layout);
    center_layout->addWidget(stacked_widget);
    center_layout->setSpacing(0);
    center_layout->setMargin(0);
    center_layout->setContentsMargins(0, 0, 0, 0);
    splitter->addWidget(category_widget);
    splitter->addWidget(stacked_widget);
    for(int i = 0; i<splitter->count();i++) {
        QSplitterHandle *handle = splitter->handle(i);
        handle->setEnabled(false);
    }

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(splitter);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(main_layout);

//    m_testWidget->loadOnePage(0, "AAA1", QMap<QString, QVariant>());
    //    m_testWidget->loadOnePage(1, "AAA2", QMap<QString, QVariant>());

    //input info
    QDBusConnection::systemBus().connect("", \
                                         "", \
                                         "com.kylin.assistant.systemdaemon", \
                                         "inputdev_info_signal", \
                                         this, SLOT(onSendInputInfo(QDBusMessage)));

    //multimedia info
    QDBusConnection::systemBus().connect("", \
                                         "", \
                                         "com.kylin.assistant.systemdaemon", \
                                         "multimediadev_info_signal", \
                                         this, SLOT(onSendMultimediaInfo(QDBusMessage)));

    //communication info
    QDBusConnection::systemBus().connect("", \
                                         "", \
                                         "com.kylin.assistant.systemdaemon", \
                                         "communicationdev_info_signal", \
                                         this, SLOT(onSendCommunicationInfo(QDBusMessage)));

    //display info
    QDBusConnection::systemBus().connect("", \
                                         "", \
                                         "com.kylin.assistant.systemdaemon", \
                                         "displaydev_info_signal", \
                                         this, SLOT(onSendDisplayInfo(QDBusMessage)));
}

void InfoWidget::onSendSystemInfo(QMap<QString, QVariant> tmpMap)
{
//    qDebug() << "--------------------system tmpMap="<<tmpMap;
    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant> sys_info_map;
        QMap<QString,QVariant>::iterator it;
        for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
            if (it.key() != "uptime" && it.value().toString().length() > 0) {
                sys_info_map.insert(it.key(), it.value());
            }
        }
        if(sys_info_map.isEmpty() || sys_info_map.count() <= 0) {
            return;
        }
        else {
            for (int i = 0; i < stacked_widget->count(); i++) {
                if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                    if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                        continue;
                    if (page->infoGuiName() == "computer") {
                        page->clearWidget();
                        page->loadOnePage(0, tr("Computer Info"), sys_info_map);
                        break;
                    }
                }
            }
            sys_info_map.clear();
//            if (system_widget) {
//                system_widget->clearWidget();
//                system_widget->loadOnePage(0, "Computer Info", sys_info_map);
//            }
        }
    }
}

//void InfoWidget::onSendSystemRunnedTime(int time_value)
//{
//    QString result;
//    int hour_value = time_value/60;
//    int minutes_value = time_value%60;
//    if(hour_value < 1)
//    {
//        result = QString::number(minutes_value) + tr(" Minutes");//分钟
//    }
//    else
//    {
//        result = QString::number(hour_value) + tr(" Hours ") + QString::number(minutes_value) + tr(" Minutes");//小时 分钟
//    }
////    if (system_widget) {
////        system_widget->updateRunningTime(result);
////    }
//}

void InfoWidget::onSendDesktopInfo(QMap<QString, QVariant> tmpMap)
{
//    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant> desktop_info_map;
        QMap<QString,QVariant>::iterator it;
        for ( it = tmpMap.begin(); it != tmpMap.end(); ++it )
        {
            if (it.value().toString().length() > 0)
            {
                desktop_info_map.insert(it.key(), it.value());
            }
        }
//        if(desktop_info_map.isEmpty() || desktop_info_map.count() <= 0) {
//            return;
//        }
//        else {
        for (int i = 0; i < stacked_widget->count(); i++) {
            if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                    continue;
                if (page->infoGuiName() == "unity") {
                    page->clearWidget();
                    if(desktop_info_map.isEmpty() || desktop_info_map.count() <= 0){
                        page->errorPage(tr("Desktop Info"));
                    } else {
                        page->loadOnePage(0, tr("Desktop Info"), desktop_info_map);
                    }

                    break;
                }
            }
        }
        desktop_info_map.clear();
//            if (desktop_widget) {
//                desktop_widget->clearWidget();
//                desktop_widget->loadOnePage(0, "Desktop Info", desktop_info_map);
//            }
//        }
//    }
}

void InfoWidget::onSendCpuInfo(QMap<QString, QVariant> tmpMap)
{
//    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant> cpu_info_map;
        QMap<QString,QVariant>::iterator it;
        for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
            if (it.value().toString().length() > 0)
            {
                cpu_info_map.insert(it.key(), it.value());
            }
        }
//        if(cpu_info_map.isEmpty() || cpu_info_map.count() <= 0) {
//            return;
//        }
//        else {
            for (int i = 0; i < stacked_widget->count(); i++) {
                if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                    if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                        continue;
                    if (page->infoGuiName() == "cpu") {
                        page->clearWidget();
                        if(cpu_info_map.isEmpty() || cpu_info_map.count() <= 0){
                            page->errorPage(tr("CPU Info"));
                        } else {
                            page->loadOnePage(0, tr("CPU Info"), cpu_info_map);
                        }

                        break;
                    }
                }
            }
            cpu_info_map.clear();
//        }
//    }
}

void InfoWidget::onSendMemoryInfo(QMap<QString, QVariant> tmpMap)
{
//    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant>::iterator iter = tmpMap.find("Memnum");
        int memoryNum = 0;
        if (iter == tmpMap.end()) {
            memoryNum = 0;
        }
        else{
            memoryNum = iter.value().toInt();
        }

            if(memoryNum <= 1) {
                tmpMap.remove("Memnum");
                QMap<QString, QVariant> memory_info_map;
                QMap<QString,QVariant>::iterator it;
                for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
                    if (it.value().toString().length() > 0) {
                        memory_info_map.insert(it.key(), it.value());
                    }
                }
//                if (memory_info_map.isEmpty()) {
//                    return;
//                }

                for (int i = 0; i < stacked_widget->count(); i++) {
                    if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                        if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                            continue;
                        if (page->infoGuiName() == "memory") {
                            page->clearWidget();
                            if (memory_info_map.isEmpty()){
                                page->errorPage(tr("Memory Info"));
                            } else {
                                page->loadOnePage(0, tr("Memory Info"), memory_info_map);
                            }

                            break;
                        }
                    }
                }
                memory_info_map.clear();
            }
            else if(memoryNum > 1) {
                bool hadRetUI = false;
                for (int i=0;i<memoryNum;i++) {
                    //vendor:  tmp_info_map.value("MemVendor").toString().toUpper()
                    QMap<QString, QVariant> memory_info_map;
                    QMap<QString, QVariant>::iterator itbegin = tmpMap.begin();
                    QMap<QString, QVariant>::iterator itend = tmpMap.end();
                    for (;itbegin != itend; ++itbegin) {
                        if(itbegin.key() != "Memnum" && itbegin.value().toString().contains("<1_1>")) {
                            QStringList tmplist = itbegin.value().toString().split("<1_1>");
                            if (tmplist.length() >= i) {
                                QString result = tmplist.at(i);
                                if (result.length() > 0) {
                                    if ((itbegin.key() == "MemSize") && (result == "-1"))
                                        result = QObject::tr("Wrong info from firmware");
                                    memory_info_map.insert(itbegin.key(), result);
                                }
                            }
//                            QString result = itbegin.value().toString().split("<1_1>").at(i);
//                            if (result.length() > 0) {
//                                memory_info_map.insert(itbegin.key(), result);
//                            }
                        }
                    }
//                    if (memory_info_map.isEmpty())
//                        return;
                    for (int j = 0; j < stacked_widget->count(); j++) {
                        if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(j))) {
                            if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                                continue;
                            if (page->infoGuiName() == "memory") {
                                if (!hadRetUI) {//只加载第一个内存时清空原来的界面
                                    page->clearWidget();
                                    hadRetUI = true;
                                }
                                if (memory_info_map.isEmpty()){
                                    page->errorPage(tr("Memory Info %1").arg(i+1));
                                } else {
                                    page->loadOnePage(0, tr("Memory Info %1").arg(i+1), memory_info_map);
                                }

                                break;
                            }
                        }
                    }
                    memory_info_map.clear();
                }
            }
//    }
}

void InfoWidget::onSendBoardInfo(QMap<QString, QVariant> tmpMap)
{
    //board_info_map.value("BoaVendor").toString().toUpper()
//    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant> board_info_map;
        QMap<QString,QVariant>::iterator it;
        for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
            if (it.value().toString().length() > 0) {
                board_info_map.insert(it.key(), it.value());
            }
        }
//        if(board_info_map.isEmpty() || board_info_map.count() <= 0) {
//            return;
//        }
//        else {
            for (int i = 0; i < stacked_widget->count(); i++) {
                if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                    if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                        continue;
                    if (page->infoGuiName() == "board") {
                        page->clearWidget();
                        if(board_info_map.isEmpty() || board_info_map.count() <= 0){
                            page->errorPage(tr("Board Info"));
                        } else {
                            page->loadOnePage(0, tr("Board Info"), board_info_map);
                        }

                        break;
                    }
                }
            }
            board_info_map.clear();
//        }
//    }
}

void InfoWidget::onSendHDInfo(QMap<QString, QVariant> tmpMap)
{
    //hd_info_map.value("DiskVendor").toString().toUpper()
//    qDebug() << "onSendHDInfo===="<<tmpMap;
//    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant>::iterator iter = tmpMap.find("DiskNum");
        int diskNum = 0;
        if (iter == tmpMap.end()) {
            diskNum = 0;
        }
        else{
            diskNum = iter.value().toInt();
        }
//        if(diskNum > 0) {
            if(diskNum <= 1) {
                tmpMap.remove("DiskNum");
                QMap<QString, QVariant> hd_info_map;
                QMap<QString,QVariant>::iterator it;
                for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
                    if (it.value().toString().length() > 0) {
                        if (QString::compare(it.value().toString(), "$", Qt::CaseInsensitive) != 0)
                            hd_info_map.insert(it.key(), it.value());
                    }
                }

//                if (hd_info_map.isEmpty()) {
//                    return;
//                }

                for (int i = 0; i < stacked_widget->count(); i++) {
                    if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                        if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                            continue;
                        if (page->infoGuiName() == "harddisk") {
                            page->clearWidget();
                            if (hd_info_map.isEmpty()) {
                                page->errorPage(tr("HardWare Info"));
                            } else {
                                page->loadOnePage(0, tr("HardWare Info"), hd_info_map);
                            }

                            break;
                        }
                    }
                }
                hd_info_map.clear();
            }
            else if(diskNum > 1) {
                bool hadRetUI = false;
                for (int i=0;i<diskNum;i++) {
                    //vendor:  tmp_info_map.value("DiskVendor").toString().toUpper()
                    QMap<QString, QVariant> hd_info_map;
                    QMap<QString, QVariant>::iterator itbegin = tmpMap.begin();
                    QMap<QString, QVariant>::iterator itend = tmpMap.end();
                    for (;itbegin != itend; ++itbegin) {
                        if(itbegin.key() != "DiskNum" && itbegin.value().toString().contains("<1_1>")) {
                            QStringList tmplist = itbegin.value().toString().split("<1_1>");
                            if (tmplist.length() >= i) {
                                QString result = tmplist.at(i);
                                if (result.length() > 0) {
                                    if (QString::compare(result, "$", Qt::CaseInsensitive) != 0)
                                        hd_info_map.insert(itbegin.key(), result);
                                }
                            }
//                            QString result = itbegin.value().toString().split("<1_1>").at(i);
//                            if (result.length() > 0) {
//                                if (QString::compare(result, "$", Qt::CaseInsensitive) != 0)
//                                    hd_info_map.insert(itbegin.key(), result);
//                            }
                        }
                    }
//                    if (hd_info_map.isEmpty())
//                        return;
                    for (int j = 0; j < stacked_widget->count(); j++) {
                        if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(j))) {
                            if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                                continue;
                            if (page->infoGuiName() == "harddisk") {
                                if (!hadRetUI) {//只加载第一个硬盘时清空原来的界面
                                    page->clearWidget();
                                    hadRetUI = true;
                                }
                                if (hd_info_map.isEmpty()){
                                    page->errorPage(tr("HardWare Info %1").arg(i+1));
                                } else {
                                    page->loadOnePage(0, tr("HardWare Info %1").arg(i+1), hd_info_map);
                                }

                                break;
                            }
                        }
                    }
                    hd_info_map.clear();
                }
            }
//        }
//    }
}

void InfoWidget::onSendNicInfo(QMap<QString, QVariant> tmpMap)
{
//    qDebug() << "onSendNicInfo="<<tmpMap;
//    if (!tmpMap.isEmpty() && tmpMap.count() > 1) {//may be wire_info_map only contains NetNum
        QMap<QString, QVariant>::iterator iter = tmpMap.find("NetNum");
        int netNum = 0;
        if (iter == tmpMap.end()) {
            netNum = 0;
        }
        else{
            netNum = iter.value().toInt();
        }
//        if(netNum < 0) {
            if(netNum <= 1) {
                //vendor:wire_info_map.value("NetVendor").toString().toUpper().contains("INTEL") :"INTEL"
                //       wire_info_map.value("NetVendor").toString().toUpper().contains("REALTEK") : "REALTEK")
                tmpMap.remove("NetNum");
                if (tmpMap.contains("NetLogicalname")) {
                    QMap<QString,QVariant>::iterator iter = tmpMap.find("NetLogicalname");
                    QString netcard = iter.value().toString();
                    if (netcard.startsWith("veth") || netcard.startsWith("virbr")) {
                        tmpMap["NetType"] = "VNIC";
                    }
                }
                QMap<QString, QVariant> wire_info_map;
                QMap<QString,QVariant>::iterator it;
                for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
                    if (it.value().toString().length() > 0) {
                        wire_info_map.insert(it.key(), it.value());
                    }
                }
//                if (wire_info_map.isEmpty()) {
//                    return;
//                }

                for (int i = 0; i < stacked_widget->count(); i++) {
                    if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                        if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                            continue;
                        if (page->infoGuiName() == "network") {
                            page->clearWidget();
                            if (wire_info_map.isEmpty()) {
                                page->errorPage(tr("NIC Info"));
                            } else {
                                page->loadOnePage(0, tr("NIC Info"), wire_info_map);
                            }

                            break;
                        }
                    }
                }
                wire_info_map.clear();
            }
            else if(netNum > 1) {
                bool hadRetUI = false;
                for (int i=0;i<netNum;i++) {
                    //vendor:  tmp_info_map.value("DiskVendor").toString().toUpper()
                    QMap<QString, QVariant> wire_info_map;
                    QMap<QString, QVariant>::iterator itbegin = tmpMap.begin();
                    QMap<QString, QVariant>::iterator itend = tmpMap.end();
                    for (;itbegin != itend; ++itbegin) {
                        if(itbegin.key() != "NetNum" && itbegin.value().toString().contains("<1_1>")) {
                            QStringList tmplist = itbegin.value().toString().split("<1_1>");
                            if (tmplist.length() >= i) {
                                QString result = tmplist.at(i);
                                if (result.length() > 0) {
                                    wire_info_map.insert(itbegin.key(), result);
                                }
                            }
//                            QString result = itbegin.value().toString().split("<1_1>").at(i);
//                            if (result.length() > 0) {
//                                  wire_info_map.insert(itbegin.key(), result);
//                            }
                        }
                    }
//                    if (wire_info_map.isEmpty())
//                        return;

                    if (wire_info_map.contains("NetLogicalname")) {
                        if (wire_info_map.value("NetLogicalname").toString().startsWith("veth") || wire_info_map.value("NetLogicalname").toString().startsWith("virbr")) {
                            wire_info_map["NetType"] = QVariant("VNIC");
                        }
                    }
                    for (int j = 0; j < stacked_widget->count(); j++) {
                        if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(j))) {
                            if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                                continue;
                            if (page->infoGuiName() == "network") {
                                if (!hadRetUI) {//只加载第一个网卡时清空原来的界面
                                    page->clearWidget();
                                    hadRetUI = true;
                                }
                                if (wire_info_map.isEmpty()){
                                    page->errorPage(tr("NIC Info %1").arg(i+1));
                                } else {
                                    page->loadOnePage(0, tr("NIC Info %1").arg(i+1), wire_info_map);
                                }

                                break;
                            }
                        }
                    }
                    wire_info_map.clear();
                }
            }
//        }
//    }
}

void InfoWidget::onSendMonitorInfo(QMap<QString, QVariant> tmpMap)
{
//    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant>::iterator iter = tmpMap.find("Vga_num");
        int vgaNum = 0;
        if (iter == tmpMap.end()) {
            vgaNum = 0;
        }
        else{
            vgaNum = iter.value().toInt();
        }
//        if(vgaNum > 0) {
            if(vgaNum <= 1) {
                //vendor:monitor_info_map.value("Vga_vendor").toString().toUpper()
                tmpMap.remove("Vga_num");
                QMap<QString, QVariant> monitor_info_map;
                QMap<QString,QVariant>::iterator it;
                for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
                    if (it.value().toString().length() > 0) {
                        monitor_info_map.insert(it.key(), it.value());
                    }
                }
//                if (monitor_info_map.isEmpty()) {
//                    return;
//                }

                for (int i = 0; i < stacked_widget->count(); i++) {
                    if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                        if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                            continue;
                        if (page->infoGuiName() == "monitor") {
                            page->clearWidget();
                            if (monitor_info_map.isEmpty()) {
                                page->errorPage(tr("Monitor Info"));
                            } else {
                                page->loadOnePage(0, tr("Monitor Info"), monitor_info_map);
                            }

                            break;
                        }
                    }
                }
                monitor_info_map.clear();
            }
            else if(vgaNum > 1) {
                bool hadRetUI = false;
                for (int i=0;i<vgaNum;i++) {
                    //vendor:  tmp_info_map.value("Vga_vendor").toString().toUpper()
                    QMap<QString, QVariant> monitor_info_map;
                    QMap<QString, QVariant>::iterator itbegin = tmpMap.begin();
                    QMap<QString, QVariant>::iterator itend = tmpMap.end();
                    for (;itbegin != itend; ++itbegin) {
                        if(itbegin.key() != "Vga_num" && itbegin.value().toString().contains("<1_1>")) {
                            QStringList tmplist = itbegin.value().toString().split("<1_1>");
                            if (tmplist.length() >= i) {
                                QString result = tmplist.at(i);
                                if (result.length() > 0) {
                                    monitor_info_map.insert(itbegin.key(), result);
                                }
                            }
//                            QString result = itbegin.value().toString().split("<1_1>").at(i);
//                            if (result.length() > 0) {
//                                monitor_info_map.insert(itbegin.key(), result);
//                            }
                        }
                    }
//                    if (monitor_info_map.isEmpty())
//                        return;
                    for (int j = 0; j < stacked_widget->count(); j++) {
                        if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(j))) {
                            if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                                continue;
                            if (page->infoGuiName() == "monitor") {
                                if (!hadRetUI) {//只加载第一个显卡时清空原来的界面
                                    page->clearWidget();
                                    hadRetUI = true;
                                }
                                if (monitor_info_map.isEmpty()){
                                    page->errorPage(tr("Monitor Info %1").arg(i+1));
                                } else {
                                    page->loadOnePage(0, tr("Monitor Info %1").arg(i+1), monitor_info_map);
                                }

                                break;
                            }
                        }
                    }
                    monitor_info_map.clear();
                }
            }
//        }
//    }
}

void InfoWidget::onSendAudioInfo(QMap<QString, QVariant> tmpMap)
{
//    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant>::iterator iter = tmpMap.find("MulNum");
        int mulNum = 0;
        if (iter == tmpMap.end()) {
            mulNum = 0;
        }
        else{
            mulNum = iter.value().toInt();
        }
//        if(mulNum > 0) {
            if(mulNum <= 1) {
                //vendor: audio_info_map.value("MulVendor").toString().toUpper()
                tmpMap.remove("MulNum");
                QMap<QString, QVariant> audio_info_map;
                QMap<QString,QVariant>::iterator it;
                for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
                    if (it.value().toString().length() > 0) {
                        audio_info_map.insert(it.key(), it.value());
                    }
                }
//                if (audio_info_map.isEmpty()) {
//                    return;
//                }

                for (int i = 0; i < stacked_widget->count(); i++) {
                    if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                        if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                            continue;
                        if (page->infoGuiName() == "audio") {
                            page->clearWidget();
                            if (audio_info_map.isEmpty()) {
                                page->errorPage(tr("Audio Info"));
                            } else {
                                page->loadOnePage(0, tr("Audio Info"), audio_info_map);
                            }

                            break;
                        }
                    }
                }
                audio_info_map.clear();
            }
            else if(mulNum > 1) {
                bool hadRetUI = false;
                for (int i=0;i<mulNum;i++) {
                    //vendor:  audio_info_map.value("MulVendor").toString().toUpper()
                    QMap<QString, QVariant> audio_info_map;
                    QMap<QString, QVariant>::iterator itbegin = tmpMap.begin();
                    QMap<QString, QVariant>::iterator itend = tmpMap.end();
                    for (;itbegin != itend; ++itbegin) {
                        if(itbegin.key() != "MulNum" && itbegin.value().toString().contains("<1_1>")) {
                            QStringList tmplist = itbegin.value().toString().split("<1_1>");
                            if (tmplist.length() >= i) {
                                QString result = tmplist.at(i);
                                if (result.length() > 0) {
                                    audio_info_map.insert(itbegin.key(), result);
                                }
                            }
//                            QString result = itbegin.value().toString().split("<1_1>").at(i);
//                            if (result.length() > 0) {
//                                audio_info_map.insert(itbegin.key(), result);
//                            }
                        }
                    }
//                    if (audio_info_map.isEmpty())
//                        return;
                    for (int j = 0; j < stacked_widget->count(); j++) {
                        if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(j))) {
                            if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                                continue;
                            if (page->infoGuiName() == "audio") {
                                if (!hadRetUI) {//只加载第一个声卡时清空原来的界面
                                    page->clearWidget();
                                    hadRetUI = true;
                                }
                                if (audio_info_map.isEmpty()){
                                    page->errorPage(tr("Audio Info %1").arg(i+1));
                                } else {
                                    page->loadOnePage(0, tr("Audio Info %1").arg(i+1), audio_info_map);
                                }
                                break;
                            }
                        }
                    }
                    audio_info_map.clear();
                }
            }
//        }
//    }
}

void InfoWidget::onSendInputInfo(QDBusMessage msg){
    // qDebug() << msg;
    const QDBusArgument &dbusArg = msg.arguments().at(0).value<QDBusArgument>();
    QList<QStringList> inputInfos;
    dbusArg >> inputInfos;
    // qDebug() << inputInfos;
//    if (inputInfo.isEmpty())
//        return;

//    QMap<QString, QVariant> m1;
//    for (QStringList::iterator it = inputInfo.begin(); it != inputInfo.end(); it++){
//        QString s1 = *it;
//        QStringList st1 = s1.split(":");
//        m1.insert(st1.at(0), st1.at(1));
//    }

    for (int i = 0; i < stacked_widget->count(); i++) {
        if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
            if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                continue;

            if (page->infoGuiName() == "input") {
                if (firstLoadInputDev){
                    page->clearWidget();
                    firstLoadInputDev = false;
                }
                if (inputInfos.isEmpty()){
                    page->errorPage(tr("Input Info"));
                } else {
                    for (QList<QStringList>::iterator it1 = inputInfos.begin(); it1 != inputInfos.end(); it1++){
                        QMap<QString, QVariant> m1;
                        QStringList inputInfo = *it1;
                        for (QStringList::iterator it2 = inputInfo.begin(); it2 != inputInfo.end(); it2++){
                            QString s1 = *it2;
                            m1.insert(s1.section(':', 0, 0), s1.section(':', 1));
                        }
                        page->loadOnePage(0, tr("Input Info"), m1);
                    }
                }
                break;
            }
        }
    }
}

void InfoWidget::onSendCommunicationInfo(QDBusMessage msg){
    const QDBusArgument &dbusArg = msg.arguments().at(0).value<QDBusArgument>();
    QList<QStringList> communicationInfos;
    dbusArg >> communicationInfos;
//    if (communicationInfo.isEmpty())
//        return;

//    QMap<QString, QVariant> m1;
//    for (QStringList::iterator it = communicationInfo.begin(); it != communicationInfo.end(); it++){
//        QString s1 = *it;
//        QStringList st1 = s1.split(":");
//        m1.insert(st1.at(0), st1.at(1));
//    }

    for (int i = 0; i < stacked_widget->count(); i++) {
        if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
            if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                continue;

            if (page->infoGuiName() == "communication") {
                if (firstLoadCommunicationDev){
                    page->clearWidget();
                    firstLoadCommunicationDev = false;
                }
                if (communicationInfos.isEmpty()){
                    page->errorPage(tr("Communication Info"));
                } else {
                    for (QList<QStringList>::iterator it1 = communicationInfos.begin(); it1 != communicationInfos.end(); it1++){
                        QMap<QString, QVariant> m1;
                        QStringList communicationInfo = *it1;
                        for (QStringList::iterator it2 = communicationInfo.begin(); it2 != communicationInfo.end(); it2++){
                            QString s1 = *it2;
                            m1.insert(s1.section(':', 0, 0), s1.section(':', 1));
                        }
                        if(m1["capabilities"].toString().indexOf("bluetooth",Qt::CaseInsensitive) != -1 || m1.contains("bluetooth version"))
                            page->loadOnePage(0, tr("Bluetooth Info"), m1);
                        else
                            page->loadOnePage(0, tr("Communication Info"), m1);
                    }
                }
                break;
            }
        }
    }
}

void InfoWidget::onSendDisplayInfo(QDBusMessage msg){
    const QDBusArgument &dbusArg = msg.arguments().at(0).value<QDBusArgument>();
    QList<QStringList> displayInfos;
    dbusArg >> displayInfos;
//    if (displayInfo.isEmpty())
//        return;

//    QMap<QString, QVariant> m1;
//    for (QStringList::iterator it = displayInfo.begin(); it != displayInfo.end(); it++){
//        QString s1 = *it;
//        QStringList st1 = s1.split(":");
//        m1.insert(st1.at(0), st1.at(1));
//    }

    for (int i = 0; i < stacked_widget->count(); i++) {
        if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
            if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                continue;

            if (page->infoGuiName() == "display") {
                if (firstLoadDisplayDev){
                    page->clearWidget();
                    firstLoadDisplayDev = false;
                }
                if (displayInfos.isEmpty()){
                    page->errorPage(tr("Display Info"));
                } else {
                    for (QList<QStringList>::iterator it1 = displayInfos.begin(); it1 != displayInfos.end(); it1++){
                        QMap<QString, QVariant> m1;
                        QStringList displayInfo = *it1;
                        for (QStringList::iterator it2 = displayInfo.begin(); it2 != displayInfo.end(); it2++){
                            QString s1 = *it2;
                            m1.insert(s1.section(':', 0, 0), s1.section(':', 1));
                        }
                        page->loadOnePage(0, tr("Display Info"), m1);
                    }
                }
                break;
            }
        }
    }
}

void InfoWidget::onSendMultimediaInfo(QDBusMessage msg){
    const QDBusArgument &dbusArg = msg.arguments().at(0).value<QDBusArgument>();
    QList<QStringList> multimediaInfos;
    dbusArg >> multimediaInfos;
//    if (multimediaInfo.isEmpty())
//        return;

//    QMap<QString, QVariant> m1;
//    for (QStringList::iterator it = multimediaInfo.begin(); it != multimediaInfo.end(); it++){
//        QString s1 = *it;
//        QStringList st1 = s1.split(":");
//        m1.insert(st1.at(0), st1.at(1));
//    }

    for (int i = 0; i < stacked_widget->count(); i++) {
        if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
            if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                continue;

            if (page->infoGuiName() == "multimedia") {
                if (firstLoadMultiMediaDev){
                    page->clearWidget();
                    firstLoadMultiMediaDev = false;
                }
                if (multimediaInfos.isEmpty()){
                    page->errorPage(tr("Multimedia Info"));
                } else {
                    for (QList<QStringList>::iterator it1 = multimediaInfos.begin(); it1 != multimediaInfos.end(); it1++){
                        QMap<QString, QVariant> m1;
                        QStringList multimediaInfo = *it1;
                        for (QStringList::iterator it2 = multimediaInfo.begin(); it2 != multimediaInfo.end(); it2++){
                            QString s1 = *it2;
                            m1.insert(s1.section(':', 0, 0), s1.section(':', 1));
                        }
                        page->loadOnePage(0, tr("Multimedia Info"), m1);
                    }
                }
                break;
            }
        }
    }
}

void InfoWidget::onSendBatteryInfo(QMap<QString, QVariant> tmpMap)
{
    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant> battery_info_map;
        QMap<QString,QVariant>::iterator it; //遍历map
        QStringList powerlist;
        powerlist << "POWER_SUPPLY_NAME" << "POWER_SUPPLY_MANUFACTURER" << "POWER_SUPPLY_MODEL_NAME" << "POWER_SUPPLY_TECHNOLOGY" << "POWER_SUPPLY_VOLTAGE_NOW" << "POWER_SUPPLY_ENERGY_FULL_DESIGN" << "POWER_SUPPLY_ENERGY_FULL" << "POWER_SUPPLY_ENERGY_NOW" << "POWER_SUPPLY_SERIAL_NUMBER";
        for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
            QList<QString>::Iterator itstart = powerlist.begin(), itend = powerlist.end();
            for(;itstart !=itend;itstart++)
            {
                if(*itstart == it.key())
                {
                    if (it.key() == "POWER_SUPPLY_SERIAL_NUMBER")
                    {
                        if (it.value().toString().replace(" " ,"").length() > 0)
                            battery_info_map.insert(it.key(), it.value());
                    }
                    else {
                        if (it.value().toString().length() > 0)
                            battery_info_map.insert(it.key(), it.value());
                    }
                    break;
                }
            }
        }
        if(battery_info_map.isEmpty() || battery_info_map.count() <= 0) {
            return;
        }

        //vendor:battery_info_map.value("POWER_SUPPLY_MANUFACTURER").toString().toUpper()
        for (int i = 0; i < stacked_widget->count(); i++) {
            if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                    continue;
                if (page->infoGuiName() == "battery") {
                    page->clearWidget();
                    page->loadOnePage(0, tr("Battery Info"), battery_info_map);
                    break;
                }
            }
        }
        battery_info_map.clear();
    }
}

void InfoWidget::onSendSensorInfo(QMap<QString, QVariant> tmpMap)
{
    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant> sensor_info_map;
        QMap<QString,QVariant>::iterator it;
        for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
            if (it.value().toString().length() > 0) {
                sensor_info_map.insert(it.key(), it.value());
            }
        }
        if (sensor_info_map.isEmpty() || sensor_info_map.count() <= 0) {
            return;
        }
        for (int i = 0; i < stacked_widget->count(); i++) {
            if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                    continue;
                if (page->infoGuiName() == "sensor") {
                    page->updatePageData("Hardware sensor information", sensor_info_map);//该页面数据需要动态刷新，所以不销毁页面
                    break;
                }
            }
        }
        sensor_info_map.clear();
    }
}

void InfoWidget::onUDevHotPluginAdd(QString strUdevSubName, QString strUdevType)
{
    //qDebug()<<"UDev Added:"<<strUdevSubName<<"|"<<strUdevType;
    if (strUdevSubName == "usb" && strUdevType == "usb_device") {
        // update input info
        firstLoadInputDev = true;
        emit this->requestInputInfo();
        // update communication info
        firstLoadCommunicationDev = true;
        emit this->requestCommunicationInfo();
        // update HD info(invalid)
        emit this->requestHDInfo();
        // update NIC info
        emit this->requestNicInfo();
    }
    else if (strUdevSubName != "usb") {
    }
}

void InfoWidget::onUDevHotPluginRemove(QString strUdevSubName, QString strUdevType)
{
    //qDebug()<<"UDev Removed:"<<strUdevSubName<<"|"<<strUdevType;
    if (strUdevSubName == "usb" && strUdevType == "usb_device") {
        // update input info
        firstLoadInputDev = true;
        emit this->requestInputInfo();
        // update communication info
        firstLoadCommunicationDev = true;
        emit this->requestCommunicationInfo();
        // update HD info
        emit this->requestHDInfo();
        // update NIC info
        emit this->requestNicInfo();
    }
    else if (strUdevSubName != "usb") {
    }
}

//void InfoWidget::updateTimeValue()
//{

//}

void InfoWidget::changeInfoPage(QListWidgetItem *item, QListWidgetItem *item1) {
    //20180101
    if (!item)
        return;
    QString m_currentGuiName = item->statusTip();
    if (m_currentGuiName.isEmpty() || m_currentGuiName.isNull())
        return;
//    qDebug() << "InfoWidget changeInfoPage" << m_currentGuiName;

    for (int i = 0; i < stacked_widget->count(); i++) {
        if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
            if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                continue;
            if (page->infoGuiName() == m_currentGuiName) {
                QPointer<InfoGui> panel(page);
                if (panel.isNull()) {
                    continue;
                }
                stacked_widget->setCurrentWidget(page);
                if (m_currentGuiName == "computer") {//system
                    emit this->requestRefreshSystemInfo();
        //            emit this->requestupdateSystemRunnedTime();
                }
                else if (m_currentGuiName == "unity") {//desktop
                    emit this->requestDesktopInfo();
                }
                else if (m_currentGuiName == "cpu") {
                    emit this->requestCpuInfo();
                }
                else if (m_currentGuiName == "memory") {
                    emit this->requestMemoryInfo();
                }
                else if (m_currentGuiName == "board") {
                    emit this->requestBoardInfo();
                }
                else if (m_currentGuiName == "harddisk") {
                    emit this->requestHDInfo();
                }
                else if (m_currentGuiName == "network") {
                    emit this->requestNicInfo();
                }
                else if (m_currentGuiName == "monitor") {
                    emit this->requestMonitorInfo();
                }
                else if (m_currentGuiName == "audio") {
                    emit this->requestAudioInfo();
                }
                else if (m_currentGuiName == "battery") {
                    emit this->requestBatteryInfo();
                }
                else if (m_currentGuiName == "sensor") {
                    emit this->requestSensorInfo();
                }
                else if (m_currentGuiName == "input"){
//                    firstLoadInputDev = true;
//                    emit this->requestInputInfo();
                }
                else if (m_currentGuiName == "communication"){
//                    firstLoadCommunicationDev = true;
//                    emit this->requestCommunicationInfo();
                }
                else if (m_currentGuiName == "drive") {
                    QMap<QString, QVariant> driver_info_map;
                    DeviceManager manager;
                    QStringList list = manager.getDeviceMsg();
//                    qDebug() << list;
                    for (int i=0 ; i < list.length() ; i++) {
                        QStringList splitlist = list.at(i).split(";");
                        if(splitlist.length() == 1) {
                            QStringList name = splitlist.at(0).split(":");
                            driver_info_map.insert(name.at(0).trimmed(), name.at(1));
                        }
                        else if(splitlist.length() == 2) {
                            QStringList name1 = splitlist.at(0).split(":");
                            QStringList name2 = splitlist.at(1).split(":");
                            driver_info_map.insert(name1.at(0).trimmed(), name1.at(1));
                            driver_info_map.insert(name2.at(0).trimmed(), name2.at(1));
                        }
                        else if(splitlist.length() == 3) {
                            QStringList name3 = splitlist[0].split(":");
                            QStringList name4 = splitlist[1].split(":");
                            QStringList name5 = splitlist[2].split(":");
                            driver_info_map.insert(name3.at(0).trimmed(), name3.at(1));
                            driver_info_map.insert(name4.at(0).trimmed(), name4.at(1));
                            driver_info_map.insert(name5.at(0).trimmed(), name5.at(1));
                        }
                    }
                    if (!driver_info_map.isEmpty()) {
                        for (int i = 0; i < stacked_widget->count(); i++) {
                            if (InfoGui *page = static_cast<InfoGui *>(stacked_widget->widget(i))) {
                                if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                                    continue;
                                if (page->infoGuiName() == "drive") {
                                    page->clearWidget();
                                    page->loadOnePage(0, tr("Driver Info"), driver_info_map);
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            }
        }
    }
}
