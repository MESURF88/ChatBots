import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("ChatBots")
    property double maximum: 10
    property double minimum: 0
Column
{
height: parent.height
width: parent.width

Rectangle { // background
    id: healthBar

// public
    property double value:   dspl.statInstance().healthStat

// private
    width: 400;  height: 50 // default size

    border.width: 0.05 * healthBar.height
    radius: 0.5 * height
   
    Rectangle { // foreground
        visible: healthBar.value > minimum
        x: 0.1 * healthBar.height;  y: 0.1 * healthBar.height
        width: Math.max(height,
               Math.min((healthBar.value - minimum) / (maximum - minimum) * (parent.width - 0.2 * healthBar.height),
                        parent.width - 0.2 * healthBar.height)) // clip
        height: 0.8 * healthBar.height
        color: "red"
        radius: parent.radius
    }
}


Rectangle { // background
    id: manaBar

// public
    property double value:   dspl.statInstance().manaStat

// private
    width: 400;  height: 50 // default size

    border.width: 0.05 * manaBar.height
    radius: 0.5 * height
   
    Rectangle { // foreground
        visible: manaBar.value > minimum
        x: 0.1 * manaBar.height;  y: 0.1 * manaBar.height
        width: Math.max(height,
               Math.min((manaBar.value - minimum) / (maximum - minimum) * (parent.width - 0.2 * manaBar.height),
                        parent.width - 0.2 * manaBar.height)) // clip
        height: 0.8 * manaBar.height
        color: "lightblue"
        radius: parent.radius
    }
}
Rectangle { // background
    id: staminaBar

// public
    property double value:   dspl.statInstance().staminaStat

// private
    width: 400;  height: 50 // default size

    border.width: 0.05 * staminaBar.height
    radius: 0.5 * height
   
    Rectangle { // foreground
        visible: staminaBar.value > minimum
        x: 0.1 * staminaBar.height;  y: 0.1 * staminaBar.height
        width: Math.max(height,
               Math.min((staminaBar.value - minimum) / (maximum - minimum) * (parent.width - 0.2 * staminaBar.height),
                        parent.width - 0.2 * staminaBar.height)) // clip
        height: 0.8 * staminaBar.height
        color: "lightgreen"
        radius: parent.radius
    }
}
}
}
