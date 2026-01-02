$(document).ready(function () {
  $("#black").click(function () {
    let ctx = canvas.getContext("2d");
    ctx.strokeStyle = "black";
  });

  $("#blue").click(function () {
    let ctx = canvas.getContext("2d");
    ctx.strokeStyle = "blue";
  });

  $("#red").click(function () {
    let ctx = canvas.getContext("2d");
    ctx.strokeStyle = "red";
  });

  $("#green").click(function () {
    let ctx = canvas.getContext("2d");
    ctx.strokeStyle = "green";
  });

  $("#first").click(function () {
    let y = (x) => x * x;
    let scale = 30;
    let canvas = document.getElementById("canvas");
    let ctx = canvas.getContext("2d");

    ctx.translate(canvas.width / 2, canvas.height / 2);

    ctx.beginPath();
    for (var i = -2; i <= 2; i += 0.2) {
      if (i) {
        ctx.lineTo(i * scale, y(i) * scale);
      } else {
        ctx.moveTo(i * scale, y(i) * scale);
      }
    }
    ctx.stroke();
  });

  $("#second").click(function () {
    let y = (x) => x * x * x;
    let scale = 30;
    let canvas = document.getElementById("canvas");
    let ctx = canvas.getContext("2d");

    ctx.translate(canvas.width / 2, canvas.height / 2);

    ctx.beginPath();
    for (var i = -2; i <= 2; i += 0.2) {
      if (i) {
        ctx.lineTo(i * scale, y(i) * scale);
      } else {
        ctx.moveTo(i * scale, y(i) * scale);
      }
    }
    ctx.stroke();
  });

  $("#third").click(function () {
    let y = (x) => Math.sin(x);
    let scale = 20;
    let canvas = document.getElementById("canvas");
    let ctx = canvas.getContext("2d");
    ctx.translate(canvas.width / 2, canvas.height / 2);

    ctx.beginPath();
    for (var i = -1; i <= 10; i += 0.2) {
      if (i) {
        ctx.lineTo(i * scale, y(i) * scale);
      } else {
        ctx.moveTo(i * scale, y(i) * scale);
      }
    }
    ctx.stroke();
  });

  $("#fourth").click(function () {
    let y = (x) => Math.cos(x);
    let scale = 20;
    let canvas = document.getElementById("canvas");
    let ctx = canvas.getContext("2d");

    ctx.translate(canvas.width / 2, canvas.height / 2);

    ctx.beginPath();
    for (var i = -1; i <= 10; i += 0.2) {
      if (i) {
        ctx.lineTo(i * scale, y(i) * scale);
      } else {
        ctx.moveTo(i * scale, y(i) * scale);
      }
    }
    ctx.stroke();
  });
});
