let nIntervId;                                                  // переменная для интервала
let x = 0;                                                // переменная использующаяся в формулах, изменяется каждый интервал

function startMove() {                                    // ДЛЯ НАЧАЛА ДВИЖЕНИЯ
    if (!nIntervId) {                                       // провка, установлен ли уже интервал
        nIntervId = setInterval(move, 10);                    // не установлен, значит установим
    }
}

function move() {                                         // ДВИЖЕНИЕ ПО СИНУСОИДЕ
    x += 1;
    document.getElementById("image").style.left = 50 + x + "px";
    document.getElementById("image").style.top = 100 + 50 * Math.sin(0.03 * x) + "px";
    console.log("left: " + document.getElementById("image").style.left);
    console.log("top: " + document.getElementById("image").style.top);
}

function stopMove() {                                     // ДЛЯ ОСТАНОВКИ ДВИЖЕНИЯ
    clearInterval(nIntervId);                               // очистка интервала
    nIntervId = null;                                       // обнуление переменной 
}

function back() {                                         // ДЛЯ ДВИЖЕНИЯ НАЗАД
    if (!nIntervId) {
        nIntervId = setInterval(backMove, 10);
    }
}

function backMove() {                                     // ДВИЖЕНИЕ НАЗАД ПО СИНУСОИДЕ
    x += 1;
    document.getElementById("image").style.left = 700 - x + "px";
    document.getElementById("image").style.top = 100 + 50 * Math.sin(0.03 * x) + "px";
}

document.getElementById("start").addEventListener("click", startMove);            // СОБЫТИЯ ДЛЯ КНОПОЧЕК
document.getElementById("stop").addEventListener("click", stopMove);
document.getElementById("back").addEventListener("click", back);