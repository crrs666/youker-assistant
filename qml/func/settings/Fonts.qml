/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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

import QtQuick 1.1
//import RegisterMyType 0.1
import SessionType 0.1
//import SystemType 0.1
import QtDesktop 0.1
import "../common" as Common

Rectangle {
    id: fontspage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"

//    property int cursor_size: 24
    property SessionDispatcher dis: sessiondispatcher

    Common.Border {
        id: leftborder
    }
    Common.Border {
        id: roightborder
        anchors.right: parent.right
    }

    Component.onCompleted: {
//        var mylist = ["lili", "xiang", "peng", "shuang"];
//        console.log("-----------------------------");
//        console.log(mylist.length);
//        themepage.cursor_size = themespinbox.value;
//        var syslist = sessiondispatcher.get_themes_qt();
//        choices1.clear();
//        for(var i=0; i < syslist.length; i++) {
//            choices1.append({"text": syslist[i]});
//        }
//        var iconlist = sessiondispatcher.get_icon_themes_qt();
//        choices2.clear();
//        for(var j=0; j < iconlist.length; j++) {
//            choices2.append({"text": iconlist[j]});
//        }
//        var cursorlist = sessiondispatcher.get_cursor_themes_qt();
//        choices3.clear();
//        for(var k=0; k < cursorlist.length; k++) {
//            choices3.append({"text": cursorlist[k]});
//        }
    }

    Connections {
        target: toolBar
        //按下确定按钮
        onButton2Clicked: {
            if (settigsDetails.setTitle == "fonts") {
//                console.log(fontslabel.text);

//                sessiondispatcher.set_theme_qt(syscombo.selectedText);
//                sessiondispatcher.set_icon_theme_qt(iconcombo.selectedText);
//                sessiondispatcher.set_cursor_theme_qt(cursorcombo.selectedText);
//                if (themepage.cursor_size != themespinbox.value) {
//                    themepage.cursor_size = themespinbox.value;
//                    sessiondispatcher.set_cursor_size_qt(themespinbox.value);
//                }
            }
        }
    }

    ListModel {
        id: choices1
        ListElement { text: "kobe999" }
    }
    ListModel {
        id: choices2
        ListElement { text: "kobe888" }
    }
    ListModel {
        id: choices
        ListElement { text: "kobe777" }
    }

    Label {
        id: fonts
        text: qsTr("字体设置>")
        height: 30
        font.bold: true
        font.family: "Ubuntu"
        elide: Text.ElideRight
        font.pointSize: 20
        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 15
        }
    }

    Column {
        spacing: 20
        anchors {
//            top: parent.top
//            topMargin: 20
            top: fonts.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

//        anchors.horizontalCenter: parent.horizontalCenter

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            Label {
                id: fontslabel
                width: 110
                text: qsTr("字体设置:")
                font {
                    family: fontspage.fontName
                    pointSize: fontspage.fontSize
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            ComboBox {
                id: fontscombo
                model: choices
                width: fontslabel.width
                onSelectedTextChanged: console.log(selectedText)
            }
//            Label {
//                id: current_theme
//                text: sessiondispatcher.get_theme_qt()
//                width: fontslabel.width
//                anchors.verticalCenter: parent.verticalCenter
//            }
        }

        Row {
            Label {
                id: desktopfontlabel
                width: 110
                text: qsTr("桌面字体:")
                font {
                    family: fontspage.fontName
                    pointSize: fontspage.fontSize
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            ComboBox {
                id: desktopfontcombo
                model: choices
                width: desktopfontlabel.width
//                onSelectedTextChanged: console.log(selectedText)
            }
//            Label {
//                id: fonts_set
//                text: sessiondispatcher.get_theme_qt()
//                width: fontslabel.width
//                anchors.verticalCenter: parent.verticalCenter
//            }
        }

        Row {
            Label {
                id: documentfontlabel
                width: 110
                text: qsTr("文档字体:")
                font {
                    family: fontspage.fontName
                    pointSize: fontspage.fontSize
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            ComboBox {
                id: documentfontcombo
                model: choices
                width: documentfontlabel.width
//                onSelectedTextChanged: console.log(selectedText)
            }
        }

        Row {
            Label {
                id: monospacefontlabel
                width: 110
                text: qsTr("monospace字体:")
                font {
                    family: fontspage.fontName
                    pointSize: fontspage.fontSize
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            ComboBox {
                id: monospacefontcombo
                model: choices
                width: monospacefontlabel.width
//                onSelectedTextChanged: console.log(selectedText)
            }
        }

        Row {
            Label {
                id: windowtitlefontlabel
                width: 110
                text: qsTr("标题栏字体:")
                font {
                    family: fontspage.fontName
                    pointSize: fontspage.fontSize
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            ComboBox {
                id: windowtitlefontcombo
                model: choices
                width: windowtitlefontlabel.width;
//                onSelectedTextChanged: console.log(selectedText)
            }
        }

        Row {
            Label {
                id: fontzoomlabel
                width: 110
                text: qsTr("字体大小:")
                font {
                    family: fontspage.fontName
                    pointSize: fontspage.fontSize
                }
                anchors.verticalCenter: parent.verticalCenter
            }
            SpinBox {
                id: fontzoomspinbox
                width: 97
                minimumValue: 32
                maximumValue: 64
                value: 48
            }
        }

    }//Column

}



//import QtQuick 1.1
////import RegisterMyType 0.1
//import SessionType 0.1
//import SystemType 0.1
//import QtDesktop 0.1
//import "../common" as Common
//Rectangle {
//    id: lancherpage
//    property bool on: true
//    width: parent.width
//    height: 460
////    property Dispatcher dis: mydispather

//    Common.Border {
//        id: leftborder
//    }
//    Common.Border {
//        id: roightborder
//        anchors.right: parent.right
//    }

//    Component.onCompleted: {
////        choices.clear();
////        choices.append({"text": mydispather.get_themes()[0]});
////        choices.append({"text": mydispather.get_themes()[1]});
////        choices.append({"text": mydispather.get_themes()[2]});
////        choices.append({"text": mydispather.get_themes()[3]});

////        streamModel.sync();
//    }

//    ListModel {
//        id: choices
//        ListElement { text: "fonts" }
//        ListElement { text: "lixiang" }
//        ListElement { text: "ps" }
//        ListElement { text: "baby" }
//    }

//    Connections {
//        target: toolBar
//        //按下确定按钮
//        onButton2Clicked: {
////            console.log("111111111111");
////            console.log(settigsDetails.setTitle);
//            if (settigsDetails.setTitle == "fonts")
//                console.log(fontslabel.text);
////            console.log("222222222222");
//        }
//    }

//    Column {
//        spacing: 20
//        anchors.horizontalCenter: parent.horizontalCenter

//        Row {
//            Label {
//                id: fontslabel
//                width: 110
//                text: qsTr("ps4-model")
//            }
//            ComboBox {
//                id: combobox
//                model: choices;
//                width: parent.width;
////                KeyNavigation.tab: t1
////                KeyNavigation.backtab: button2
////                onSelectedIndexChanged: console.log(selectedText)
//            }
//            Button {
//                id: button1
//                text: qsTr("确定")
//                width: 96
//                tooltip:"This is an interesting tool tip"
//                //                KeyNavigation.tab: button2
//                //                KeyNavigation.backtab: frame.tabBar
//                onClicked: {

//                }
//            }
//        }
//        Row {
//            Label {
//                id: modelabel1
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox2
//                x: 110
//            }
//        }
//        Row {
//            Label {
//                id: modelabel3
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox4
//                x: 110
//            }
//        }
//        Row {
//            Label {
//                id: modelabel5
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox6
//                x: 110
//            }
//        }


//    }//Column

//}





//Rectangle {
//    id: lancherpage
//    property bool on: true
//    width: parent.width
//    height: 460
//    property Dispatcher dis: mydispather
//    Column {
//        spacing: 20
//        anchors.top: parent.top
//        anchors.topMargin: 30
//        anchors.left: parent.left
//        anchors.leftMargin: 30

//        Row {
//            Label {
//                id: hidelabel
//                width: 110
//                text: qsTr("自动隐藏:")
//            }
//            CheckBox {
//                id: enabledCheck
//                text: qsTr("开启")
//                checked: false
//                onCheckedChanged: {}
//                onClicked: {
////                    enabledCheck.checked = !enabledCheck.checked;
////                    if (enabledCheck.checked == true) {
//////                        enabledCheck.checked = false;
////                        enabledCheck.text = qsTr("关闭");
////                    }
////                    else if (enabledCheck.checked == false){
//////                        enabledCheck.checked = true;
////                        enabledCheck.text = qsTr("开启");
////                    }
//                }
//            }

////            Common.Switch {
////                id: themeSwitch
////                anchors.right: parent.right
////                height: parent.height
////                spacing: 8
////                textOn: qsTr("On")
////                textOff: qsTr("Off")
////                fontColor: "#666666"
////                onSwitched: lancherpage.on = position
//////                id: switchLauncher
////////                checked: false
//////                x: 130
////////                onClicked: {
////////                    //kobe: wait for adding function
////////                    mydispather.set_launcher(switchLauncher.checked)
////////                }
////            }
//        }

//        Row {
//            Label {
//                id: sizelabel
//                width: 110
//                text: qsTr("图标大小:")
//            }
//            Slider {
//                id: slider
//                x: 130
////                function formatValue(v) { return v.toFixed(2) }
//                minimumValue: 0
//                maximumValue: 100
//                value: 0
////                live: true
////                onTouched: {
////                    console.log(slider.value)
////                }
//            }
//        }

//        Row {
//            Label {
//                id: locationlabel
//                width: 110
//                text: qsTr("位置:")
//            }
//            RadioButton {
//                id: radioleft
//                x: 130
////                text: "靠左"
//            }
//        }

//        Row {
//            Label {
//                id: inputlabel1
//                width: 110
//                text: qsTr("输入用户名:")
//            }
//            TextField {
//                id: textfield1
//                placeholderText: qsTr("put your username")
//                echoMode: TextInput.Normal
////                hasClearButton: true
//                width: 200
//                onTextChanged: {
//                    //kobe: wait for adding function
//                    console.log(textfield1.text)
//                }
//            }
//        }

//        Row {
//            Label {
//                id: inputlabel2
//                width: 110
//                text: qsTr("输入密码:")
//            }
//            TextField {
//                id: textfield2
//                placeholderText: qsTr("put your password")
////                hasClearButton: true
//                echoMode: TextInput.Password
//                width: 200
//                onTextChanged: {
//                    //kobe: wait for adding function
//                    console.log(textfield2.text)
//                }

//            }
//        }

//        Row {
//            Label {
//                id: progresslabel
//                width: 110
//                text: qsTr("进度显示:")
//            }
//            ProgressBar {
//                id: progressbar
////                indeterminate: true
//                value: 24
//                minimumValue: 0
//                maximumValue: 100

//            }
//        }

//        Row {
//            Label {
//                id: modelabel
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox
//                x: 110
////                titel1: "111111111"
////                titel2: "222222222"
////                titel3: "333333333"
////                flags: "launcher"
//            }

//        }
//    }
//}
