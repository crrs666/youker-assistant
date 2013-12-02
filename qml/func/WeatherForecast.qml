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
import "common" as Common
import "bars" as Bars
Item {
    id: weatherpage; width: parent.width; height: 475
    Rectangle {
        id: weather_widget
        anchors.fill: parent
        property string actiontitle: qsTr("Forecast in the coming 6 days.")//未来六天天气预报
        property string actiontext: qsTr("Access to the China Meteorological Administration six days weather data, provide travel information for users.")//获取中国气象局的六天天气预报数据，为用户出行提供参考。

        //设置六天天气预报数据显示在QML界面上
        function initWeatherForcast() {
            //("星期日"),("星期一"),("星期二"),("星期三"),("星期四"),("星期五"),("星期六")
            var dayNames = new Array(qsTr("Sunday"),qsTr("Monday"),qsTr("Tuesday"),qsTr("Wednesday"),qsTr("Thursday"),qsTr("Friday"),qsTr("Saturday"));
            var Stamp = new Date();
            var dateTime = (Stamp.getMonth() + 1) +"月" +Stamp.getDate()+ "日";
            var num = Stamp.getDay();
            week1.text = dateTime + " " + dayNames[num];
            var alterNum;
            for(var i = num+1; i<num+6; i++) {
                if(i == num+1) {
                    if(i >=7) {
                        alterNum = i - 7;
                        week2.text = dayNames[alterNum];
                    }
                    else
                        week2.text = dayNames[i];
                }
                else if(i == num+2) {
                    if(i >=7) {
                        alterNum = i - 7;
                        week3.text = dayNames[alterNum];
                    }
                    else
                        week3.text = dayNames[i];
                }
                else if(i == num+3) {
                    if(i >=7) {
                        alterNum = i - 7;
                        week4.text = dayNames[alterNum];
                    }
                    else
                        week4.text = dayNames[i];
                }
                else if(i == num+4) {
                    if(i >=7) {
                        alterNum = i - 7;
                        week5.text = dayNames[alterNum];
                    }
                    else
                        week5.text = dayNames[i];
                }
                else if(i == num+5) {
                    if(i >=7) {
                        alterNum = i - 7;
                        week6.text = dayNames[alterNum];
                    }
                    else
                        week6.text = dayNames[i];
                }
            }

            var updateTime = sessiondispatcher.getSingleWeatherInfo("fchh", "forecast");
            //未来六天天气预报，预报时间：          时
            weather_widget.actiontitle = sessiondispatcher.getSingleWeatherInfo("city", "forecast") + qsTr("Forecast in the coming 6 days, the forecast time is：") + sessiondispatcher.getSingleWeatherInfo("date_y", "forecast") + updateTime + qsTr("hour");
            //将字符串类型的时间转成整形
            var updateIntTime = parseInt(updateTime, 10);
            if(updateIntTime >= 6 && updateIntTime < 18) {
                //白天
                var result1 = sessiondispatcher.getSingleWeatherInfo("img1", "forecast");
                var result2 = sessiondispatcher.getSingleWeatherInfo("img2", "forecast");
                if (result1 == "99") {
                    img1.source = "../img/weather/d" + result2 + ".gif";
                }
                else {
                    img1.source = "../img/weather/d" + result1 + ".gif";
                }
                if (result2 == "99") {
                    img2.source = "../img/weather/n" + result1 + ".gif";
                }
                else {
                    img2.source = "../img/weather/n" + result2 + ".gif";
                }


                var result3 = sessiondispatcher.getSingleWeatherInfo("img3", "forecast");
                var result4 = sessiondispatcher.getSingleWeatherInfo("img4", "forecast");
                if (result3 == "99") {
                    img3.source = "../img/weather/d" + result4 + ".gif";
                }
                else {
                    img3.source = "../img/weather/d" + result3 + ".gif";
                }
                if (result4 == "99") {
                    img4.source = "../img/weather/n" + result3 + ".gif";
                }
                else {
                    img4.source = "../img/weather/n" + result4 + ".gif";
                }


                var result5 = sessiondispatcher.getSingleWeatherInfo("img5", "forecast");
                var result6 = sessiondispatcher.getSingleWeatherInfo("img6", "forecast");
                if (result5 == "99") {
                    img5.source = "../img/weather/d" + result6 + ".gif";
                }
                else {
                    img5.source = "../img/weather/d" + result5 + ".gif";
                }
                if (result6 == "99") {
                    img6.source = "../img/weather/n" + result5 + ".gif";
                }
                else {
                    img6.source = "../img/weather/n" + result6 + ".gif";
                }

                var result7 = sessiondispatcher.getSingleWeatherInfo("img7", "forecast");
                var result8 = sessiondispatcher.getSingleWeatherInfo("img8", "forecast");
                if (result7 == "99") {
                    img7.source = "../img/weather/d" + result8 + ".gif";
                }
                else {
                    img7.source = "../img/weather/d" + result7 + ".gif";
                }
                if (result8 == "99") {
                    img8.source = "../img/weather/n" + result7 + ".gif";
                }
                else {
                    img8.source = "../img/weather/n" + result8 + ".gif";
                }


                var result9 = sessiondispatcher.getSingleWeatherInfo("img9", "forecast");
                var result10 = sessiondispatcher.getSingleWeatherInfo("img10", "forecast");
                if (result9 == "99") {
                    img9.source = "../img/weather/d" + result10 + ".gif";
                }
                else {
                    img9.source = "../img/weather/d" + result9 + ".gif";
                }
                if (result10 == "99") {
                    img10.source = "../img/weather/n" + result9 + ".gif";
                }
                else {
                    img10.source = "../img/weather/n" + result10 + ".gif";
                }


                var result11 = sessiondispatcher.getSingleWeatherInfo("img11", "forecast");
                var result12 = sessiondispatcher.getSingleWeatherInfo("img12", "forecast");
                if (result11 == "99") {
                    img11.source = "../img/weather/d" + result12 + ".gif";
                }
                else {
                    img11.source = "../img/weather/d" + result11 + ".gif";
                }
                if (result12 == "99") {
                    img12.source = "../img/weather/n" + result11 + ".gif";
                }
                else {
                    img12.source = "../img/weather/n" + result12 + ".gif";
                }
            }
            else {
                //晚上
                var result1n = sessiondispatcher.getSingleWeatherInfo("img1", "forecast");
                var result2n = sessiondispatcher.getSingleWeatherInfo("img2", "forecast");

                if (result1n == "99") {
                    img1.source = "../img/weather/n" + result2n + ".gif";
                }
                else {
                    img1.source = "../img/weather/n" + result1n + ".gif";
                }
                if (result2n == "99") {
                    img2.source = "../img/weather/d" + result1n + ".gif";
                }
                else {
                    img2.source = "../img/weather/d" + result2n + ".gif";
                }


                var result3n = sessiondispatcher.getSingleWeatherInfo("img3", "forecast");
                var result4n = sessiondispatcher.getSingleWeatherInfo("img4", "forecast");
                if (result3n == "99") {
                    img3.source = "../img/weather/n" + result4n + ".gif";
                }
                else {
                    img3.source = "../img/weather/n" + result3n + ".gif";
                }
                if (result4n == "99") {
                    img4.source = "../img/weather/d" + result3n + ".gif";
                }
                else {
                    img4.source = "../img/weather/d" + result4n + ".gif";
                }


                var result5n = sessiondispatcher.getSingleWeatherInfo("img5", "forecast");
                var result6n = sessiondispatcher.getSingleWeatherInfo("img6", "forecast");
                if (result5n == "99") {
                    img5.source = "../img/weather/n" + result6n + ".gif";
                }
                else {
                    img5.source = "../img/weather/n" + result5n + ".gif";
                }
                if (result6n == "99") {
                    img6.source = "../img/weather/d" + result5n + ".gif";
                }
                else {
                    img6.source = "../img/weather/d" + result6n + ".gif";
                }

                var result7n = sessiondispatcher.getSingleWeatherInfo("img7", "forecast");
                var result8n = sessiondispatcher.getSingleWeatherInfo("img8", "forecast");
                if (result7n == "99") {
                    img7.source = "../img/weather/n" + result8n + ".gif";
                }
                else {
                    img7.source = "../img/weather/n" + result7n + ".gif";
                }
                if (result8n == "99") {
                    img8.source = "../img/weather/d" + result7n + ".gif";
                }
                else {
                    img8.source = "../img/weather/d" + result8n + ".gif";
                }


                var result9n = sessiondispatcher.getSingleWeatherInfo("img9", "forecast");
                var result10n = sessiondispatcher.getSingleWeatherInfo("img10", "forecast");
                if (result9n == "99") {
                    img9.source = "../img/weather/n" + result10n + ".gif";
                }
                else {
                    img9.source = "../img/weather/n" + result9n + ".gif";
                }
                if (result10n == "99") {
                    img10.source = "../img/weather/d" + result9n + ".gif";
                }
                else {
                    img10.source = "../img/weather/d" + result10n + ".gif";
                }


                var result11n = sessiondispatcher.getSingleWeatherInfo("img11", "forecast");
                var result12n = sessiondispatcher.getSingleWeatherInfo("img12", "forecast");
                if (result11n == "99") {
                    img11.source = "../img/weather/n" + result12n + ".gif";
                }
                else {
                    img11.source = "../img/weather/n" + result11n + ".gif";
                }
                if (result12n == "99") {
                    img12.source = "../img/weather/d" + result11n + ".gif";
                }
                else {
                    img12.source = "../img/weather/d" + result12n + ".gif";
                }
            }
            temp1.text = sessiondispatcher.getSingleWeatherInfo("temp1", "forecast");
            temp2.text = sessiondispatcher.getSingleWeatherInfo("temp2", "forecast");
            temp3.text = sessiondispatcher.getSingleWeatherInfo("temp3", "forecast");
            temp4.text = sessiondispatcher.getSingleWeatherInfo("temp4", "forecast");
            temp5.text = sessiondispatcher.getSingleWeatherInfo("temp5", "forecast");
            temp6.text = sessiondispatcher.getSingleWeatherInfo("temp6", "forecast");
            weather1.text = sessiondispatcher.getSingleWeatherInfo("weather1", "forecast");
            weather2.text = sessiondispatcher.getSingleWeatherInfo("weather2", "forecast");
            weather3.text = sessiondispatcher.getSingleWeatherInfo("weather3", "forecast");
            weather4.text = sessiondispatcher.getSingleWeatherInfo("weather4", "forecast");
            weather5.text = sessiondispatcher.getSingleWeatherInfo("weather5", "forecast");
            weather6.text = sessiondispatcher.getSingleWeatherInfo("weather6", "forecast");
            wind1.text = sessiondispatcher.getSingleWeatherInfo("wind1", "forecast");
            wind2.text = sessiondispatcher.getSingleWeatherInfo("wind2", "forecast");
            wind3.text = sessiondispatcher.getSingleWeatherInfo("wind3", "forecast");
            wind4.text = sessiondispatcher.getSingleWeatherInfo("wind4", "forecast");
            wind5.text = sessiondispatcher.getSingleWeatherInfo("wind5", "forecast");
            wind6.text = sessiondispatcher.getSingleWeatherInfo("wind6", "forecast");
        }

        Connections
        {
            target: sessiondispatcher
            onStartUpdateForecastWeahter: {
                weather_widget.initWeatherForcast();
            }
        }

        Component.onCompleted: {
            sessiondispatcher.get_forecast_weahter_qt();
            weather_widget.initWeatherForcast();
        }
        //背景
        Image {
            source: "../img/skin/bg-middle.png"
            anchors.fill: parent
        }
        //顶层工具栏
        Bars.TopBar {
            id: topBar
            width: 28
            height: 26
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 40
            opacity: 0.9
            onButtonClicked: {
                var num = sessiondispatcher.get_page_num();
                if (num == 0)
                    pageStack.push(homepage)
                else if (num == 3)
                    pageStack.push(systemset)
                else if (num == 4)
                    pageStack.push(functioncollection)
            }
        }
        Column {
            spacing: 10
            anchors.top: parent.top
            anchors.topMargin: 44
            anchors.left: parent.left
            anchors.leftMargin: 80
            Text {
                 text: weather_widget.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
             }
             Text {
                 text: weather_widget.actiontext
                 font.pixelSize: 12
                 color: "#7a7a7a"
             }
        }

        Column {
            anchors{
                left: parent.left
                leftMargin: 150
                top: parent.top
                topMargin: 120
            }
            spacing: 30
            Row {
                spacing: 100
                Column {
                    spacing: 5
                    Text {
                        id: week1
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Row {
                        spacing: 20
                        Image {
                            id: img1
                            source: "../img/weather/d0.gif"
                        }
                        Image {
                            id: img2
                            source: "../img/weather/d1.gif"
                        }
                    }
                    Text {
                        id: temp1
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: weather1
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: wind1
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                Column {
                    spacing: 5
                    Text {
                        id: week2
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Row {
                        spacing: 20
                        Image {
                            id: img3
                            source: "../img/weather/d0.gif"
                        }
                        Image {
                            id: img4
                            source: "../img/weather/d1.gif"
                        }
                    }
                    Text {
                        id: temp2
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: weather2
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: wind2
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                Column {
                    spacing: 5
                    Text {
                        id: week3
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Row {
                        spacing: 20
                        Image {
                            id: img5
                            source: "../img/weather/d0.gif"
                        }
                        Image {
                            id: img6
                            source: "../img/weather/d1.gif"
                        }
                    }
                    Text {
                        id: temp3
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: weather3
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: wind3
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

            }
            Row {
                spacing: 100
                Column {
                    spacing: 5
                    Text {
                        id: week4
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Row {
                        spacing: 20
                        Image {
                            id: img7
                            source: "../img/weather/d0.gif"
                        }
                        Image {
                            id: img8
                            source: "../img/weather/d1.gif"
                        }
                    }
                    Text {
                        id: temp4
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: weather4
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: wind4
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                Column {
                    spacing: 5
                    Text {
                        id: week5
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Row {
                        spacing: 20
                        Image {
                            id: img9
                            source: "../img/weather/d0.gif"
                        }
                        Image {
                            id: img10
                            source: "../img/weather/d1.gif"
                        }
                    }
                    Text {
                        id: temp5
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: weather5
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: wind5
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }


                Column {
                    spacing: 5
                    Text {
                        id: week6
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Row {
                        spacing: 20
                        Image {
                            id: img11
                            source: "../img/weather/d0.gif"
                        }
                        Image {
                            id: img12
                            source: "../img/weather/d1.gif"
                        }
                    }
                    Text {
                        id: temp6
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: weather6
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: wind6
                        text: ""
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
    }
}
