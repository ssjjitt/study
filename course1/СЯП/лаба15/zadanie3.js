let regexp = /<[<a>]>/gm;

let str = `<a>привет</a>
</a>как дела<a>
<u>!!!!</u>
`;

alert(str.replace(regexp, " open a ")); 