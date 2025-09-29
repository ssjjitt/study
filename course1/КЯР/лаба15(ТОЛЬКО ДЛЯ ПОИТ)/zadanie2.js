
let form = document.querySelector("form");
let footer = document.querySelector("footer");


function fn(){
    footer.innerHTML = "<br>" + form.elements[0].value+ "<br>" +form.elements[1].value+ "<br>" +form.elements[2].value+ "<br>" +form.elements[3].value+ "<br>" +form.elements[4].value+ "<br>" +form.elements[5].value;
}
