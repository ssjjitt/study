const assert = require('assert');

// Заглушка хранилища
const fakeStorage = {
    tasks: [],

    loadTasks: function () {
        return this.tasks;
    },

    saveTasks: function (newTasks) {
        this.tasks = newTasks;
    }
};

// Подменяем весь модуль `tasks.js`
const tasks = {
    addTask(description) {
        const tasks = fakeStorage.loadTasks();
        tasks.push({ id: tasks.length + 1, task: description, done: false });
        fakeStorage.saveTasks(tasks);
    },

    listTasks() {
        return fakeStorage.loadTasks();
    },

    updateTask(id, newDesc) {
        const tasks = fakeStorage.loadTasks();
        const task = tasks.find(t => t.id === id);
        if (task) {
            task.task = newDesc;
            fakeStorage.saveTasks(tasks);
            return true;
        }
        return false;
    },

    deleteTask(id) {
        const tasks = fakeStorage.loadTasks();
        const newTasks = tasks.filter(t => t.id !== id);
        if (newTasks.length !== tasks.length) {
            fakeStorage.saveTasks(newTasks);
            return true;
        }
        return false;
    },

    markDone(id) {
        const tasks = fakeStorage.loadTasks();
        const task = tasks.find(t => t.id === id);
        if (task) {
            task.done = true;
            fakeStorage.saveTasks(tasks);
            return true;
        }
        return false;
    }
};

// Вспомогательная функция для вывода отладочной информации
function debugPrint(label, data) {
    console.log(`\n[DEBUG] ${label}:`);
    console.table(data);
}

describe('Задачи (с полной изоляцией)', () => {
    beforeEach(() => {
        fakeStorage.tasks = [{ id: 1, task: 'Тестовая задача', done: false }];
    });

    it('должен добавлять задачу', () => {
        tasks.addTask('Новая задача');
        const all = tasks.listTasks();
        debugPrint('После добавления задачи', all);
        assert.strictEqual(all.length, 2);
        assert.strictEqual(all[1].task, 'Новая задача');
    });

    it('новая задача должна иметь done=false', () => {
        tasks.addTask('Проверка done');
        const added = tasks.listTasks().find(t => t.task === 'Проверка done');
        debugPrint('Проверка done=false', tasks.listTasks());
        assert.strictEqual(added.done, false);
    });

    it('id должен быть уникален при добавлении', () => {
        tasks.addTask('ещё 1');
        tasks.addTask('ещё 2');
        const all = tasks.listTasks();
        const ids = all.map(t => t.id);
        const unique = [...new Set(ids)];
        debugPrint('Проверка уникальности id', all);
        assert.deepStrictEqual(ids, unique);
    });

    it('можно найти задачу по описанию после добавления нескольких', () => {
        tasks.addTask('Погладить кота');
        tasks.addTask('Покормить кота');
        const found = tasks.listTasks().filter(t => t.task.includes('кота'));
        debugPrint('Фильтр по "кота"', found);
        assert.strictEqual(found.length, 2);
    });

    it('должен обновлять задачу, не трогая другие поля', () => {
        const before = tasks.listTasks()[0];
        tasks.updateTask(1, 'Новое описание');
        const updated = tasks.listTasks()[0];
        debugPrint('После обновления описания', tasks.listTasks());
        assert.strictEqual(updated.id, before.id);
        assert.strictEqual(updated.done, before.done);
    });

    it('удаление должно удалить только нужную задачу', () => {
        tasks.addTask('Останется');
        const idToDelete = fakeStorage.tasks.find(t => t.task === 'Тестовая задача').id;
        tasks.deleteTask(idToDelete);
        const all = tasks.listTasks();
        debugPrint('После удаления', all);
        assert.strictEqual(all.length, 1);
        assert.strictEqual(all[0].task, 'Останется');
    });

    it('markDone не должен менять описание', () => {
        const before = tasks.listTasks()[0].task;
        tasks.markDone(1);
        const after = tasks.listTasks()[0];
        debugPrint('После markDone()', tasks.listTasks());
        assert.strictEqual(after.task, before);
        assert.strictEqual(after.done, true);
    });

    // Базовые тесты
    it('должен обновлять задачу', () => {
        const result = tasks.updateTask(1, 'Обновлено');
        assert.strictEqual(result, true);
        const all = tasks.listTasks();
        debugPrint('Обновление задачи', all);
        assert.strictEqual(all[0].task, 'Обновлено');
    });

    it('не должен обновлять несуществующую задачу', () => {
        const result = tasks.updateTask(99, '...');
        debugPrint('Попытка обновить несуществующую задачу', tasks.listTasks());
        assert.strictEqual(result, false);
    });

    it('должен удалять задачу', () => {
        const result = tasks.deleteTask(1);
        const remaining = tasks.listTasks();
        debugPrint('После удаления задачи', remaining);
        assert.strictEqual(result, true);
        assert.strictEqual(remaining.length, 0);
    });

    it('не должен удалять несуществующую задачу', () => {
        const result = tasks.deleteTask(999);
        debugPrint('Попытка удаления несуществующей задачи', tasks.listTasks());
        assert.strictEqual(result, false);
    });

    it('должен отмечать задачу как выполненную', () => {
        const result = tasks.markDone(1);
        const updated = tasks.listTasks()[0];
        debugPrint('После markDone()', tasks.listTasks());
        assert.strictEqual(result, true);
        assert.strictEqual(updated.done, true);
    });

    it('не должен отмечать несуществующую задачу как выполненную', () => {
        const result = tasks.markDone(999);
        debugPrint('Попытка отметить несуществующую задачу', tasks.listTasks());
        assert.strictEqual(result, false);
    });
    
});
// nyc
// proxyquire
// sinon
// mocha