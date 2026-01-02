const EventEmitter = require('events');

class DB extends EventEmitter {
    constructor() {
        super();
        this.db_data = [
            {
                id: 1,
                name: 'Савко Сашка',
                bday: '1763-01-01'
            },
            {
                id: 2,
                name: 'Жук Светка',
                bday: '2004-10-20'
            },
            {
                id: 3,
                name: 'Сосновец Дашш',
                bday: '2004-10-26'
            },
            {
                id: 4,
                name: 'Ващилко Дашш',
                bday: '2004-10-06'
            }
        ];
    }

    commit() {
        this.emit('COMMIT');
    }

    select() {
        return this.db_data;
    }

    insert(row) {
        row.id = this.db_data.length ? this.db_data[this.db_data.length - 1].id + 1 : 1;
        this.db_data.push(row);
    }

    update(row) {
        let index = this.db_data.findIndex(el => el.id === row.id);
        if (index !== -1) {
            this.db_data[index] = row;
        }
    }

    delete(id) {
        let index = this.db_data.findIndex(el => el.id === id);
        if (index !== -1) {
            return this.db_data.splice(index, 1)[0];
        }
        return null;
    }
}

exports.DB = DB;