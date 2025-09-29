$(document).ready(function () {
  $("#menu1").click(function () {
    $("#sub1").slideToggle(800);
  });

  $("#menu2").click(function () {
    $("#sub2").slideToggle(800);
  });

  $("#menu3").click(function () {
    $("#sub3").slideToggle(800);
  });

  $("#menu1").mouseover(function () {
    $("#menu1").css("background-color", "red");
  });

  $("#menu2").mouseover(function () {
    $("#menu2").css("background-color", "red");
  });

  $("#menu3").mouseover(function () {
    $("#menu3").css("background-color", "red");
  });

  $("#menu1").mouseout(function () {
    $("#menu1").css("background-color", "black");
  });

  $("#menu2").mouseout(function () {
    $("#menu2").css("background-color", "black");
  });

  $("#menu3").mouseout(function () {
    $("#menu3").css("background-color", "black");
  });

});
