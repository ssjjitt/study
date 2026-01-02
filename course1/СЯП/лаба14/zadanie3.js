let userName = "Глухова Дарья";

document.write("первоначальная строка: " +userName);

userName = userName.padStart(18, "123");
document.write("<br>добавим цифры в начале: " +userName);

userName = userName.padEnd(20, "18");
document.write("<br>добавим возраст: " +userName);

