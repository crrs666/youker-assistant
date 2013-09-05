/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
#include "sudodispatcher.h"
#include <QDebug>
#include <QProcessEnvironment>
#include <QtDBus>
#include "authdialog.h"
//extern QString passwd;

SudoDispatcher::SudoDispatcher(QObject *parent) :
    QObject(parent)
{
    sudoiface = new QDBusInterface("com.ubuntukylin.Ihu",
                               "/",
                               "com.ubuntukylin.Ihu",
                               QDBusConnection::systemBus());
    QObject::connect(sudoiface,SIGNAL(clean_complete(QString)),this,SLOT(handler_clear_rubbish(QString)));
    QObject::connect(sudoiface,SIGNAL(clean_error(QString)),this,SLOT(handler_clear_rubbish_error(QString)));

}

void SudoDispatcher::exit_qt()
{
    sudoiface->call("exit");
}

QString SudoDispatcher::get_sudo_daemon_qt() {
    QDBusReply<QString> reply = sudoiface->call("get_sudo_daemon");
    return reply.value();
}

void SudoDispatcher::handler_clear_rubbish(QString msg)
{
     emit finishCleanWork(msg);
}

void SudoDispatcher::handler_clear_rubbish_error(QString msg)
{
     emit finishCleanWorkError(msg);
}
//bool SudoDispatcher::trans_password(QString flagstr, QString pwd) {
//    QString cmd1 = "echo " + pwd + " | sudo -S touch /usr/bin/youker.txt";
//    QByteArray ba1 = cmd1.toLatin1();
//    const char *transpd = ba1.data();
//    int bb = system(transpd);
//    qDebug() << bb;
//    if (bb == 0) {
//        qDebug() << "yes";
//        QString cmd2 = "echo " + pwd + " | sudo -S rm /usr/bin/youker.txt";
//        QByteArray ba2 = cmd2.toLatin1();
//        const char *transpd2 = ba2.data();
//        int bb1 = system(transpd2);
//        qDebug() << bb1;
//        QProcess *process = new QProcess;
//        process->start("/usr/bin/" + flagstr + " " + pwd);
//        return true;
//    }
//    else {
//        qDebug() << "no";
//    }
//    return false;
//}

bool SudoDispatcher::show_passwd_dialog() {
    AuthDialog *dialog = new AuthDialog("提示：请输入当前用户登录密码，保证优客助手的正常使用。");
    dialog->exec();
//    bool value = trans_password("youkersudo", passwd);
//    return value;
}

void SudoDispatcher::clean_package_cruft_qt(QStringList strlist) {
    sudoiface->call("clean_package_cruft", strlist);
}
