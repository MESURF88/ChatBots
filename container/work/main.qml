import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    width: 460
    height: 380
    visible: true
    title: qsTr("ChatBots")
    property double maximum: 10
    property double minimum: 0


Column
{
    id: playView
height: parent.height
width: parent.width
spacing: 2
Text
{
    width: 80
    height: 20
    id: inputTextHUUID
    text: dspl.statInstance().uuid
    font.pixelSize: 20
}

Image
{
    width: 80
    height: 80
    id: theSpriteAction
    source: "idle.png"
    states: [
        State {
            name: "Idle"
            PropertyChanges {
                target: theSpriteAction
                source: "idle.png"
            }
        },
        State {
            name: "Missed Attack"
            PropertyChanges {
                target: theSpriteAction
                source: "missed.png"
            }
        },
        State {
            name: "Missed Magic Attack"
            PropertyChanges {
                target: theSpriteAction
                source: "missedmagic.png"
            }
        },
        State {
            name: "Attack"
            PropertyChanges {
                target: theSpriteAction
                source: "attack.png"
            }
        },
        State {
            name: "Magic Attack"
            PropertyChanges {
                target: theSpriteAction
                source: "magicattack.png"
            }
        },
        State {
            name: "Recover"
            PropertyChanges {
                target: theSpriteAction
                source: "recover.png"
            }
        },
        State {
            name: "Win"
            PropertyChanges {
                target: theSpriteAction
                source: "win.png"
            }
        },
        State {
            name: "Lose"
            PropertyChanges {
                target: theSpriteAction
                source: "lose.png"
            }
        }
    ]
}

Text {
    id: winLoseStatus
    width: 80
    height: 20
    font.pixelSize: 20
    color: (dspl.winStatus === "WIN")? "Green" : "Black"
    visible: (dspl.winStatus === "")? false : true
    text: dspl.winStatus
    onVisibleChanged: {
        if (theSpriteAction.state !== "Idle")
        {
            theSpriteAction.state = (dspl.winStatus === "WIN")? "Win" : "Lose";
        }
    }
}

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
    TextInput
    {
        anchors.left: healthBar.right
        width: 80
        height: 20
        id: inputTextHealth
        text: dspl.statInstance().healthStat
        font.pixelSize: 20

        Keys.onPressed: (event)=>  {
            switch(event.key)
            {
                case Qt.Key_Return:
                case Qt.Key_Enter:
                dspl.statInstance().healthStat = parseFloat(inputTextHealth.text);
                break;
            }
        }
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
    TextInput
    {
        anchors.left: manaBar.right
        width: 80
        height: 20
        id: inputTextMana
        text: dspl.statInstance().manaStat
        font.pixelSize: 20

        Keys.onPressed: (event)=>  {
            switch(event.key)
            {
                case Qt.Key_Return:
                case Qt.Key_Enter:
                dspl.statInstance().manaStat = parseFloat(inputTextMana.text);
                break;
            }
        }
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
    TextInput
    {
        anchors.left: staminaBar.right
        width: 80
        height: 20
        id: inputTextStamina
        text: dspl.statInstance().staminaStat
        font.pixelSize: 20

        Keys.onPressed: (event)=>  {
            switch(event.key)
            {
                case Qt.Key_Return:
                case Qt.Key_Enter:
                dspl.statInstance().staminaStat = parseFloat(inputTextStamina.text);
                break;
            }
        }
    }
}
Rectangle { // background
    id: amorBar

// public
    property double value:   dspl.statInstance().armorStat

// private
    width: 400;  height: 50 // default size

    border.width: 0.05 * amorBar.height
    radius: 0.5 * height

    Rectangle { // foreground
        visible: amorBar.value > minimum
        x: 0.1 * amorBar.height;  y: 0.1 * amorBar.height
        width: Math.max(height,
               Math.min((amorBar.value - minimum) / (maximum - minimum) * (parent.width - 0.2 * amorBar.height),
                        parent.width - 0.2 * amorBar.height)) // clip
        height: 0.8 * amorBar.height
        color: "darkgrey"
        radius: parent.radius
    }
    TextInput
    {
        anchors.left: amorBar.right
        width: 80
        height: 20
        id: inputTextArmor
        text: dspl.statInstance().armorStat
        font.pixelSize: 20

        Keys.onPressed: (event)=>  {
            switch(event.key)
            {
                case Qt.Key_Return:
                case Qt.Key_Enter:
                dspl.statInstance().armorStat = parseFloat(inputTextArmor.text);
                break;
            }
        }
    }
}
Rectangle
{
    id: borderRect
    height: inputTextAction.height+5
    width: 400
    border.color: "Black"
    border.width: 2
Text
{
    width: 80
    height: 20
    id: inputTextAction
    text: dspl.actionState
    font.pixelSize: 20
    onTextChanged: {
        switch(dspl.actionState)
        {
        case "MISSED ATTACK":
            theSpriteAction.state = "Missed Attack"
            break;
        case "MISSED MAGIC ATTACK":
            theSpriteAction.state = "Missed Magic Attack"
            break;
        case "NORMAL ATTACK":
            theSpriteAction.state = "Attack"
            break;
        case "MAGIC ATTACK":
            theSpriteAction.state = "Magic Attack"
            break;
        case "RECOVER":
            theSpriteAction.state = "Recover"
            break;
        default:
            theSpriteAction.state = "Idle"
            break;
        }
    }
}
}
}
}
