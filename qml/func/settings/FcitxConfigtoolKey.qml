import QtQuick 1.1
import SystemType 0.1
import SessionType 0.1
import "../common" as Common
import "../bars" as Bars

Rectangle {
    id:fcitxconfigtoolKey
    width: parent.width
    height: 475

    property string actiontitle: "小企鹅输入法快捷键/云输入/皮肤配置"
    property string actiontext: "可以设置自己喜欢的方式，点击＂下一步＂继续设置，点击＂取消＂取消当前设置并返回,点击“应用”按钮完成输入法设置。"
    property int flagCheck: 1
    property int flag_i: 0
    property string h_fcitxSkinImage: ""
    property string v_fcitxSkinImage: ""
    //背景
    Image {
        source: "../../img/skin/bg-left.png"
        anchors.fill: parent
    }

    //温馨提示
    Column {
        spacing: 20
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Text {
             text: fcitxconfigtoolKey.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"

         }
         Text {
             text: fcitxconfigtoolKey.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

    function refreshFcitxKey(){
        skinModel.clear();
        //set font============================================================
        var setFont = fcitxcfgwizard.get_font();
        fontStyleBtn.text = setFont;
        //get font size=======================================================
        var getFontSize = fcitxcfgwizard.get_font_size();
        sliderFontSize.value = getFontSize;

        //get_skin_list and current_skin======================================
        var getSkinList = fcitxcfgwizard.get_all_skin_type()
        var getCurrentSkin = fcitxcfgwizard.get_skin_type()

        if(getCurrentSkin != "default")
        {
            enableSkinBox.checked = true
            flagCheck = 1;
        }
        else
        {
            enableSkinBox.checked = false;
            flagCheck = 0;
        }
        getSkinList.unshift(getCurrentSkin);   //js将数组第一个添加unshift进来的
        skinModel.clear();
        for(var i=0;i<getSkinList.length;i++)
       {
            skinModel.append({"skinTitle": getSkinList[i]});
            if(i!=0&&(getSkinList[i] == getCurrentSkin))
                skinModel.remove(i);
        }

        //load_skin_image====================================================
        if(getCurrentSkin == "default")
        {
            h_fcitxSkinImage = "../../img/skin/h_default.png"
            v_fcitxSkinImage = "../../img/skin/v_default.png"
        }
        else if(getCurrentSkin == "dark")
        {
            h_fcitxSkinImage = "../../img/skin/h_dark.png"
            v_fcitxSkinImage = "../../img/skin/v_dark.png"
        }
        else if(getCurrentSkin == "classic")
        {
            h_fcitxSkinImage = "../../img/skin/h_classic.png"
            v_fcitxSkinImage = "../../img/skin/v_classic.png"
        }
        else{
            h_fcitxSkinImage = ""
            v_fcitxSkinImage = ""
        }

  }


    Connections {
            target: fcitxcfgwizard
            onRefreshFcitxSig: {
                refreshFcitxKey();
            }
        }

    Component.onCompleted: {
        skinModel.clear();
        //set font============================================================
        var setFont = fcitxcfgwizard.get_font();
        fontStyleBtn.text = setFont;
        //get font size=======================================================
        var getFontSize = fcitxcfgwizard.get_font_size();
        sliderFontSize.value = getFontSize;

        //get_skin_list and current_skin=================================================
        var getSkinList = fcitxcfgwizard.get_all_skin_type()
        var getCurrentSkin = fcitxcfgwizard.get_skin_type()
        if(getCurrentSkin != "default")
        {
            enableSkinBox.checked = true
            flagCheck = 1;
        }
        else
        {
            enableSkinBox.checked = false;
            flagCheck = 0;
        }
        getSkinList.unshift(getCurrentSkin);   //js将数组第一个添加unshift进来的
        skinModel.clear();
        for(var i=0;i<getSkinList.length;i++)
       {
            skinModel.append({"skinTitle": getSkinList[i]});
            if(i!=0&&(getSkinList[i] == getCurrentSkin))
                skinModel.remove(i);
        }
        //load_skin_image====================================================
        if(getCurrentSkin == "default")
        {
            h_fcitxSkinImage = "../../img/skin/h_default.png"
            v_fcitxSkinImage = "../../img/skin/v_default.png"
        }
        else if(getCurrentSkin == "dark")
        {
            h_fcitxSkinImage = "../../img/skin/h_dark.png"
            v_fcitxSkinImage = "../../img/skin/v_dark.png"
        }
        else if(getCurrentSkin == "classic")
        {
            h_fcitxSkinImage = "../../img/skin/h_classic.png"
            v_fcitxSkinImage = "../../img/skin/v_classic.png"
        }
        else{
            h_fcitxSkinImage = ""
            v_fcitxSkinImage = ""
        }
    }


    //分割线
    Row{
        anchors{
            left: parent.left
            leftMargin: 40
            top: parent.top
            topMargin: 120
        }
        spacing: 5
        Text{
            text: "皮肤设置"
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        Rectangle{
            width:700
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    //使用皮肤
    Row{
        spacing: 75
        anchors {
            top: parent.top
            topMargin: 150
            left: parent.left
            leftMargin: 65
        }
        //选择皮肤
        ListModel {
            id: skinModel
            ListElement {skinTitle: "";}
        }
        Common.CheckBox{
            id:enableSkinBox
            anchors.verticalCenter: parent.verticalCenter
            titleName: "使用皮肤"
            onCheckedChanged: {
                if(flagCheck == 1)
                {
                    if(enableSkinBox.checked == false)
                    {
                        var getSkinList = fcitxcfgwizard.get_all_skin_type()
                        for(var i=0;i<getSkinList.length;i++)
                       {
                            if(getSkinList[i] == "default")
                            {
                                flag_i = i;
                                break;
                            }
                        }
                        if(fcitxcfgwizard.get_skin_type()=="default")
                                {
                                    flag_i = 0;
                                }

                        skinCombo.selectedIndex = flag_i;
                    }
                }
            }
        }
        Common.ComboBox {
            id: skinCombo
            model: skinModel
            width: 130
            height: 25
            onSelectedTextChanged: {
                if(skinCombo.selectedText != "default")
                {
                    enableSkinBox.checked = true;
                    flagCheck = 1;
                }
                //load_skin_image====================================================
                if(skinCombo.selectedText == "default")
                {
                    h_fcitxSkinImage = "../../img/skin/h_default.png"
                    v_fcitxSkinImage = "../../img/skin/v_default.png"
                    enableSkinBox.checked = false;
                    flagCheck = 0;
                }
                else if(skinCombo.selectedText == "dark")
                {
                    h_fcitxSkinImage = "../../img/skin/h_dark.png"
                    v_fcitxSkinImage = "../../img/skin/v_dark.png"
                }
                else if(skinCombo.selectedText == "classic")
                {
                    h_fcitxSkinImage = "../../img/skin/h_classic.png"
                    v_fcitxSkinImage = "../../img/skin/v_classic.png"
                }
                else{
                    h_fcitxSkinImage = ""
                    v_fcitxSkinImage = ""
                }
           }
        }
     }
    //更换字体
    Row{
        spacing: 75
        anchors {
            top: parent.top
            topMargin: 180
            left: parent.left
            leftMargin: 65
        }
        Common.CheckBox{
            id:enableHotKeyBox
            anchors.verticalCenter: parent.verticalCenter
            titleName: "更换字体"
            onCheckedChanged: {
                if(enableHotKeyBox.checked == false)
                {
                    sliderFontSize.value = 20;
                    fontStyleBtn.text = "Sans 10";
                }
            }
        }
        //fontsize
        Row{
            spacing: 10
            Text {
                id: fontSize
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("大小")
            }
            Row{
                spacing: 10
                Common.Slider {
                    id: sliderFontSize
                    anchors.verticalCenter: parent.verticalCenter
                    minimumValue: 0
                    maximumValue: 72
                    width: 150
                    stepSize: 1
                    animated: true
                    onValueChanged: {
                        if(sliderFontSize.value != 20)
                        {
                            enableHotKeyBox.checked = true;
                        }
                    }
                }
                Text {
                    id: displayFontSize
                    text: sliderFontSize.value
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
     }
    //font
   Row{
       spacing: 10
       anchors {
           top: parent.top
           topMargin: 180
           left: parent.left
           leftMargin: 400
       }
       Text {
           id: font
           font.pixelSize: 12
           color: "#7a7a7a"
           anchors.verticalCenter: parent.verticalCenter
           text: qsTr("字体设置")
       }
       Common.Button {
            id: fontStyleBtn
            smooth:true
            width: 160;height: 25
            hoverimage: "fcitxfont.png"//../../img/icons/
            fontcolor:"#929292"
            fontsize: 13
            anchors.verticalCenter: font.verticalCenter
           onClicked: {
               fontStyleBtn.text = fcitxcfgwizard.show_font_dialog();
           }
           onTextChanged: {
               if(fontStyleBtn.text != "Sans 10" )
               {
                   enableHotKeyBox = true;
               }
           }
       }
   }


    Rectangle{
        anchors{
            top:parent.top
            topMargin: 220
            left:parent.left
            leftMargin: 65
        }
       color:"white"
        width: 680
        height: 190
        Row{
            anchors{
                top:parent.top
                topMargin: 15
                left:parent.left
                leftMargin: 20
            }
        spacing: 30
        Image {
            id: fcitxVimage
            source: v_fcitxSkinImage
            smooth: true
            anchors.verticalCenter: parent.verticalCenter
        }
        Image {
            id: fcitxHimage
            source: h_fcitxSkinImage
            smooth: true
            anchors.verticalCenter: parent.verticalCenter
        }
      }
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
    //底层工具栏
    Bars.FcitxThreeBar {
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//            button1Label: qsTr("退出")
//            button1Label: qsTr("返回")
//            button2Label: qsTr("应用")
        onCancelBtnClicked: {
            fcitxcfgwizard.send_fcitx_ok_warn();
        }
        onGobackBtnClicked: {
            pageStack.push(fcitxConfigtoolFontpage);//静态添加页面

        }
        onFinishBtnClicked: {
            //接后台应用接口
            fcitxcfgwizard.set_font(fontStyleBtn.text,false);
            fcitxcfgwizard.set_font_size(sliderFontSize.value,false);
            fcitxcfgwizard.set_skin_type(skinCombo.selectedText, false);
            fcitxcfgwizard.all_cfg_save()
            pageStack.push(functioncollection);
        }

    }

}