const fs = require('fs');
const { loadTasks, saveTasks } = require('./storage');
const assert = require('assert');

function debugPrint(label, data) {
    console.log(`\n[DEBUG] ${label}:`);
    console.table(data);
}

describe('Хранилище', () => {
    const testFile = 'test_todo_list.json';

    before(() => {
        // Переименовываем основной файл, чтобы не мешать тестам
        if (fs.existsSync('todo_list.json')) {
            fs.renameSync('todo_list.json', testFile);
        } else {
            fs.writeFileSync(testFile, JSON.stringify([]));
        }
    });

    after(() => {
        // Возвращаем обратно
        if (fs.existsSync('todo_list.json')) fs.unlinkSync('todo_list.json');
        fs.renameSync(testFile, 'todo_list.json');
    });

    it('должен загружать пустой список', () => {
        fs.writeFileSync(testFile, JSON.stringify([]));
        const tasks = loadTasks();
        debugPrint('Загруженные задачи (пустой список)', tasks);
        assert.deepStrictEqual(tasks, []);
    });
    // тут короче показать что покрытие не всегда соточка
    // it('должен сохранять и загружать задачи', () => {
    //     const tasks = [{ id: 1, task: 'Тестовая задача', done: false }];
    //     saveTasks(tasks);
    //     const loaded = loadTasks();
    //     debugPrint('Загруженные задачи (после сохранения)', loaded);
    //     assert.deepStrictEqual(loaded, tasks);
    // });
});
