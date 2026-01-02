var vizhener = {
    ru: "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ".split(""),
    bel: [
        "А", "Б", "В", "Г", "Д", "Дж", "Дз", "Е", "Ё", "Ж", "І", "Й", "К", "Л", "М",
        "Н", "О", "П", "Р", "С", "Т", "У", "Ў", "Ф", "Х", "Ц", "Ч", "Ш", "Ы", "Ь",
        "Э", "Ю", "Я", "'"
    ],
    square: [],
    genSqViz: function (lang) {
        var l = this[lang];
        this.square = [];
        for (var i = 0; i < l.length; i++) {
            this.square[i] = l.slice(i).concat(l.slice(0, i));
        }
    },
    parseBelarusianText: function (text) {
        let result = [];
        for (let i = 0; i < text.length; i++) {
            if (text[i] === "Д" && text[i + 1] === "З") {
                result.push("Дз"); i++;
            } else if (text[i] === "Д" && text[i + 1] === "Ж") {
                result.push("Дж"); i++;
            } else { result.push(text[i]); }
        }
        return result;
    },
    encryption: function (lang, text, key) {
        if (lang !== "ru" && lang !== "bel") return false;

        if (lang === "bel") {
            text = this.parseBelarusianText(text);
            key = this.parseBelarusianText(this.genKey(text, key));
        } else {
            text = text.split("");
            key = this.genKey(text, key).split("");
        }

        this.genSqViz(lang);
        var s = "";
        var keyIndex = 0;

        for (var i = 0; i < text.length; i++) {
            let row = this[lang].indexOf(text[i]);
            if (row === -1) { 
                s += text[i];
            } else {
                let col = this[lang].indexOf(key[keyIndex]);
                s += this.square[row][col];
                keyIndex++;
            }
        }
        return s;
    },
    decryption: function (lang, key, cipher) {
        if (lang !== "ru" && lang !== "bel") return false;

        if (lang === "bel") {
            cipher = this.parseBelarusianText(cipher);
            key = this.parseBelarusianText(this.genKey(cipher, key));
        } else {
            cipher = cipher.split("");
            key = this.genKey(cipher, key).split("");
        }

        this.genSqViz(lang);
        var s = "";
        var keyIndex = 0;

        for (var i = 0; i < cipher.length; i++) {
            let row = this[lang].indexOf(key[keyIndex]);
            let coll = this.square[row]?.indexOf(cipher[i]);

            if (row === -1 || coll === -1) {
                s += cipher[i];
            } else {
                s += this[lang][coll];
                keyIndex++;
            }
        }
        return s;
    },
    genKey: function (text, key) {
        if (typeof text === "string") text = text.split("");
        while (key.length < text.length) {
            key += key;
        }
        return key.slice(0, text.length);
    }
};