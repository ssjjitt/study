let re1 = /[+[u]]|[+[/u]+]/gm;
let str = `[u]прив[/u]
[u]как дела[/u]
[u]!!!!!
`;
let newstr = str.replace(re1, "<u>");
console.log(newstr);