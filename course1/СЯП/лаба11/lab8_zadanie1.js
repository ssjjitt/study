// Плагин (plug-in ) – это модуль к
// программе, который создается отдельно и, в случае необходимости, может
// быть подключен к уже работающему приложению.
// $ вызывает функциональность библиотеки jquery
// ECMAScript - спецификация, которая описывает, каким может быть скриптовый язык. По сути это скриптовый язык, на котором основан js
// jQuery – это библиотека, которая значительно упрощает и ускоряет
// написание JavaScript кода. 

$(document).ready(function () {
  // Код который будет выполнен после полной загрузки документа
  $("p#paragraph").mouseover(function () {
    $("p#paragraph").css("color", "blue");
  });

  $("p#paragraph").mouseout(function () {
    $("p#paragraph").css("color", "black");
  });

  $("p#paragraph").click(function () {
    $("p#paragraph").css("fontSize", "20px");
  });

  $("#image").click(function () {
    $("#image").attr("src", "kot12.jpg");
  });

  $("#appearCat").click(function () {
    $("#appearCat").html("<img src = 'kot10.jpg'>");
  });

  $("#sizeImg").mouseover(function () {
    $("#sizeImg").css("width", "300px");
  });

  $("#sizeImg").mouseout(function () {
    $("#sizeImg").css("width", "200px");
  });

  $("#border").dblclick(function () {
    $("#border").css("border", "2px dashed blue");
  });
});
