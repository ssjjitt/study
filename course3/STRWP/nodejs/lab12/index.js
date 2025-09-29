const Sequelize = require('sequelize');
require('dotenv').config();
const op = Sequelize.Op;
const Model = Sequelize.Model;

const sequelize = new Sequelize(
    process.env.DB,
    process.env.USER,
    process.env.PASSWORD,
    {
        host: process.env.HOST,
        port: process.env.SQL_PORT,
        dialect: process.env.DIALECT,
        dialectOptions: {
            options: { encrypt: false },
        },
        pool: {
            max: 10,
            min: 1,
            idle: 20000,
        },
    }
);

const Auditorium = require('./models/auditorium')(sequelize, Sequelize.DataTypes);
const Auditorium_type = require('./models/auditorium_type')(sequelize, Sequelize.DataTypes);
const Pulpit = require('./models/pulpit')(sequelize, Sequelize.DataTypes);
const Faculty = require('./models/faculty')(sequelize, Sequelize.DataTypes);
const Subject = require('./models/subject')(sequelize, Sequelize.DataTypes);
const Teacher = require('./models/teacher')(sequelize, Sequelize.DataTypes);

const setupAssociations = require('./models/associations');
setupAssociations({ Faculty, Pulpit, Subject, Teacher, Auditorium_type, Auditorium, Sequelize });

module.exports = {
    sequelize,
    Auditorium,
    Auditorium_type,
    Faculty,
    Pulpit,
    Subject,
    Teacher
};